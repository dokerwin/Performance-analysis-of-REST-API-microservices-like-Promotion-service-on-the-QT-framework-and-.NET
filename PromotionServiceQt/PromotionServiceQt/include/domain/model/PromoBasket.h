#ifndef PROMOBASKET_H
#define PROMOBASKET_H

#include <QList>
#include "include/domain/model/base/Entity.h"
#include "include/domain/enums/BasketType.h" // Assuming BasketType is an enum similar to C#'s BasketType
#include "PromoBasketProduct.h" // Assuming PromoBasketProduct is already defined

class PromoBasket : public Entity
{
public:
    explicit PromoBasket(int id = -1,
                         BasketType basketType = BasketType::AllItems)
        : Entity(id), // Initialize the base Entity class with id
          m_basketType(basketType)
    {
    }

    // Getter for BasketType
    BasketType getBasketType() const { return m_basketType; }

    // Setter for BasketType
    void setBasketType(BasketType basketType) { m_basketType = basketType; }

    // Getter for AssociatedProducts
    QList<PromoBasketProduct> getAssociatedProducts() const { return m_associatedProducts; }

    // Getter for AssociatedProducts
    void addAssociatedProduct(PromoBasketProduct & product) { m_associatedProducts.append(product); }

private:
    BasketType m_basketType;
    QList<PromoBasketProduct> m_associatedProducts;
};

#endif // PROMOBASKET_H
