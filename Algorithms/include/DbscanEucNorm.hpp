#include <Dbscan.hpp>
#include <DataUtils.hpp>
#include <cmath>

#pragma once

namespace Algorithms
{

class DbscanEucNorm : virtual public Dbscan
{
public:
    DbscanEucNorm() {}
    DbscanEucNorm(int p_minPoints, double p_eps, const std::string& p_filePath) : Dbscan{p_minPoints, std::sqrt(2 - 2 * p_eps), p_filePath},
                                                                                  _originalEps{p_eps}
    {
        loadData();
    }
protected:
    std::string getEpsilonView() const override;
    virtual void loadData() override;
    virtual std::string getAlgorithmName() const override;
    virtual void setNeighbourhood(Data::Point&, const std::vector<Data::Point>&, std::vector<Data::Point>&) override;

    double _originalEps;
};

}

