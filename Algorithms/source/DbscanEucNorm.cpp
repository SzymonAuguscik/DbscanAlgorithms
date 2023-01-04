#include <DbscanEucNorm.hpp>
#include <chrono>
#include <algorithm>

namespace Algorithms
{

void DbscanEucNorm::loadData()
{
    const auto startTime = std::chrono::high_resolution_clock::now();
    Data::normalizePoints(_points);
    const auto endTime = std::chrono::high_resolution_clock::now();
    const auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    _stats.timeStats.dataLoadingTime = elapsedTime.count();
}

void DbscanEucNorm::setNeighbourhood(const Data::Point& p_centralPoint,
                                       const std::vector<Data::Point>& p_dataset, 
                                       std::vector<Data::Point>& p_potentialNeighbours)
{
    return Dbscan::setNeighbourhood(p_centralPoint, p_dataset, p_potentialNeighbours);
}

}

