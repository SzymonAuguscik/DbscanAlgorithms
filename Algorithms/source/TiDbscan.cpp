#include <TiDbscan.hpp>
#include <DataUtils.hpp>
#include <algorithm>
#include <cmath>
#include <chrono>

namespace 
{

std::vector<double> findMaxCoordinates(const std::vector<Data::Point>& p_points)
{
    auto maxCoordinates = p_points[0].getCoordinates();
    size_t dimension = maxCoordinates.size();

    for (auto point = p_points.begin() + 1; point != p_points.end(); point++)
    {
        auto currentCoordinates = point->getCoordinates();

        for (size_t i = 0; i < dimension; i++)
        {
            if (maxCoordinates[i] < currentCoordinates[i])
            {
                maxCoordinates[i] = currentCoordinates[i];
            }
        }
    }

    return maxCoordinates;
}

std::vector<double> findMinCoordinates(const std::vector<Data::Point>& p_points)
{
    auto minCoordinates = p_points[0].getCoordinates();
    size_t dimension = minCoordinates.size();

    for (auto point = p_points.begin() + 1; point != p_points.end(); point++)
    {
        auto currentCoordinates = point->getCoordinates();

        for (size_t i = 0; i < dimension; i++)
        {
            if (minCoordinates[i] > currentCoordinates[i])
            {
                minCoordinates[i] = currentCoordinates[i];
            }
        }
    }

    return minCoordinates;
}

}

namespace Algorithms
{

void TiDbscan::sortPoints()
{
    std::sort(_points.begin(),
              _points.end(),
              [&] (const Data::Point& p_point1, const Data::Point& p_point2) { return _referenceDistances[p_point1.getId()] < _referenceDistances[p_point2.getId()]; });
}

void TiDbscan::setReferencePointByDimension(size_t p_dimension)
{
    std::vector<double> coordinates{};
    size_t dimensions = _points[0].getCoordinates().size();

    for (size_t i = 0; i < dimensions; i++)
    {
        coordinates.push_back((int)(p_dimension == i));
    }

    _referencePoint = Data::Point{coordinates};
}

void TiDbscan::setReferencePoint(const std::string& p_referencePointMode)
{
    if (REFERENCE_POINT_MODES.count(p_referencePointMode) == 0)
    {
        auto coordinates = findMaxCoordinates(_points);
        _referencePoint = Data::Point{coordinates};
        _refSufix = "_rMax";
        return;
    }

    _refSufix = "_r" + p_referencePointMode;

    switch (REFERENCE_POINT_MODES.at(p_referencePointMode))
    {
        case Data::ReferencePointMode::Max:
        {
            auto coordinates = findMaxCoordinates(_points);
            _referencePoint = Data::Point{coordinates};
            break;
        }
        case Data::ReferencePointMode::Min:
        {
            auto coordinates = findMinCoordinates(_points);
            _referencePoint = Data::Point{coordinates};
            break;
        }
        case Data::ReferencePointMode::Dimension0:
        {
            setReferencePointByDimension(0);
            break;
        }
        case Data::ReferencePointMode::Dimension1:
        {
            setReferencePointByDimension(1);
            break;
        }
        case Data::ReferencePointMode::Dimension2:
        {
            setReferencePointByDimension(2);
            break;
        }
        case Data::ReferencePointMode::Dimension3:
        {
            setReferencePointByDimension(3);
            break;
        }
        case Data::ReferencePointMode::Dimension4:
        {
            setReferencePointByDimension(4);
            break;
        }
        case Data::ReferencePointMode::Dimension5:
        {
            setReferencePointByDimension(5);
            break;
        }
    }
}

void TiDbscan::loadData()
{
    auto startTime = std::chrono::high_resolution_clock::now();
    std::for_each(_points.begin(),
                  _points.end(),
                  [&] (const Data::Point& p_point) { _referenceDistances.insert({p_point.getId(), Data::getDistance(p_point, _referencePoint)}); });
    auto endTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    _stats.timeStats.referenceDistanceCalculationsTime = elapsedTime.count();

    startTime = std::chrono::high_resolution_clock::now();
    sortPoints();
    endTime = std::chrono::high_resolution_clock::now();
    elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    _stats.timeStats.pointsSortingTime = elapsedTime.count();
}

void TiDbscan::filterWithTriangleInequality(const Data::Point& p_centralPoint,
                                            std::vector<Data::Point>& p_potentialNeighbours)
{
    const auto& startingPoint = std::find(_points.begin(),
                                          _points.end(),
                                          p_centralPoint);
    p_potentialNeighbours.push_back(p_centralPoint);

    if (startingPoint != _points.begin())
    {
        for (auto it = startingPoint - 1; it != _points.begin() - 1; it--)
        {
            _stats.operationStats.triangleInequalityFilterCount++;
            if (_referenceDistances[p_centralPoint.getId()] - _referenceDistances[it->getId()] > _eps)
            {
                break;
            }
            p_potentialNeighbours.push_back(*it);
        }
    }
    
    if (startingPoint != _points.end())
    {
        for (auto it = startingPoint + 1; it != _points.end(); it++)
        {
            _stats.operationStats.triangleInequalityFilterCount++;
            if (_referenceDistances[it->getId()] - _referenceDistances[p_centralPoint.getId()] > _eps)
            {
                break;
            }
            p_potentialNeighbours.push_back(*it);
        }
    }
}

std::vector<Data::Point> TiDbscan::getDataset(const Data::Point& p_centralPoint)
{
    std::vector<Data::Point> filteredPoints;
    filterWithTriangleInequality(p_centralPoint, filteredPoints);
    return filteredPoints;
}

std::string TiDbscan::getReferencePointView() const
{
    std::string referencePointView{"reference point: {"};
    
    for (auto coordinate : _referencePoint.getCoordinates())
    {
        referencePointView += " " + std::to_string(coordinate);
    }

    referencePointView += " }\n";

    return referencePointView;
}

void TiDbscan::setNeighbourhood(Data::Point& p_centralPoint,
                                const std::vector<Data::Point>& p_dataset, 
                                std::vector<Data::Point>& p_potentialNeighbours)
{
    p_potentialNeighbours.clear();
    std::copy_if(p_dataset.begin(), 
                 p_dataset.end(), 
                 std::back_inserter(p_potentialNeighbours), 
                 [this, &p_centralPoint] (const auto& p_point)
                 {
                     if (p_centralPoint == p_point)
                     {
                         return true;
                     }
                     p_centralPoint.incrementCalculationsCount();
                     _stats.operationStats.distanceCalculationsCount++;
                     return Data::getDistance(p_centralPoint, p_point) <= _eps;
                 });

    std::for_each(p_potentialNeighbours.begin(),
                  p_potentialNeighbours.end(),
                  [&p_centralPoint] (const Data::Point& p_neighbour) { p_centralPoint.addNeighbourId(p_neighbour.getId()); });
}

std::string TiDbscan::getAlgorithmName() const
{
    return "_TIDBSCAN_";
}

}

