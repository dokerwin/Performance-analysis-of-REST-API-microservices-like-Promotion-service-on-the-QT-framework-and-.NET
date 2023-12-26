using PromotionServiceNet.Application.DTOs;
using PromotionServiceNet.Domain.Entities;
using PromotionServiceNet.Domain.Enums;
using PromotionServiceNet.Domain.Interfaces;
using PromotionServiceNet.Domain.ValueObjects;

namespace PromotionServiceNet.Application.UseCases.GetPromotionForProducts
{
    public class GetPromotionForProductsUseCase : IUseCase<List<ProductDto>, DiscountDto>
    {

        private readonly IUnitOfWork _unitOfWork;

        public GetPromotionForProductsUseCase(IUnitOfWork unitOfWork)
        {
            _unitOfWork = unitOfWork;
        }

        public async Task<DiscountDto> execute(List<ProductDto> products)
        {
            var now = DateTime.Now;

            var filteredPromotions = await _unitOfWork.PromotionRepository.GetPromotionsByFilter(new Filter(true, now));

            var bestDiscounts = new Dictionary<int, ProductDiscount>();

            foreach (var promotion in filteredPromotions)
            {
                // Check if there's at least one basket in the promotion where all products match the DTO list
                // Initialize a list to hold matching baskets
                var matchingBaskets = new List<PromoBasket>();

                // Iterate through each basket in the associated baskets of the promotion
                foreach (var basket in promotion.AssociatedBaskets)
                {
                    // If all products matched, add the basket to the list of matching baskets
                    if (AllProductsExistInList(products, basket.AssociatedProducts))
                    {
                        matchingBaskets.Add(basket);
                    }
                }


                if (!matchingBaskets.Any())
                {
                    continue;
                }

                foreach (var product in products)
                {
                    decimal productDiscount = 0;

                    // Calculate discount only if the product is in a matching basket
                    if (matchingBaskets.Any(basket => basket.AssociatedProducts.Any(p => p.ProductId == product.Id)))
                    {
                        productDiscount = product.Price * promotion.DiscountValue / 100;

                        // Check if this is the best discount for this product
                        if (!bestDiscounts.ContainsKey(product.Id) || bestDiscounts[product.Id].Discount < productDiscount)
                        {
                            bestDiscounts[product.Id] = new ProductDiscount
                            {
                                OriginalPrice = Math.Round(product.Price, 2),
                                Discount = Math.Round(productDiscount, 2),
                                SellingPrice = Math.Round(product.Price - productDiscount, 2),
                                DiscountName = promotion.Description,
                                ProductId = product.Id,
                                PromotionId = promotion.Id,
                            };
                        }
                    }
                }
            }

            return new DiscountDto() { discounts = bestDiscounts.Values.ToList() };
        }

        private bool AllProductsExistInList(List<ProductDto> products, ICollection<PromoBasketProduct> associatedProducts)
        {
            foreach (var associatedProduct in associatedProducts)
            {
                // Find a matching product in the products list based on ProductID and Quantity
                var matchingProduct = products.FirstOrDefault(p =>
                    p.Id == associatedProduct.ProductId &&
                    p.Quantity == associatedProduct.Quantity);

                // If no matching product is found, return false
                if (matchingProduct == null)
                {
                    return false;
                }
            }

            // All associated products exist in the products list
            return true;
        }
    }
}