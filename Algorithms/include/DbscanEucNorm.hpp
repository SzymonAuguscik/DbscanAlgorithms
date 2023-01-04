#include <Dbscan.hpp>
#include <DataUtils.hpp>

#pragma once

namespace Algorithms
{

class DbscanEucNorm : virtual public Dbscan
{
public:
    DbscanEucNorm() {}
    DbscanEucNorm(int p_minPoints, double p_eps, const std::string& p_filePath) : Dbscan{p_minPoints, p_eps, p_filePath}
    {
        loadData();
    }
protected:
    virtual void loadData() override;
    virtual void setNeighbourhood(const Data::Point&, const std::vector<Data::Point>&, std::vector<Data::Point>&) override;
};

}

