using PromotionServiceNet.Domain.ValueObjects.Base;

namespace PromotionServiceNet.Domain.ValueObjects;

public class Discount : ValueObject
{
   public List<ProductDiscount> discounts = new List<ProductDiscount>();

}
