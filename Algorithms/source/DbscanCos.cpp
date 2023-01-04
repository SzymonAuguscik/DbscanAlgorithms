#include <DbscanCos.hpp>
#include <DataUtils.hpp>
#include <algorithm>

namespace Algorithms
{

void DbscanCos::setNeighbourhood(const Data::Point& p_centralPoint,
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
                     return Data::getCosSim(p_centralPoint, p_point, _lengths) >= _eps;
                 });
}

}