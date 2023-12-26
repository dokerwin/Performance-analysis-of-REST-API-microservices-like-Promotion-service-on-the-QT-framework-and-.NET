// DiscountServer.h

#ifndef DISCOUNTSERVER_H
#define DISCOUNTSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QThreadPool>
#include <QRunnable>
#include <QJsonDocument>
#include <QJsonObject>

class DiscountTask : public QObject, public QRunnable {
    Q_OBJECT

public:
    DiscountTask(QTcpSocket *socket);

    void run() override;

signals:
    void errorOccurred(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket *socket;
    QJsonObject calculateDiscount(const QJsonObject &input);
};

class DiscountServer : public QTcpServer {
    Q_OBJECT

public:
    DiscountServer();

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void onErrorOccurred(QAbstractSocket::SocketError socketError);

private:
    QThreadPool pool;
};

#endif // DISCOUNTSERVER_H
