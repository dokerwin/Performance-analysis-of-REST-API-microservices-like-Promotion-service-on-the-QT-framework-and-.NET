using Microsoft.EntityFrameworkCore;
using PromotionServiceNet.Domain.Entities;

namespace PromotionServiceNet.Infrastructure.Persistance
{
    public class EFContext : DbContext
    {
        private readonly IConfiguration _configuration;
        public EFContext(DbContextOptions<EFContext> dbContextOptions, IConfiguration configuration)
               : base()
        {
            _configuration = configuration;
        }

        public virtual DbSet<Promotion> Promotions { get; set; }
        public virtual DbSet<Product> Products { get; set; }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.ApplyConfigurationsFromAssembly(typeof(EFContext).Assembly);
        }


        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseSqlite(_configuration.GetConnectionString("PromoService_ConnectionString"));
        }
    }
}
