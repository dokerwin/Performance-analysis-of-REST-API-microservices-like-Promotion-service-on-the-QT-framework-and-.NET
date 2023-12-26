#include "include/infrastructure/PromotionController.h"
#include "include/infrastructure/SqliteUnitOfWork.h"
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QFuture>
#include <QtConcurrent>
#include <QFutureWatcher>

PromotionController::PromotionController(std::shared_ptr<IUnitOfWork> unitOfWork, QObject* parent)
    : QObject(parent), _unitOfWork(unitOfWork) {

    _productsUseCase = new GetPromotionForProductsUseCase(unitOfWork);
}

void PromotionController::handleNewConnection(QTcpSocket* clientSocket) {
    connect(clientSocket, &QTcpSocket::readyRead, this, [this, clientSocket]() {
        if (!clientSocket->isValid()) {
            // Handle invalid socket case
            return;
        }

        QByteArray request = clientSocket->readAll();
        processRequestAsync(clientSocket, request);
    });
    connect(clientSocket, &QTcpSocket::disconnected, this, [clientSocket]() {
        qDebug() << "Client disconnected:" << clientSocket->peerAddress().toString();
        // Handle any cleanup or state resetting here
    });
}

void PromotionController::processRequestAsync(QTcpSocket* clientSocket, const QByteArray& request) {
    QFuture<void> future = QtConcurrent::run(this, &PromotionController::processRequest, clientSocket, request);

    QFutureWatcher<void>* watcher = new QFutureWatcher<void>(this);
    connect(watcher, &QFutureWatcher<void>::finished, this, [this, clientSocket, watcher]() {
        watcher->deleteLater();
        sendResponseAsync(clientSocket);
    });

    watcher->setFuture(future);

}

void PromotionController::processRequest(QTcpSocket* clientSocket, const QByteArray& request) {
    if (request.contains("POST /calculate-discount HTTP/1.1")) {
        int jsonStartIndex = request.indexOf("\r\n\r\n") + 4;
        QByteArray jsonRequestBody = request.mid(jsonStartIndex);
        QJsonDocument doc = QJsonDocument::fromJson(jsonRequestBody);
        QJsonArray jsonArray = doc.array();

        QList<ProductDto> products = parseProducts(jsonArray);

        calculateDiscount(clientSocket, products);
    }
    // Additional request handling...
}

void PromotionController::calculateDiscount(QTcpSocket* clientSocket, const QList<ProductDto>& products) {

    GetPromotionForProductsUseCase a =  GetPromotionForProductsUseCase(_unitOfWork);
    DiscountDto result = a.execute(products).result();

    QByteArray responseData = createJsonResponse(result);
    responseQueue.enqueue({clientSocket, responseData});
}

void PromotionController::sendResponseAsync(QTcpSocket* clientSocket) {
    QFuture<void> future = QtConcurrent::run(this, &PromotionController::sendResponse, clientSocket);

    QFutureWatcher<void>* watcher = new QFutureWatcher<void>(this);
    connect(watcher, &QFutureWatcher<void>::finished, this, [watcher]() {
        watcher->deleteLater();
    });

    watcher->setFuture(future);
}

void PromotionController::sendResponse(QTcpSocket* clientSocket) {
    QByteArray responseData;

    while (!responseQueue.isEmpty()) {
        auto response = responseQueue.dequeue();
        if (response.clientSocket == clientSocket) {
            responseData = response.responseData;
            break;
        }
    }

    if (responseData.isEmpty()) {
        qWarning() << "Response data not found for the client socket";
        return;
    }

    if (!clientSocket || !clientSocket->isOpen()) {
        qWarning() << "Client socket is null or not open";
        return;
    }

    QByteArray httpResponse;
    httpResponse.append("HTTP/1.1 200 OK\r\n");
    httpResponse.append("Content-Type: application/json\r\n");
    httpResponse.append("Content-Length: " + QByteArray::number(responseData.size()) + "\r\n");
    httpResponse.append("\r\n");
    httpResponse.append(responseData);

    if (clientSocket->write(httpResponse) == -1) {
        qWarning() << "Failed to write to socket: " << clientSocket->errorString();
    } else {
        if (!clientSocket->flush()) {
            qWarning() << "Failed to flush socket: " << clientSocket->errorString();
        }
    }
}

QList<ProductDto> PromotionController::parseProducts(const QJsonArray& jsonArray) {
    QList<ProductDto> products;
    for (const QJsonValue &value : jsonArray) {
        QJsonObject obj = value.toObject();
        ProductDto product;
        product.setId(obj["Id"].toInt());
        product.setName(obj["Name"].toString());
        product.setPrice(obj["Price"].toDouble());
        product.setQuantity(obj["Quantity"].toInt());
        products.append(product);
    }
    return products;
}

QByteArray PromotionController::createJsonResponse(const DiscountDto& discountDto) {
    QJsonArray jsonArray;
    for (const auto& discount : discountDto.getDiscounts()) {
        QJsonObject jsonDiscount;
        jsonDiscount["ProductId"] = discount.getProductId();
        jsonDiscount["PromotionId"] = discount.getPromotionId();
        jsonDiscount["DiscountName"] = discount.getDiscountName();
        jsonDiscount["Discount"] = discount.getDiscount();
        jsonDiscount["OriginalPrice"] = discount.getOriginalPrice();
        jsonDiscount["SellingPrice"] = discount.getSellingPrice();
        jsonArray.append(jsonDiscount);
    }

    QJsonDocument doc(jsonArray);
    return doc.toJson();
}
