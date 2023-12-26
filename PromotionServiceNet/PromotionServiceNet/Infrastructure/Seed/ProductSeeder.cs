using PromotionServiceNet.Domain.Entities;

namespace PromotionService.EntityFramework.Seed;

public static class ProductSeeder
{
    private static readonly Random random = new Random();
    private static readonly string[] predefinedCategories = new string[]
    {
        "Electronics", "Clothing", "Groceries", "Books", "Toys",
        "Home & Garden", "Sports", "Automotive", "Beauty & Health",
        "Music", "Office Supplies", "Pets", "Baby Products", "Jewelry",
        "Footwear", "Gourmet Foods", "Travel", "Art Supplies", "Gardening",
        "Photography","Bakery", "Dairy", "Confectionery", "Snacks", "Frozen Foods",
        "Meat & Poultry", "Seafood", "Fruits", "Vegetables", "Cereals",
        "Pasta & Noodles", "Delicatessen", "Health Foods", "Beverages",
        "Spices & Herbs", "Canned Goods", "Gourmet Foods", "Organic Foods",
        "Gluten-Free Foods", "Vegan Foods"
    };

    public static List<Product> GenerateRandomProducts(int numberOfProducts)
    {
        var products = new List<Product>();

        for (int i = 1; i <= numberOfProducts; i++)
        {
            var product = new Product
            {
                Id = i,
                Name = $"Product {i}",
                Category = predefinedCategories[random.Next(predefinedCategories.Length)],
                Price = Math.Round((decimal)(random.NextDouble() * 1000.0), 2) // Random price between 0 and 1000, rounded to 2 decimal places
            };

            products.Add(product);
        }

        return products;
    }
}
