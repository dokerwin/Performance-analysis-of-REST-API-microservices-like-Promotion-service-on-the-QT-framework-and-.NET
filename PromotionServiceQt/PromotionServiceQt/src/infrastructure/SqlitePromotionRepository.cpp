#include "include/infrastructure/SqlitePromotionRepositroy.h"
#include <QtConcurrent>
#include <QSqlQuery>
#include <QVariant>

SqlitePromotionRepository::SqlitePromotionRepository(const QSqlDatabase& database)
{
    db = database;
}

SqlitePromotionRepository::~SqlitePromotionRepository()
{
    db.close();
}

QFuture<bool> SqlitePromotionRepository::addPromotion(const Promotion& promotion) {
    return QtConcurrent::run([=]() {
        QSqlQuery query(db);
        query.prepare("INSERT INTO promotions (description, startDate, endDate, discountValue, type) VALUES (:description, :startDate, :endDate, :discountValue, :type)");
        query.bindValue(":description", promotion.getDescription());
        query.bindValue(":startDate", promotion.getStartDate());
        query.bindValue(":endDate", promotion.getEndDate());
        query.bindValue(":discountValue", promotion.getDiscountValue());
        query.bindValue(":type", static_cast<int>(promotion.getType())); // Assuming PromotionType is an enum

        return query.exec();
    });
}

//QFuture<Promotion> SqlitePromotionRepository::getPromotionById(int id) {
//    return QtConcurrent::run([=]() -> Promotion {
//        QSqlQuery query(db);
//        query.prepare("SELECT * FROM promotions WHERE id = :id");
//        query.bindValue(":id", id);
//        if (query.exec() && query.next()) {
//            // Assuming Promotion has a constructor that takes these values
//            return Promotion(
//                query.value("id").toInt(),
//                query.value("description").toString(),
//                query.value("startDate").toDateTime(),
//                query.value("endDate").toDateTime(),
//                query.value("discountValue").toDouble(),
//                static_cast<PromotionType>(query.value("type").toInt())
//            );
//        }
//    });
//}

QFuture<QList<Promotion>> SqlitePromotionRepository::getPromotionsByFilter(const Filter& filter) {
     return QtConcurrent::run([this, filter]() -> QList<Promotion> {
        QList<Promotion> promotions;
        QSqlQuery query(db);

        // Query for promotions, associated baskets, and products in one go
        query.prepare(R"(
            SELECT
                p.Id AS pId, p.Description, p.StartDate, p.EndDate, p.DiscountValue, p.Type,
                pb.Id AS pbId, pb.BasketType,
                pbp.Id AS pbpId, pbp.ProductId, pbp.Quantity
            FROM Promotions p
            LEFT JOIN PromoBasket pb ON p.Id = pb.PromotionId
            LEFT JOIN PromoBasketProduct pbp ON pb.Id = pbp.BasketId
            WHERE :CurrentDate BETWEEN p.StartDate AND p.EndDate
        )");
        query.bindValue(":CurrentDate", filter.getCurrentDate());

        if (query.exec()) {
            QMap<int, Promotion> promotionMap; // Temporarily store promotions by their IDs

            while (query.next()) {
                int promotionId = query.value("pId").toInt();

                // Check if the promotion is already created
                if (!promotionMap.contains(promotionId)) {
                    //const int promoId, const QString& description, const QDateTime& startDate, const QDateTime& endDate, double discountValue, PromotionType type

                    Promotion promotion(
                        promotionId,
                        query.value("Description").toString(),
                        query.value("StartDate").toDateTime(),
                        query.value("EndDate").toDateTime(),
                        query.value("DiscountValue").toDouble(),
                        static_cast<PromotionType>(query.value("Type").toInt())
                        // Include other fields as necessary
                    );
                    promotionMap.insert(promotionId, promotion);
                }

                // Process baskets and products
                int basketId = query.value("pbId").toInt();
                if (basketId != 0) { // Check if there's an associated basket
                    PromoBasket basket(
                        basketId,
                        static_cast<BasketType>(query.value("BasketType").toInt())
                        // ... other basket fields ...
                    );

                    // Add product to basket
                    int productId = query.value("ProductId").toInt();
                    if (productId != 0) { // Check if there's an associated product
                        PromoBasketProduct product(
                            query.value("pbpId").toInt(),
                            productId,
                            basketId,
                            query.value("Quantity").toInt()
                            // ... other product fields ...
                        );
                        basket.addAssociatedProduct(product); // Assuming PromoBasket has an addAssociatedProduct method
                    }

                    // Add basket to promotion
                    promotionMap[promotionId].addAssociatedBasket(basket); // Assuming Promotion has an addAssociatedBasket method
                }
            }

            // Convert the map to a list
            promotions = promotionMap.values();
        }

        return promotions;
    });
}
