#include <DbscanCosFamily.hpp>
#include <DataUtils.hpp>
#include <chrono>
#include <algorithm>

namespace Algorithms
{

void DbscanCosFamily::loadData()
{
    const auto startTime = std::chrono::high_resolution_clock::now();
    std::for_each(_points.begin(),
                  _points.end(),
                  [&] (const Data::Point& p_point) { _lengths.insert({p_point, Data::getLength(p_point)}); });
    const auto endTime = std::chrono::high_resolution_clock::now();
    const auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    _stats.timeStats.dataLoadingTime = elapsedTime.count();
}

}