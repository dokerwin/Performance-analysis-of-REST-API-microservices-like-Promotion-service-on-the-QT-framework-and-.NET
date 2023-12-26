QT -= gui
QT += network sql concurrent core
CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        src/application/usecases/GetPromotionForProductsUseCase.cpp \
        src/domain/model/Promotion.cpp \
        src/infrastructure/PromotionController.cpp \
        src/infrastructure/SqlitePromotionRepository.cpp \
        src/infrastructure/SqliteUnitOfWork.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    include/application/dto/DiscountDto.h \
    include/application/dto/ProductDto.h \
    include/application/mappers/PromotionMapper.h \
    include/application/usecases/AddPromotionUseCase.h \
    include/application/usecases/DeletePromotionUseCase.h \
    include/application/usecases/DisablePromotionUseCase.h \
    include/application/usecases/EditPromotionUseCase.h \
    include/application/usecases/GetPromotionForProductsUseCase.h \
    include/domain/enums/BasketType.h \
    include/domain/enums/PromotionType.h \
    include/domain/interfaces/IPromotionRepository.h \
    include/domain/interfaces/IUnitOfWork.h \
    include/domain/interfaces/IUseCase.h \
    include/domain/model/Discount.h \
    include/domain/model/Filter.h \
    include/domain/model/Product.h \
    include/domain/model/ProductDiscount.h \
    include/domain/model/ProductPromotion.h \
    include/domain/model/PromoBasket.h \
    include/domain/model/PromoBasketProduct.h \
    include/domain/model/Promotion.h \
    include/domain/model/base/Entity.h \
    include/domain/model/base/ValueObject.h \
    include/infrastructure/PromotionController.h \
    include/infrastructure/SqlitePromotionRepositroy.h \
    include/infrastructure/SqliteUnitOfWork.h
