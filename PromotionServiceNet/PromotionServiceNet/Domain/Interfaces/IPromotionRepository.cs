using PromotionServiceNet.Domain.Entities;
using PromotionServiceNet.Domain.ValueObjects;

namespace PromotionServiceNet.Domain.Interfaces;

public interface IPromotionRepository
{
   Task<bool> AddPromotion(Promotion promotion);
   Task<bool> DeletePromotion(Promotion promotion);
   Task<bool> UpdatePromotion(Promotion promotion);
   Task<Promotion> GetPromotionById(int id);
   Task<List<Promotion>> GetPromotionsByFilter(Filter filter);
}
