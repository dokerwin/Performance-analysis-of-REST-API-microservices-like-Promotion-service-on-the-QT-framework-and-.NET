using PromotionServiceNet.Application.DTOs;

public class ProductPromotionDto
{
    public Guid PromotionId { get; private set; }
    public PromotionDto Promotion { get; private set; }
    public Guid ProductId { get; private set; }
    public ProductDto Product { get; private set; }
    public int Quantity { get; private set; }

}
