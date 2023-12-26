using PromotionServiceNet.Domain.ValueObjects.Base;

namespace PromotionServiceNet.Domain.ValueObjects;

public class Filter : ValueObject
{
    public bool IsActive { get; set; }
    public DateTime CurrentDate { get; set; }

    public Filter(bool isActive, DateTime currentDate)
    {
        IsActive = isActive;
        CurrentDate = currentDate;
    }
}
