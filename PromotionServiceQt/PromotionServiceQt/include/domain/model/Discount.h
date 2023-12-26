#ifndef DISCOUNT_H
#define DISCOUNT_H

#include <QVector>
#include "base/ValueObject.h" // Assuming ValueObject is a class you've defined
#include "ProductDiscount.h" // Assuming ProductDiscount is a class you've defined

class Discount : public ValueObject
{
public:
    Discount() = default;
    ~Discount() = default;

    const QVector<ProductDiscount>& getDiscounts() const { return discounts; }
    void addDiscount(const ProductDiscount& discount) { discounts.append(discount); }

private:
    QVector<ProductDiscount> discounts;
};

#endif // DISCOUNT_H
