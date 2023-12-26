#ifndef PROMOTION_H
#define PROMOTION_H

#include <QString>
#include <QDateTime>
#include <QList>
#include "include/domain/model/base/Entity.h"
#include "include/domain/enums/PromotionType.h"
#include "include/domain/model/PromoBasket.h"

class Promotion : public Entity
{
public:

    Promotion(const int promoId, const QString& description, const QDateTime& startDate, const QDateTime& endDate, double discountValue, PromotionType type)
        : Entity(promoId), Description(description), StartDate(startDate), EndDate(endDate), DiscountValue(discountValue), Type(type) {}

    Promotion() : Entity(0), DiscountValue(0.0), Type(PromotionType::PercentageDiscount) {}

    QString getDescription() const { return Description; }
    QDateTime getStartDate() const { return StartDate; }
    QDateTime getEndDate() const { return EndDate; }
    double getDiscountValue() const { return DiscountValue; }
    PromotionType getType() const { return Type; }
    const QList<PromoBasket>& getAssociatedBaskets() const { return AssociatedBaskets; }


    void addAssociatedBasket(const PromoBasket& basket) { AssociatedBaskets.append(basket); }
    void update(const QString& description, const QDateTime& startDate, const QDateTime& endDate, double discountValue, PromotionType type);
    void removeAssociatedProduct(const int& productId);
    bool isActive() const;

private:
    QString Description;
    QDateTime StartDate;
    QDateTime EndDate;
    double DiscountValue;
    PromotionType Type;
    QList<PromoBasket> AssociatedBaskets;
};

#endif // PROMOTION_H
