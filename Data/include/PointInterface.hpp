#include <vector>

#pragma once

namespace Data
{
    
class PointInterface
{
public:
    virtual void setClass(int) = 0;
    virtual int getClass() const = 0;
    virtual void setCore() = 0;
    virtual bool isCore() const = 0;
    virtual void addCoordinate(double) = 0;
    virtual std::vector<double> getCoordinates() const = 0;
};

}

