#include <DbscanInterface.hpp>
#include <DataLoader.hpp>
#include <DataLoaderInterface.hpp>
#include <Point.hpp>
#include <vector>
#include <string>
#include <memory>
#include <DataUtils.hpp>
#include <functional>
#include <map>
#include <OverallStats.hpp>

#pragma once

namespace Algorithms
{

class Dbscan : public DbscanInterface
{
public:
    Dbscan() {}
    Dbscan(int p_minPoints, double p_eps, const std::string& p_filePath) : _minPoints{p_minPoints},
                                                                           _eps{p_eps}
    { 
        _dataLoader = std::make_unique<Data::DataLoader>(p_filePath);
        loadData();
    }

    void performClustering() override;
    void printPointsByType();
    void printAllPoints();
    void printStats();
    std::vector<Data::Point> getNoisePoints();
    std::vector<Data::Point> getReachablePoints();
    std::vector<Data::Point> getCorePoints();
protected:
    virtual void loadData();
    virtual void sortPoints();
    virtual std::vector<Data::Point> getDataset(const Data::Point&);
    virtual void setNeighbourhood(const Data::Point&, const std::vector<Data::Point>&, std::vector<Data::Point>&);

    int _minPoints;
    double _eps;
    std::unique_ptr<Data::DataLoaderInterface> _dataLoader;
    std::vector<Data::Point> _points{};
    Results::OverallStats _stats{};
};

}

