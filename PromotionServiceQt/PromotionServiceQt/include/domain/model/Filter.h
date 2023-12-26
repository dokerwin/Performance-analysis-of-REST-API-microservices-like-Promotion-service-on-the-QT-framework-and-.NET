#ifndef FILTER_H
#define FILTER_H

#include <QDateTime>
#include "base/ValueObject.h"

class Filter : public ValueObject
{
public:
    Filter() = default;
    Filter(bool isActive, const QDateTime& currentDate)
        : isActive(isActive), currentDate(currentDate) {}

    bool getIsActive() const { return isActive; }
    void setIsActive(bool value) { isActive = value; }

    QDateTime getCurrentDate() const { return currentDate; }
    void setCurrentDate(const QDateTime& value) { currentDate = value; }

private:
    bool isActive;
    QDateTime currentDate;
};

#endif // FILTER_H
