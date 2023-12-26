#ifndef PRODUCTDISCOUNT_H
#define PRODUCTDISCOUNT_H

#include <QString>

class ProductDiscount
{
public:
    ProductDiscount() = default;
    ProductDiscount(int const productId, int const promotionId, QString discountName,
                    double discount, double originalPrice, double sellingPrice, double quantity)
        : ProductId(productId), PromotionId(promotionId), DiscountName(discountName), Discount(discount),
          OriginalPrice(originalPrice), SellingPrice(sellingPrice), Quantity(quantity) {}

    int getProductId() const { return ProductId; }
    void setProductId(const int& value) { ProductId = value; }

    int getPromotionId() const { return PromotionId; }
    void setPromotionId(const int& value) { PromotionId = value; }

    QString getDiscountName() const { return DiscountName; }
    void setDiscountName(const QString& value) { DiscountName = value; }

    double getDiscount() const { return Discount; }
    void setDiscount(double value) { Discount = value; }

    double getSellingPrice() const { return SellingPrice; }
    void setSellingPrice(double value) { SellingPrice = value; }

    double getOriginalPrice() const { return OriginalPrice; }
    void setOriginalPrice(double value) { OriginalPrice = value; }


    double getQuantity() const { return Quantity; }
    void setQuantity(double value) { Quantity = value; }

private:
    int ProductId;
    int PromotionId;
    QString DiscountName;
    double Discount;
    double OriginalPrice;
    double SellingPrice;
    double Quantity;
};

#endif // PRODUCTDISCOUNT_H
