using PromotionServiceNet.Domain.Interfaces;

namespace PromotionServiceNet.Infrastructure.Persistance;

public class EFUnitOfWork : IUnitOfWork
{
    private readonly EFContext _context;

    public EFUnitOfWork(IPromotionRepository PromotionRepository, EFContext context)
    {
        this.PromotionRepository = PromotionRepository;
        _context = context;
    }
    public IPromotionRepository PromotionRepository { get; private set; }

    public async Task<bool> AsyncCommit()
    {
        return await _context.SaveChangesAsync() > 0;
    }
}
