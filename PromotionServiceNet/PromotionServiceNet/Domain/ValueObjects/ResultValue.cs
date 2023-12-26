using PromotionServiceNet.Domain.ValueObjects.Base;

namespace PromotionServiceNet.Domain.ValueObjects;

public class ResultValue<T> : ValueObject
{
   public bool Result { get; set; }
    public T? Value { get; set; }
}
