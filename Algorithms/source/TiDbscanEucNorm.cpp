#include <TiDbscanEucNorm.hpp>

namespace Algorithms
{

std::vector<Data::Point> TiDbscanEucNorm::getDataset(const Data::Point& p_centralPoint)
{
    return TiDbscan::getDataset(p_centralPoint);
}

void TiDbscanEucNorm::setNeighbourhood(Data::Point& p_centralPoint,
                                       const std::vector<Data::Point>& p_dataset, 
                                       std::vector<Data::Point>& p_potentialNeighbours)
{
    return DbscanEucNorm::setNeighbourhood(p_centralPoint, p_dataset, p_potentialNeighbours);
}

std::string TiDbscanEucNorm::getAlgorithmName() const
{
    return "_TIDBSCANEUCNORM_";
}

}

