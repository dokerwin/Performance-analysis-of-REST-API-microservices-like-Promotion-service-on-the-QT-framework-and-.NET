using PromotionServiceNet.Domain.ValueObjects.Base;

namespace PromotionServiceNet.Domain.ValueObjects;

public class ProductDiscount : ValueObject
{
    public int ProductId { get; set; }
    public int PromotionId { get; set; }
    public string DiscountName { get; set; }
    public decimal OriginalPrice { get; set; }
    public decimal Discount { get; set; }
    public decimal SellingPrice { get; set; }
}
