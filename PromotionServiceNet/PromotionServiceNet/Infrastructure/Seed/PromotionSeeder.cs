//using PromotionServiceNet.Domain.Entities;
//using PromotionServiceNet.Domain.Enums;

//namespace PromotionService.EntityFramework.Seed;

//public class PromotionSeeder
//{
//    public static List<Promotion> GetPromotions()
//    {



//        return new List<Promotion>()
//        {
//            // Sample Promotion 1: Percentage Discount
//            new Promotion( 1, "1% Off Fruits", DateTime.Now.AddDays(-1), DateTime.Now.AddDays(30), 1.0M, PromotionType.PercentageDiscount)
//            {
//                AssociatedProducts = new List<ProductPromotion>()
//                {
//                   new ProductPromotion(
//                       1,1,
//                       /*qt*/ 1)
//                   {

//                   }
//                }
//            },

//            // Sample Promotion 1: Percentage Discount
//            new Promotion(2, "10% Off Electronics", DateTime.Now.AddDays(-1), DateTime.Now.AddDays(30), 10.0M, PromotionType.PercentageDiscount)
//            {
//                AssociatedProducts = new List<ProductPromotion>()
//                {
//                   new ProductPromotion(
//                      2,2,
//                       /*qt*/ 1)
//                   {

//                   }
//                }
//            },

//            // Sample Promotion 1: Percentage Discount
//            new Promotion(3, "2% Off Electronics for 2", DateTime.Now.AddDays(-1), DateTime.Now.AddDays(30), 2.0M, PromotionType.PercentageDiscount)
//            {
//                AssociatedProducts = new List<ProductPromotion>()
//                {
//                   new ProductPromotion(
//                        productId: 3,
//                        promotionId: 3,
//                       /*qt*/ 2)
//                   {

//                   }
//                }
//            },
//                        // Sample Promotion 1: Percentage Discount
//            new Promotion(4, "15% Off Electronics for 2", DateTime.Now.AddDays(-1), DateTime.Now.AddDays(30), 15.0M, PromotionType.PercentageDiscount)
//            {
//                AssociatedProducts = new List<ProductPromotion>()
//                {
//                   new ProductPromotion(
//                      4,4,
//                       /*qt*/ 2)
//                   {

//                   }
//                }
//            },

//                        // Sample Promotion 1: Percentage Discount
//            new Promotion(5,"50% Off Electronics for 3", DateTime.Now.AddDays(-1), DateTime.Now.AddDays(30), 50.0M, PromotionType.PercentageDiscount)
//            {
//                Id = 5,
//                AssociatedProducts = new List<ProductPromotion>()
//                {
//                   new ProductPromotion(
//                       5, 
//                       5,
//                       3)
//                   {

//                   }
//                }
//            },
//                        // Sample Promotion 1: Percentage Discount
//            new Promotion(6, "70% Off Electronics for 10", DateTime.Now.AddDays(-1), DateTime.Now.AddDays(30), 70.0M, PromotionType.PercentageDiscount)
//            {
//                AssociatedProducts = new List<ProductPromotion>()
//                {
//                   new ProductPromotion(
//                      6, 6,
//                       /*qt*/ 10)
//                   {

//                   }
//                }
//            }


//        };
//    }
//}

using PromotionServiceNet.Domain.Entities;
using PromotionServiceNet.Domain.Enums;

namespace PromotionService.EntityFramework.Seed;
public static class PromotionSeeder
{
    private static readonly Random random = new Random();

    public static List<Promotion> GetPromotions()
    {
        var promotions = new List<Promotion>();

        int basketId = 1; // Initialize outside the promotions loop

        for (int i = 1; i <= 500; i++)
        {
            var discount = random.Next(1, 100); // Random discount between 1% and 99%
            var daysToAdd = random.Next(-30, 31); // Random start date between -30 and +30 days from now
            var duration = random.Next(1, 60); // Random duration between 1 and 60 days

            var baskets = new List<PromoBasket>();
            var basketQt = random.Next(1, 10); // Random number of baskets

            for (int j = 1; j <= basketQt; j++)
            {
                var products = new List<PromoBasketProduct>();
                var productQt = random.Next(1, 15); // Random number of products in basket

                for (int k = 1; k <= productQt; k++)
                {
                    products.Add(new PromoBasketProduct(random.Next(1, 1000), basketId, random.Next(1, 15)));
                }

                baskets.Add(new PromoBasket(basketId++, BasketType.AllItems, products)); // Use and increment basketId
            }

            var promotion = new Promotion(
                i,
                $"{discount}% Off Random Product",
                DateTime.Now.AddDays(daysToAdd),
                DateTime.Now.AddDays(daysToAdd + duration),
                discount,
                PromotionType.PercentageDiscount)
            {
                AssociatedBaskets = baskets
            };

            promotions.Add(promotion);
        }

        return promotions;
    }
}
