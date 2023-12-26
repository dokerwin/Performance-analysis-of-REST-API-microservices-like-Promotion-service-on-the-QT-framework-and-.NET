using PromotionServiceNet.Application.DTOs;
using PromotionServiceNet.Domain.Entities;

namespace PromotionServiceNet.Application.Mapper;

internal class PromotionMapper
{
    internal static Promotion MapToEntity(PromotionDto request)
    {
        var promo =  new Promotion(request.Id, request.Description,request.StartDate,request.EndDate, request.DiscountValue, request.Type);

        //foreach (var assosProd in request.AssociatedBaskets)
        //    promo.AddPromoBasket(assosProd.ProductId, assosProd.Quantity);

        return promo;
    }
}