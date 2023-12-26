#ifndef SQLITEPROMOTIONREPOSITORY_H
#define SQLITEPROMOTIONREPOSITORY_H

#include "include/domain/interfaces/IPromotionRepository.h"
#include "include/domain/model/Promotion.h"
#include "include/domain/model/PromoBasket.h"
#include "include/domain/model/PromoBasketProduct.h"
#include "include/domain/model/Filter.h"
#include <QSqlDatabase>

class SqlitePromotionRepository : public IPromotionRepository
{
public:
    SqlitePromotionRepository(const QSqlDatabase& databasePath);
    ~SqlitePromotionRepository();

    QFuture<bool> addPromotion(const Promotion& promotion) override;
    //QFuture<Promotion> getPromotionById(int id) override;
    QFuture<QList<Promotion>> getPromotionsByFilter(const Filter& filter) override;

private:
    QSqlDatabase db;
};

#endif // SQLITEPROMOTIONREPOSITORY_H
