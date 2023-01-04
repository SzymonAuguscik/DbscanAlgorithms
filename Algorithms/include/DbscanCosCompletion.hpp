#include <DbscanCosFamily.hpp>

#pragma once

namespace Algorithms
{

class DbscanCosCompletion : public DbscanCosFamily
{
public:
    DbscanCosCompletion(int p_minPoints, double p_eps, const std::string& p_filePath) : Dbscan{p_minPoints, p_eps, p_filePath},
                                                                                        DbscanCosFamily{p_minPoints, p_eps, p_filePath}
    {}
protected:
    virtual void setNeighbourhood(const Data::Point&, const std::vector<Data::Point>&, std::vector<Data::Point>&) override;
};

}

