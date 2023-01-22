#include <DbscanEucNorm.hpp>
#include <chrono>
#include <algorithm>
#include <iostream>

namespace Algorithms
{

void DbscanEucNorm::loadData()
{
    std::cout << "[LOG] Normalizing" << std::endl;
    const auto startTime = std::chrono::high_resolution_clock::now();
    Data::normalizePoints(_points);
    const auto endTime = std::chrono::high_resolution_clock::now();
    const auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    _stats.timeStats.normalizingTime = elapsedTime.count();
}

void DbscanEucNorm::setNeighbourhood(Data::Point& p_centralPoint,
                                     const std::vector<Data::Point>& p_dataset, 
                                     std::vector<Data::Point>& p_potentialNeighbours)
{
    return Dbscan::setNeighbourhood(p_centralPoint, p_dataset, p_potentialNeighbours);
}

std::string DbscanEucNorm::getAlgorithmName() const
{
    return "_DBSCANEUCNORM_";
}

std::string DbscanEucNorm::getEpsilonView() const
{
    return "original eps: " + std::to_string(_originalEps) + "\neps: " + std::to_string(_eps) + '\n';
}

}

