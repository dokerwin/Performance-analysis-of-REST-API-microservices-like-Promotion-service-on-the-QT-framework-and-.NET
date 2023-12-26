#ifndef PRODUCTDTO_H
#define PRODUCTDTO_H

#include <QString>

class ProductDto
{
public:
    ProductDto() = default;
    ProductDto(const int& id, const QString& name, int categoryType, double price, double quantity)
        : id(id), name(name), categoryType(categoryType), price(price), quantity(quantity) {}

    int getId() const { return id; }
    void setId(const int& value) { id = value; }

    QString getName() const { return name; }
    void setName(const QString& value) { name = value; }

    int getCategoryType() const { return categoryType; }
    void setCategoryType(int value) { categoryType = value; }

    double getPrice() const { return price; }
    void setPrice(double value) { price = value; }

    double getQuantity() const { return quantity; }
    void setQuantity(double value) { quantity = value; }

private:
    int id;
    QString name;
    int categoryType;
    double price;
    double quantity;
};

#endif // PRODUCTDTO_H
