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

const std::string OUT_PREFIX{"out"};
const std::string STAT_PREFIX{"stat"};
const std::string RESULTS_DIR{"Results/files/"};

class Dbscan : public DbscanInterface
{
public:
    Dbscan() {}
    Dbscan(int p_minPoints, double p_eps, const std::string& p_filePath) : _minPoints{p_minPoints},
                                                                           _eps{p_eps},
                                                                           _filePath{p_filePath}
    { 
        _dataLoader = std::make_unique<Data::DataLoader>(p_filePath);
        loadData();
    }

    void performClustering() override;
protected:
    void fillRandIndex();
    void saveResults();
    void saveOutputFile() const;
    void saveStatFile() const;
    int getClassNumber() const;
    int getNoisePointsNumber() const;
    int getReachablePointsNumber() const;
    int getCorePointsNumber() const;

    std::string buildResultFilename(std::string) const;
    virtual std::string getAlgorithmName() const;
    virtual void loadData();
    virtual void sortPoints();
    virtual std::vector<Data::Point> getDataset(const Data::Point&);
    virtual void setNeighbourhood(Data::Point&, const std::vector<Data::Point>&, std::vector<Data::Point>&);
    virtual std::string getReferencePointView() const { return ""; };
    virtual std::string getEpsilonView() const;

    int _minPoints;
    double _eps;
    std::string _filePath;
    std::string _refSufix{};
    std::unique_ptr<Data::DataLoaderInterface> _dataLoader;
    std::vector<Data::Point> _points{};
    Results::OverallStats _stats{};
};

}

