#include "include/application/usecases/GetPromotionForProductsUseCase.h"
#include "include/domain/interfaces/IUnitOfWork.h"
#include "include/application/dto/ProductDto.h"
#include "include/domain/enums/PromotionType.h"
#include "include/domain/model/PromoBasket.h"
#include "include/domain/model/Promotion.h"
#include <QtConcurrent>
#include <QDateTime>
#include <QMap>
#include <cmath> // for std::round
