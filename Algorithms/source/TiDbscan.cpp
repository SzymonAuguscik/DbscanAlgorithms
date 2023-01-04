#include <TiDbscan.hpp>
#include <DataUtils.hpp>
#include <algorithm>
#include <cmath>
#include <chrono>

namespace Algorithms
{

void TiDbscan::sortPoints()
{
    std::sort(_points.begin(),
              _points.end(),
              [&] (const Data::Point& p_point1, const Data::Point& p_point2) { return _referenceDistances[p_point1] < _referenceDistances[p_point2]; });
}

void TiDbscan::loadData()
{
    std::for_each(_points.begin(),
                  _points.end(),
                  [&] (const Data::Point& p_point) { _referenceDistances.insert({p_point, Data::getDistance(p_point, _referencePoint)}); });
    const auto startTime = std::chrono::high_resolution_clock::now();
    sortPoints();
    const auto endTime = std::chrono::high_resolution_clock::now();
    const auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
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
        for (auto it = startingPoint - 1; it != _points.begin(); it--)
        {
            if (std::abs(_referenceDistances[*it] - _referenceDistances[p_centralPoint]) > _eps)
            {
                break;
            }
            p_potentialNeighbours.push_back(*it);
            _stats.operationStats.triangleInequalityFilterCount++;
        }
    }
    
    if (startingPoint != _points.end())
    {
        for (auto it = startingPoint + 1; it != _points.end(); it++)
        {
            if (std::abs(_referenceDistances[*it] - _referenceDistances[p_centralPoint]) > _eps)
            {
                break;
            }
            p_potentialNeighbours.push_back(*it);
            _stats.operationStats.triangleInequalityFilterCount++;
        }
    }
}

std::vector<Data::Point> TiDbscan::getDataset(const Data::Point& p_centralPoint)
{
    std::vector<Data::Point> filteredPoints;
    filterWithTriangleInequality(p_centralPoint, filteredPoints);
    return filteredPoints;
}

void TiDbscan::setNeighbourhood(const Data::Point& p_centralPoint,
                                const std::vector<Data::Point>& p_dataset, 
                                std::vector<Data::Point>& p_potentialNeighbours)
{
    p_potentialNeighbours.clear();
    std::copy_if(p_dataset.begin(), 
                 p_dataset.end(), 
                 std::back_inserter(p_potentialNeighbours), 
                 [this, &p_centralPoint] (const auto& p_point)
                 {
                     _stats.operationStats.distanceCalculationsCount++;
                     return Data::getDistance(p_centralPoint, p_point) <= _eps;
                 });
}

}

