#include "include/infrastructure/DiscountServer.h"

DiscountTask::DiscountTask(QTcpSocket *socket) : socket(socket) {
    socket->setParent(nullptr);
    setAutoDelete(true);
}

void DiscountTask::run() {
    if (!socket->waitForReadyRead(5000)) {
        emit errorOccurred(socket->error());
        socket->deleteLater();
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(socket->readAll());
    QJsonObject response = calculateDiscount(doc.object());

    socket->write(QJsonDocument(response).toJson());
    socket->disconnectFromHost();
    socket->waitForDisconnected();
    socket->deleteLater();
}

QJsonObject DiscountTask::calculateDiscount(const QJsonObject &input) {

    // Implement your discount calculation logic here

    QThread::msleep(300); // Sleep for 300 millisecond

    QJsonObject result;
    // ... perform calculations

    result["originalPrice"] = 100;
    result["discount"] = 10; // 10% discount
    result["finalPrice"] = 90; // Final price after discount

    return result;
}

DiscountServer::DiscountServer() {
    pool.setMaxThreadCount(50);
    listen(QHostAddress::Any, 8080);
}

void DiscountServer::incomingConnection(qintptr socketDescriptor) {
    QTcpSocket *socket = new QTcpSocket();
    if (socket->setSocketDescriptor(socketDescriptor)) {
        DiscountTask *task = new DiscountTask(socket);
        connect(task, &DiscountTask::errorOccurred, this, &DiscountServer::onErrorOccurred);
        pool.start(task);
    } else {
        delete socket;
    }
}

void DiscountServer::onErrorOccurred(QAbstractSocket::SocketError socketError) {
    // Handle errors here
}
