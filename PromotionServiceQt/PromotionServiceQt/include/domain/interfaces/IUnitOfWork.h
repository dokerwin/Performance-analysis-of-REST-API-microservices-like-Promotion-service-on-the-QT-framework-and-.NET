#ifndef IUNITOFWORK_H
#define IUNITOFWORK_H

#include "IPromotionRepository.h"
#include <QFuture>

class IUnitOfWork
{
public:
    virtual ~IUnitOfWork() {}

    virtual IPromotionRepository* getPromotionRepository() const = 0;
    virtual QFuture<bool> asyncCommit() = 0;
};

#endif // IUNITOFWORK_H
