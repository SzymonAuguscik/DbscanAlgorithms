#include <DbscanCosFamily.hpp>
#include <DataUtils.hpp>
#include <algorithm>

namespace Algorithms
{

void DbscanCosFamily::loadData()
{
    std::for_each(_points.begin(),
                  _points.end(),
                  [&] (const Data::Point& p_point) { _lengths.insert({p_point.getId(), Data::getLength(p_point)}); });
}

}