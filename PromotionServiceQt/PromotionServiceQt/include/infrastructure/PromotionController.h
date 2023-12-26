#ifndef PROMOTIONCONTROLLER_H
#define PROMOTIONCONTROLLER_H

#include <QTcpServer>
#include <QObject>
#include <QFutureWatcher>
#include "include/application/usecases/GetPromotionForProductsUseCase.h"
#include "include/domain/interfaces/IUnitOfWork.h"

class PromotionController : public QObject
{
    Q_OBJECT

public:
    PromotionController(std::shared_ptr<IUnitOfWork> unitOfWork, QObject* parent = nullptr);

public slots:
    void handleNewConnection(QTcpSocket* clientSocket);

private:
    std::shared_ptr<IUnitOfWork> _unitOfWork;

    void processRequestAsync(QTcpSocket* clientSocket, const QByteArray& request);
    void processRequest(QTcpSocket* clientSocket, const QByteArray& request);
    void calculateDiscount(QTcpSocket* clientSocket, const QList<ProductDto>& products);
    void sendResponseAsync(QTcpSocket* clientSocket);
    void sendResponse(QTcpSocket* clientSocket);
    QList<ProductDto> parseProducts(const QJsonArray& jsonArray);
    QByteArray createJsonResponse(const DiscountDto& discountDto);

    struct ResponseData {
        QTcpSocket* clientSocket;
        QByteArray responseData;
    };

    QQueue<ResponseData> responseQueue;

    GetPromotionForProductsUseCase* _productsUseCase;
};

#endif // PROMOTIONCONTROLLER_H
