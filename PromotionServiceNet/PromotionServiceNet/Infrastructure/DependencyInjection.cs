using Microsoft.EntityFrameworkCore;
using PromotionServiceNet.Domain.Interfaces;
using PromotionServiceNet.Infrastructure.Persistance;

namespace UserService.Infrastructure;
public static class DependencyInjection
{
    public static IServiceCollection AddEntityFramework(this IServiceCollection services, IConfiguration Configuration)
    {
        services.AddDbContext<EFContext>(
        optionsAction => optionsAction.UseSqlite(Configuration.GetConnectionString("PromoService_ConnectionString")));
        return services;
    }

    public static IServiceCollection AddInfrastructure(this IServiceCollection services)
    {
        services.AddRepositorises();
        return services;
    }

    private static IServiceCollection AddRepositorises(this IServiceCollection services)
    {
        services.AddScoped<IUnitOfWork, EFUnitOfWork>();
        services.AddScoped<IPromotionRepository, EFPromotionRepository>();

        return services;
    }
}