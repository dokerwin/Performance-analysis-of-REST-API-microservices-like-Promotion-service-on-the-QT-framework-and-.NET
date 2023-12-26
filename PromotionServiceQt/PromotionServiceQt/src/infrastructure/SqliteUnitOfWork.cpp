#include "include/infrastructure/SqliteUnitOfWork.h"
#include <QtConcurrent>

SQLiteUnitOfWork::SQLiteUnitOfWork(const QString& databasePath)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databasePath);
    if (!db.open()) {
        // Handle database opening error
    }

    promotionRepository = new SqlitePromotionRepository(db);
}

SQLiteUnitOfWork::~SQLiteUnitOfWork()
{
    delete promotionRepository;
    db.close();
}

IPromotionRepository* SQLiteUnitOfWork::getPromotionRepository() const
{
    return promotionRepository;
}

QFuture<bool> SQLiteUnitOfWork::asyncCommit()
{
    return QtConcurrent::run([this]() {
        // Assuming you're using SQL transactions
        if (db.transaction()) {
            if (db.commit()) {
                return true;
            } else {
                db.rollback();
                return false;
            }
        }
        return false;
    });
}
