#include <vector>

#pragma once

namespace Data
{
    
class PointInterface
{
public:
    virtual void setId(int) = 0;
    virtual int getId() const = 0;
    virtual void setClass(int) = 0;
    virtual int getClass() const = 0;
    virtual void setOriginalClass(int) = 0;
    virtual int getOriginalClass() const = 0;
    virtual void setCore() = 0;
    virtual bool isCore() const = 0;
    virtual void addCoordinate(double) = 0;
    virtual std::vector<double> getCoordinates() const = 0;
    virtual void addNeighbourId(int) = 0;
    virtual std::vector<int> getNeighbourIds() const = 0;
    virtual void incrementCalculationsCount() = 0;
    virtual int getCalculationsCount() const = 0;
};

}

