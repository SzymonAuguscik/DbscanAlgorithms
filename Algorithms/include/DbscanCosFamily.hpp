#include <Dbscan.hpp>

#pragma once

namespace Algorithms
{

class DbscanCosFamily : virtual public Dbscan
{
public:
    DbscanCosFamily() {}
    DbscanCosFamily(int p_minPoints, double p_eps, const std::string& p_filePath) : Dbscan{p_minPoints, p_eps, p_filePath}
    {
        loadData();
    }
protected:
    virtual void loadData() override;
    std::map<Data::Point, double> _lengths{};
};

}

