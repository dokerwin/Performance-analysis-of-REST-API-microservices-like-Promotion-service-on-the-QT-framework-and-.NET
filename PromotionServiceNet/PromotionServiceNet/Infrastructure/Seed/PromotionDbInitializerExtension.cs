using PromotionServiceNet.Infrastructure.Persistance;


namespace PromotionService.EntityFramework.Seed;

public static class PromotionDbInitializerExtension
{
    public static IApplicationBuilder UseItToSeedDb(this IApplicationBuilder app)
    {
        ArgumentNullException.ThrowIfNull(app, nameof(app));

        using var scope = app.ApplicationServices.CreateScope();
        var services = scope.ServiceProvider;
  
            var context = services.GetRequiredService<EFContext>();
            PromotionServiceDbInitializer.Initialize(context);


        return app;
    }
}
