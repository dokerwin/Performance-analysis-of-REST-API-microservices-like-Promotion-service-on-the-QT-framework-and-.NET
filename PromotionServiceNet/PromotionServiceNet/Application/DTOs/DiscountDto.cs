using PromotionServiceNet.Domain.ValueObjects.Base;
using PromotionServiceNet.Domain.ValueObjects;

namespace PromotionServiceNet.Application.DTOs;

public class DiscountDto
{
    public List<ProductDiscount> discounts = new List<ProductDiscount>();
}
