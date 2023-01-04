#include <Point.hpp>

namespace Data
{

void Point::setClass(int p_class)
{
    _class = p_class;
}

int Point::getClass() const
{
    return _class;
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

}