#include <QCoreApplication>
#include "include/infrastructure/PromotionController.h"
#include "include/infrastructure/SqliteUnitOfWork.h"
#include <QDebug>


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);


    // Create an instance of SqliteUnitOfWork
    QString databasePath = "C:/Users/User/Desktop/AEH/Praca magisterska/LocalDatabase.db";

    std::shared_ptr<IUnitOfWork> unitOfWork = std::make_shared<SQLiteUnitOfWork>(databasePath);

    // Create an instance of PromotionController
    PromotionController controller(unitOfWork);

    // Set up the TCP server
    QTcpServer server;
    QObject::connect(&server, &QTcpServer::newConnection, [&server, &controller]() {
        while (server.hasPendingConnections()) {
            QTcpSocket* clientSocket = server.nextPendingConnection();
            if (clientSocket) {
                // Delegate the handling of this connection to the controller
                controller.handleNewConnection(clientSocket);
            }
        }
    });

    // Start listening for incoming connections
    if (!server.listen(QHostAddress::Any, 8080)) {
        qCritical() << "Unable to start the server:" << server.errorString();
        return -1;
    }

    qDebug() << "Server started, listening on port" << server.serverPort();

    return app.exec();
}
