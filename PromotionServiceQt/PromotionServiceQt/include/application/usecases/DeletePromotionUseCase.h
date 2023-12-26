#ifndef GETPROMOTIONFORPRODUCTSUSECASE_H
#define GETPROMOTIONFORPRODUCTSUSECASE_H

#include <QList>
#include <QFuture>
#include "include/domain/interfaces/IUnitOfWork.h"
#include "include/application/dto/ProductDto.h"
#include "include/application/dto/DiscountDto.h"
#include "include/domain/model/ProductDiscount.h"
#include "include/domain/enums/PromotionType.h"
#include "include/domain/model/Product.h"
#include <QDateTime>
#include <QList>
#include <QMap>
#include <QtConcurrent/QtConcurrent>
#include <memory>

class GetPromotionForProductsUseCase {
public:
    GetPromotionForProductsUseCase(std::shared_ptr<IUnitOfWork> unitOfWork)
        : unitOfWork(unitOfWork) {}

    QFuture<DiscountDto> execute(const QList<ProductDto>& products) {
        return QtConcurrent::run(this, &GetPromotionForProductsUseCase::calculateDiscount, products);
    }

private:
    std::shared_ptr<IUnitOfWork> unitOfWork;

    DiscountDto calculateDiscount(const QList<ProductDto>& products) {
        QDateTime now = QDateTime::currentDateTime();

        auto filteredPromotions = unitOfWork->getPromotionRepository()->getPromotionsByFilter(Filter(true, now)).result();
        QHash<int, ProductDiscount> bestDiscounts; // Changed from QMap to QHash for better performance in some cases
        for (const auto& promotion : filteredPromotions) {
            // Check if there's at least one basket in the promotion where all products match the DTO list
            // Initialize a list to hold matching baskets
            QList<PromoBasket> matchingBaskets;

            for (const auto& basket : promotion.getAssociatedBaskets()) {
                // If all products matched, add the basket to the list of matching baskets
                if (allProductsExistInList(products, basket.getAssociatedProducts())) {
                    matchingBaskets.append(basket);
                }
            }

            if (matchingBaskets.isEmpty()) {
                continue;
            }

            for (const auto& product : products) {
                double productDiscount = 0.0;

                // Calculate discount only if the product is in a matching basket
                for (const auto& basket : matchingBaskets) {
                    for (const auto& p : basket.getAssociatedProducts()) {
                        if (p.getId() == product.getId()) {
                            productDiscount = product.getPrice() * promotion.getDiscountValue() / 100.0;

                            // Check if this is the best discount for this product
                            if (!bestDiscounts.contains(product.getId()) || bestDiscounts[product.getId()].getDiscount() < productDiscount) {
                                bestDiscounts[product.getId()] = ProductDiscount(
                                            product.getId(),
                                            promotion.getId(),
                                            promotion.getDescription(),
                                            std::round(productDiscount * 100) / 100,
                                            std::round(product.getPrice() * 100) / 100,
                                            qRound((product.getPrice() - productDiscount) * 100) / 100.0,
                                            product.getQuantity()
                                            );
                            }
                        }
                    }
                }
            }

        }
            DiscountDto discountDto;
            for (const auto& discount : bestDiscounts) {
                discountDto.addDiscount(discount);
            }
            return discountDto;
        }



        bool allProductsExistInList(QList<ProductDto> products, QList<PromoBasketProduct> associatedProducts) {
            for (const auto& associatedProduct : associatedProducts) {
                // Find a matching product in the products list based on ProductID and Quantity
                bool matchingProductFound = false;
                for (const auto& product : products) {
                    if (product.getId() == associatedProduct.getId() && product.getId() == associatedProduct.getQuantity()) {
                        matchingProductFound = true;
                        break;
                    }
                }

                // If no matching product is found, return false
                if (!matchingProductFound) {
                    return false;
                }
            }

            // All associated products exist in the products list
            return true;
        }

    };
    
#endif // GETPROMOTIONFORPRODUCTSUSECASE_H
    
