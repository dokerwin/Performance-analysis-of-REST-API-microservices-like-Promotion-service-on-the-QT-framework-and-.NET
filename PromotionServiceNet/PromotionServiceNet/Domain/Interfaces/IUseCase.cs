using PromotionServiceNet.Domain.ValueObjects;

namespace PromotionServiceNet.Domain.Interfaces;

public interface IUseCase<IRequest, IResponse>
{
   Task<IResponse> execute(IRequest request);
}