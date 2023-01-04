#include <Dbscan.hpp>
#include <map>

#pragma once

namespace Algorithms
{

class TiDbscan : virtual public Dbscan
{
public:
    TiDbscan() {}
    TiDbscan(int p_minPoints,
             double p_eps, 
             const std::string& p_filePath, 
             const Data::Point& p_referencePoint) : Dbscan{p_minPoints, p_eps, p_filePath},
                                                    _referencePoint{p_referencePoint}
    {
        loadData();
    }
protected:
    const Data::Point _referencePoint;
    void filterWithTriangleInequality(const Data::Point&, std::vector<Data::Point>&);
    void sortPoints() override;
    virtual void loadData() override;
    virtual std::vector<Data::Point> getDataset(const Data::Point&) override;
    virtual void setNeighbourhood(const Data::Point&, const std::vector<Data::Point>&, std::vector<Data::Point>&) override;
    std::map<Data::Point, double> _referenceDistances{};
};

}

