#include <Point.hpp>

namespace Data
{

void Point::addNeighbourId(int p_id)
{
    _neighbourIds.push_back(p_id);
}

std::vector<int> Point::getNeighbourIds() const
{
    return _neighbourIds;
}

void Point::setId(int p_id)
{
    _id = p_id;
}

int Point::getId() const
{
    return _id;
}

void Point::setClass(int p_class)
{
    _class = p_class;
}

int Point::getClass() const
{
    return _class;
}

void Point::setOriginalClass(int p_class)
{
    _originalClass = p_class;
}

int Point::getOriginalClass() const
{
    return _originalClass;
}
    
void Point::setCore()
{
    _isCore = true;
}
    
bool Point::isCore() const
{
    return _isCore;
}

void Point::addCoordinate(double p_coordinate)
{
    _coordinates.push_back(p_coordinate);
}

std::vector<double> Point::getCoordinates() const
{
    return _coordinates;
}

void Point::incrementCalculationsCount()
{
    _calculationsCount++;
}

int Point::getCalculationsCount() const
{
    return _calculationsCount;
}

}