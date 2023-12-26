#ifndef SQLITEUNITOFWORK_H
#define SQLITEUNITOFWORK_H

#include "include/domain/interfaces/IPromotionRepository.h"
#include "include/domain/interfaces/IUnitOfWork.h"
#include "include/infrastructure/SqlitePromotionRepositroy.h"
#include <QSqlDatabase>

class SQLiteUnitOfWork : public IUnitOfWork
{
public:
    SQLiteUnitOfWork(const QString& databasePath);
    ~SQLiteUnitOfWork();

    IPromotionRepository* getPromotionRepository() const override;
    QFuture<bool> asyncCommit() override;

private:
    QSqlDatabase db;
    SqlitePromotionRepository* promotionRepository;
};

#endif // SQLITEUNITOFWORK_H
