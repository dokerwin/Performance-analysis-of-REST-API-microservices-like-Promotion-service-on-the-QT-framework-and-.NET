using PromotionServiceNet.Domain.Entities.Base;
using PromotionServiceNet.Domain.ValueObjects.Base;

namespace PromotionServiceNet.Domain.Entities;

public class Product : Entity<int>
{
    public int Id { get; set; }
    public string? Name { get; set; }
    public string? Category { get; set; }
    public decimal Price { get; set; }

}
