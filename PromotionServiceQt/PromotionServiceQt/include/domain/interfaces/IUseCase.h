#ifndef IUSECASE_H
#define IUSECASE_H

#include <QFuture>
#include <QObject>

template<typename IRequest, typename IResponse>
class IUseCase
{
public:
    virtual ~IUseCase() {}

    virtual QFuture<IResponse> execute(IRequest request) = 0;
};

#endif // IUSECASE_H
