using PromotionServiceNet.Application.DTOs;
using PromotionServiceNet.Application.Mapper;
using PromotionServiceNet.Domain.Interfaces;
using PromotionServiceNet.Domain.ValueObjects;

namespace PromotionServiceNet.Application.UseCases.AddPromotionUseCase;

public class AddPromotionUseCase : IUseCase<PromotionDto, ResultValue<bool>>
{

    private readonly IUnitOfWork _unitOfWork;

    public AddPromotionUseCase(IUnitOfWork unitOfWork)
    {
        _unitOfWork = unitOfWork;
    }

    public async Task<ResultValue<bool>> execute(PromotionDto request)
    {

        var promo = PromotionMapper.MapToEntity(request);

        var added = await _unitOfWork.PromotionRepository.AddPromotion(promo);

        await _unitOfWork.AsyncCommit();

        return new() { Result = added };
    }
}
