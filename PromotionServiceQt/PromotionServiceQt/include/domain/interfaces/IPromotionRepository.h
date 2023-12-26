#ifndef IPROMOTIONREPOSITORY_H
#define IPROMOTIONREPOSITORY_H

#include <QFuture>
#include <QList>
#include "include/domain/model/Filter.h"
#include "include/domain/model/Promotion.h"
#include "Filter.h"

class IPromotionRepository
{
public:
    virtual ~IPromotionRepository() {}

    virtual QFuture<bool> addPromotion(const Promotion& promotion) = 0;
   // virtual QFuture<Promotion> getPromotionById(int id) = 0;
    virtual QFuture<QList<Promotion>> getPromotionsByFilter(const Filter& filter) = 0;
};

#endif // IPROMOTIONREPOSITORY_H
