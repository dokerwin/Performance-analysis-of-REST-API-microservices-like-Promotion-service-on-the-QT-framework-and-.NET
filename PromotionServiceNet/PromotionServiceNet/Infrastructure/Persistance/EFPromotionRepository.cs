using Microsoft.EntityFrameworkCore;
using PromotionServiceNet.Domain.Entities;
using PromotionServiceNet.Domain.Interfaces;
using PromotionServiceNet.Domain.ValueObjects;

namespace PromotionServiceNet.Infrastructure.Persistance;

public class EFPromotionRepository : IPromotionRepository
{
    private readonly EFContext _eFContext;

    private readonly DbSet<Promotion> _promotions;

    private readonly DbSet<Product> _products;

    public EFPromotionRepository(EFContext eFContext)
    {
        _eFContext = eFContext;
        _promotions = _eFContext.Set<Promotion>();
        _products = _eFContext.Set<Product>();
    }
    public async Task<bool> AddPromotion(Promotion promotion)
    {
        await _eFContext.AddAsync(promotion);

        return true;
    }

    public Task<bool> DeletePromotion(Promotion promotion)
    {
        throw new NotImplementedException();
    }

    public Task<Promotion> GetPromotionById(int id)
    {
        throw new NotImplementedException();
    }

    public async Task<List<Promotion>> GetPromotionsByFilter(Filter filter)
    {
        // Start with all promotions
        var query = _promotions
       .Include(p => p.AssociatedBaskets)
         .ThenInclude(basket => basket.AssociatedProducts) // Include AssociatedProducts of each PromoBasket
       .AsQueryable();

        // Apply filter criteria
        if (filter.IsActive)
        {
            query = query.Where(p => p.StartDate <= filter.CurrentDate && p.EndDate >= filter.CurrentDate);
        }

        // Execute the query and return the list of promotions
        return await query.ToListAsync();
    }


    public Task<bool> UpdatePromotion(Promotion promotion)
    {
        throw new NotImplementedException();
    }

    
}
