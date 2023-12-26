namespace PromotionServiceNet.Domain.Interfaces;

public interface IUnitOfWork
{
    IPromotionRepository PromotionRepository { get; }
    public Task<bool> AsyncCommit();
}
