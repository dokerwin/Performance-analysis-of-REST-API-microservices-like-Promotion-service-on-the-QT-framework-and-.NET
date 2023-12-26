using PromotionServiceNet.Domain.Entities;
using PromotionServiceNet.Domain.Enums;

namespace PromotionServiceNet.Application.DTOs
{
    public class PromotionDto
    {
        public int Id { get; set; }
        public string Description { get; private set; }
        public DateTime StartDate { get; private set; }
        public DateTime EndDate { get; private set; }
        public decimal DiscountValue { get; private set; }
        public PromotionType Type { get; private set; }
        public ICollection<PromoBasket> AssociatedBaskets { get; private set; }
    }
}
