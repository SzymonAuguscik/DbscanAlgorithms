#include <DbscanCosFamily.hpp>

#pragma once

namespace Algorithms
{

class DbscanCosCompletion : public DbscanCosFamily
{
public:
    DbscanCosCompletion(int p_minPoints, double p_eps, const std::string& p_filePath) : Dbscan{p_minPoints, 1 - p_eps, p_filePath},
                                                                                        DbscanCosFamily{p_minPoints, 1 - p_eps, p_filePath},
                                                                                        _originalEps{p_eps}
    {}
protected:
    std::string getEpsilonView() const override;
    virtual std::string getAlgorithmName() const override;
    virtual void setNeighbourhood(Data::Point&, const std::vector<Data::Point>&, std::vector<Data::Point>&) override;

    double _originalEps;
};

}

