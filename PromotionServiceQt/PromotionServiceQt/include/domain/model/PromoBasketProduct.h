#ifndef PROMOBASKETPRODUCT_H
#define PROMOBASKETPRODUCT_H

#include "include/domain/model/base/Entity.h"



class PromoBasketProduct : public Entity
{
public:
    // Constructor for PromoBasketProduct
    PromoBasketProduct(int promoBasketProductId, int productId, int basketId, int quantity)
         : Entity (promoBasketProductId), // Call the base Entity class constructor if needed
          m_basketId(basketId),
          m_productId(productId),
          m_quantity(quantity)
    {
    }

    // Getter for BasketId
    int getBasketId() const { return m_basketId; }

    // Getter for ProductId
    int getProductId() const { return m_productId; }

    // Getter for Quantity
    int getQuantity() const { return m_quantity; }

    // Note: Setters are not provided as the properties are private and not intended to be changed after construction.

private:
    int m_basketId;
    int m_productId;
    int m_quantity;
};

#endif // PROMOBASKETPRODUCT_H
