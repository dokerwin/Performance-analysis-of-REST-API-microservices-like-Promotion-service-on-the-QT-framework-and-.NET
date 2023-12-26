using Microsoft.EntityFrameworkCore;
using PromotionServiceNet.Infrastructure.Persistance;

namespace PromotionService.EntityFramework.Seed;
public class PromotionServiceDbInitializer
{
    public static void Initialize(EFContext dbContext)
    {
        if (dbContext.Database.CanConnect())
        {
            if (!dbContext.Promotions.Any())
            {
             
                dbContext.Products.RemoveRange(dbContext.Products);
                dbContext.Products.AddRange(ProductSeeder.GenerateRandomProducts(1000));
                dbContext.Promotions.RemoveRange(dbContext.Promotions);
                dbContext.Promotions.AddRange(PromotionSeeder.GetPromotions());
                dbContext.SaveChanges();
            }

            dbContext.SaveChanges();
        }
    }
}
