#include <Dbscan.hpp>
#include <map>
#include <ReferencePointMode.hpp>

#pragma once

namespace Algorithms
{

const std::map<const std::string, Data::ReferencePointMode> REFERENCE_POINT_MODES{
    {"Min", Data::ReferencePointMode::Min},
    {"Dimension0", Data::ReferencePointMode::Dimension0},
    {"Dimension1", Data::ReferencePointMode::Dimension1},
    {"Dimension2", Data::ReferencePointMode::Dimension2},
    {"Dimension3", Data::ReferencePointMode::Dimension3},
    {"Dimension4", Data::ReferencePointMode::Dimension4},
    {"Dimension5", Data::ReferencePointMode::Dimension5},
    {"Max", Data::ReferencePointMode::Max}
};

class TiDbscan : virtual public Dbscan
{
public:
    TiDbscan() {}
    TiDbscan(int p_minPoints,
             double p_eps, 
             const std::string& p_filePath, 
             const std::string& p_referencePointMode) : Dbscan{p_minPoints, p_eps, p_filePath}
    {
        setReferencePoint(p_referencePointMode);
        loadData();
    }
protected:
    void setReferencePointByDimension(size_t);
    void filterWithTriangleInequality(const Data::Point&, std::vector<Data::Point>&);
    void sortPoints() override;
    void setReferencePoint(const std::string&);
    virtual void loadData() override;
    virtual std::string getAlgorithmName() const override;
    virtual std::vector<Data::Point> getDataset(const Data::Point&) override;
    virtual void setNeighbourhood(Data::Point&, const std::vector<Data::Point>&, std::vector<Data::Point>&) override;
    std::string getReferencePointView() const override;

    std::map<int, double> _referenceDistances{};
    Data::Point _referencePoint{};
};

}

