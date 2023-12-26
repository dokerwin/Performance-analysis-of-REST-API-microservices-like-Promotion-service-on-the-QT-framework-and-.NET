using Microsoft.AspNetCore.Mvc;
using PromotionServiceNet.Application.DTOs;
using PromotionServiceNet.Application.UseCases.AddPromotionUseCase;
using PromotionServiceNet.Application.UseCases.GetPromotionForProducts;
using PromotionServiceNet.Domain.Interfaces;

// For more information on enabling Web API for empty projects, visit https://go.microsoft.com/fwlink/?LinkID=397860

namespace PromotionServiceNet.Infrastructure.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class PromotionController : ControllerBase
    {

        private readonly IUnitOfWork _unitOfWork;

        public PromotionController(IUnitOfWork unitOfWork)
        {
            _unitOfWork = unitOfWork;
        }

        [HttpPost]
        public async Task<bool> Post([FromBody] PromotionDto request)
        {
            var addPromotionUseCase = new AddPromotionUseCase(_unitOfWork);

            var response = await addPromotionUseCase.execute(request);

            return response.Result;
        }

        [HttpPost("calculate-discount")]
        public async Task<IActionResult> CalculateDiscount([FromBody] List<ProductDto> products)
        {
            var discount = await new GetPromotionForProductsUseCase(_unitOfWork).execute(products);
            return Ok(discount.discounts);
        }
    }
}
