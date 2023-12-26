#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>
#include "base/ValueObject.h"
#include "include/domain/model/base/Entity.h"

class Product : public Entity
{
public:
    Product(const int& id, const QString& name, const QString& category, double price, double quantity)
        : Entity(id), Name(name), Category(category), Price(price), Quantity(quantity) {}


    QString getName() const { return Name; }
    void setName(const QString& value) { Name = value; }

    QString getCategory() const { return Category; }
    void setCategory(const QString& value) { Category = value; }

    double getPrice() const { return Price; }
    void setPrice(double value) { Price = value; }

    double getQuantity() const { return Quantity; }
    void setQuantity(double value) { Quantity = value; }

private:
    QString Name;
    QString Category;
    double Price;
    double Quantity;
};

#endif // PRODUCT_H
