#include <TiDbscan.hpp>
#include <DbscanEucNorm.hpp>
#include <DataUtils.hpp>

#pragma once

namespace Algorithms
{

class TiDbscanEucNorm : public DbscanEucNorm, public TiDbscan
{
public:
    TiDbscanEucNorm(int p_minPoints,
                    double p_eps,
                    const std::string& p_filePath,
                    const std::string& p_referencePointMode) : Dbscan{p_minPoints, std::sqrt(2 - 2 * p_eps), p_filePath},
                                                               DbscanEucNorm{p_minPoints, p_eps, p_filePath},
                                                               TiDbscan{p_minPoints, std::sqrt(2 - 2 * p_eps), p_filePath, p_referencePointMode}
    {}
protected:
    void loadData() override {};
    std::string getAlgorithmName() const override;
    std::vector<Data::Point> getDataset(const Data::Point&) override;
    void setNeighbourhood(Data::Point&, const std::vector<Data::Point>&, std::vector<Data::Point>&) override;
};

}

