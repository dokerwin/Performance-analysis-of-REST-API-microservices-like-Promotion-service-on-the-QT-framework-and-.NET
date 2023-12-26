#ifndef DISCOUNTDTO_H
#define DISCOUNTDTO_H

#include <QList>
#include "include/domain/model/ProductDiscount.h"

class DiscountDto
{
public:
    DiscountDto() = default;
    explicit DiscountDto(const QList<ProductDiscount> &discounts) : discounts(discounts) {}

    const QList<ProductDiscount> &getDiscounts() const { return discounts; }
    void setDiscounts(const QList<ProductDiscount> &value) { discounts = value; }

    void addDiscount(const ProductDiscount &discount) { discounts.append(discount); }

private:
    QList<ProductDiscount> discounts;
};

#endif // DISCOUNTDTO_H
