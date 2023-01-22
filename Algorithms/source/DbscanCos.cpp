#include <DbscanCos.hpp>
#include <DataUtils.hpp>
#include <algorithm>

namespace Algorithms
{

void DbscanCos::setNeighbourhood(Data::Point& p_centralPoint,
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
                     return Data::getCosSim(p_centralPoint, p_point, _lengths) >= _eps;
                 });
    
    std::for_each(p_potentialNeighbours.begin(),
                  p_potentialNeighbours.end(),
                  [&p_centralPoint] (const Data::Point& p_neighbour) { p_centralPoint.addNeighbourId(p_neighbour.getId()); });
}

std::string DbscanCos::getAlgorithmName() const
{
    return "_DBSCANCOS_";
}

}