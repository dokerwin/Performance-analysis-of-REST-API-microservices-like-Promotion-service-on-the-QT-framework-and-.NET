using PromotionServiceNet.Domain.Entities.Base;
using PromotionServiceNet.Domain.Enums;

namespace PromotionServiceNet.Domain.Entities
{
    public class PromoBasket : Entity<int>
    {
        public BasketType BasketType { get; set; }

        public ICollection<PromoBasketProduct> AssociatedProducts { get; set; } = new List<PromoBasketProduct>();

        private PromoBasket()
        {
            AssociatedProducts = new List<PromoBasketProduct>();
        }

        public PromoBasket(int id, BasketType basketType, List<PromoBasketProduct> promoBasketProducts)
            : this()
        {
            Id = id;
            BasketType = basketType;
            AssociatedProducts = promoBasketProducts;
        }

        public void AddAssociatedProduct(int productId, int quantity)
        {
            var productPromotion = new PromoBasketProduct(productId, this.Id,  quantity);
            AssociatedProducts.Add(productPromotion);
        }

    }
}
