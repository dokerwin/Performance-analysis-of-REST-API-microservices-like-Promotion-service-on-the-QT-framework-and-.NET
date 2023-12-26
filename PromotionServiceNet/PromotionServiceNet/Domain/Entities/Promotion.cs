using PromotionServiceNet.Domain.Entities.Base;
using PromotionServiceNet.Domain.Enums;

namespace PromotionServiceNet.Domain.Entities
{
    public class Promotion : Entity<int>
    {
        public string Description { get; private set; }
        public DateTime StartDate { get; private set; }
        public DateTime EndDate { get; private set; }
        public decimal DiscountValue { get; private set; }
        public PromotionType Type { get; private set; }
        public ICollection<PromoBasket> AssociatedBaskets { get; set; } = new List<PromoBasket>();

        private Promotion()
        {
            AssociatedBaskets = new List<PromoBasket>();
        }

        public Promotion(int id, string description, DateTime startDate, DateTime endDate, decimal discountValue, PromotionType type)
            : this()
        {
            Id = id;
            Description = description;
            StartDate = startDate;
            EndDate = endDate;
            DiscountValue = discountValue;
            Type = type;
        }

        public void AddPromoBasket(int id, List <PromoBasketProduct> promoBasketProducts)
        {
            var productBasket = new PromoBasket( id, BasketType.AllItems, promoBasketProducts);
            AssociatedBaskets.Add(productBasket);
        }

        public bool IsActive()
        {
            var now = DateTime.Now;
            return StartDate <= now && now <= EndDate;
        }
    }
}
