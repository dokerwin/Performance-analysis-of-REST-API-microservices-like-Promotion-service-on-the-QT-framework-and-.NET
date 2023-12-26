using PromotionServiceNet.Domain.Entities.Base;
using PromotionServiceNet.Domain.ValueObjects;

namespace PromotionServiceNet.Domain.Entities;

public class PromoBasketProduct : Entity<int>
{
    public int BasketId { get; private set; }
    public int ProductId { get; private set; }
    public int Quantity { get; private set; }

    private PromoBasketProduct() { }

    public PromoBasketProduct(int productId, int basketId, int quantity)
    {
        BasketId = basketId;
        ProductId = productId;
        Quantity = quantity;
    }
}
