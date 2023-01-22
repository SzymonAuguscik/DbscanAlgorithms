#include <TiDbscan.hpp>
#include <DbscanCosCompletion.hpp>
#include <DataUtils.hpp>

#pragma once

namespace Algorithms
{

class TiDbscanCosCompletion : public DbscanCosCompletion, public TiDbscan
{
public:
    TiDbscanCosCompletion(int p_minPoints,
                          double p_eps,
                          const std::string& p_filePath,
                          const std::string& p_referencePointMode) : Dbscan{p_minPoints, 1 - p_eps, p_filePath},
                                                                     DbscanCosCompletion{p_minPoints, p_eps, p_filePath},
                                                                     TiDbscan{p_minPoints, 1 - p_eps, p_filePath, p_referencePointMode}
    {}
protected:
    void loadData() override {}
    std::string getAlgorithmName() const override;
    std::vector<Data::Point> getDataset(const Data::Point&) override;
    void setNeighbourhood(Data::Point&, const std::vector<Data::Point>&, std::vector<Data::Point>&) override;
};

}

