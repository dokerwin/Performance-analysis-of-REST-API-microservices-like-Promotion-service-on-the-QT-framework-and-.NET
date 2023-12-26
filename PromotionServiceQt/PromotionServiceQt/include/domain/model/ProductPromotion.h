#ifndef PRODUCTPROMOTION_H
#define PRODUCTPROMOTION_H

class ProductPromotion
{
public:
    ProductPromotion() = default;
    ProductPromotion(const int& productId, const int& promotionId, int quantity)
        : ProductId(productId), PromotionId(promotionId), Quantity(quantity) {}

    int getPromotionId() const { return PromotionId; }
    int getProductId() const { return ProductId; }
    int getQuantity() const { return Quantity; }

private:
    int ProductId;
    int PromotionId;
    int Quantity;
};

#endif // PRODUCTPROMOTION_H
