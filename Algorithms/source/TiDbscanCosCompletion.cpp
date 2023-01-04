#include <TiDbscanCosCompletion.hpp>
#include <chrono>

namespace Algorithms
{

std::vector<Data::Point> TiDbscanCosCompletion::getDataset(const Data::Point& p_centralPoint)
{
    return TiDbscan::getDataset(p_centralPoint);
}

void TiDbscanCosCompletion::setNeighbourhood(const Data::Point& p_centralPoint,
                                       const std::vector<Data::Point>& p_dataset, 
                                       std::vector<Data::Point>& p_potentialNeighbours)
{
    return DbscanCosCompletion::setNeighbourhood(p_centralPoint, p_dataset, p_potentialNeighbours);
}

}

