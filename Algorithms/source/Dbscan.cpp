#include <Dbscan.hpp>
#include <DataLoader.hpp>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <DataUtils.hpp>
#include <deque>
#include <chrono>
#include <iostream>
#include <fstream>

#include <set>

namespace Data
{

double getDistance(const Point&, const Point&);

}

namespace Algorithms
{

void Dbscan::performClustering()
{
    std::cout << "[LOG] Clustering" << std::endl;
    const auto startTime = std::chrono::high_resolution_clock::now();
    int currentClass{0};

    for (auto& point : _points)
    {
        std::cout << "[LOG] point id: " << point.getId() << std::endl;
        if (point.getClass() != Data::NO_CLASS)
        {
            continue;
        }

        std::vector<Data::Point> neighbours{};
        const auto& dataset = getDataset(point);
        setNeighbourhood(point, dataset, neighbours);

        if (neighbours.size() < static_cast<size_t>(_minPoints))
        {
            point.setClass(Data::NOISE);
            continue;
        }
        
        point.setCore();
        point.setClass(currentClass);
        std::vector<Data::Point> seeds;
        neighbours.erase(std::remove_if(neighbours.begin(), neighbours.end(), [&point] (auto& p_point) { return p_point == point; } ), neighbours.end());
        std::copy(neighbours.begin(), neighbours.end(), std::back_inserter(seeds));

        while (seeds.size() > 0)
        {
            std::set<Data::Point> s{seeds.begin(), seeds.end()};
            std::cout << "Seeds: " << seeds.size() << ", " << s.size() << std::endl;
            const auto seed = std::find_if(_points.begin(), _points.end(), [&seeds] (const auto& p_point) { return seeds.front() == p_point; } );
            seeds.erase(std::remove_if(seeds.begin(), seeds.end(), [&seed] (auto& p_seed) { return p_seed == *seed; }), seeds.end());

            if (seed->getClass() == Data::NOISE)
            {
                seed->setClass(currentClass);
                continue;
            }

            if (seed->getClass() != Data::NO_CLASS)
            {
                continue;
            }

            seed->setClass(currentClass);
            std::vector<Data::Point> seedNeighbours;
            const auto& seedDataset = getDataset(*seed);
            setNeighbourhood(*seed, seedDataset, seedNeighbours);

            if (seedNeighbours.size() >= static_cast<size_t>(_minPoints))
            {
                seed->setCore();
                seedNeighbours.erase(std::remove_if(seedNeighbours.begin(), seedNeighbours.end(), [&seed] (const auto& p_point) { return *seed == p_point; }), seedNeighbours.end());
                seedNeighbours.erase(std::remove_if(seedNeighbours.begin(), seedNeighbours.end(), [&seeds] (const auto& p_neighbour) { return std::count(seeds.begin(), seeds.end(), p_neighbour) != 0; }), seedNeighbours.end());
                std::copy(seedNeighbours.begin(), seedNeighbours.end(), std::back_inserter(seeds));
            }
        }
        currentClass++;
    }
    const auto endTime = std::chrono::high_resolution_clock::now();
    const auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    _stats.timeStats.clusteringAlgorithmTime = elapsedTime.count();
    saveResults();
}

void Dbscan::loadData()
{
    std::cout << "[LOG] Loading data" << std::endl;
    auto startTime = std::chrono::high_resolution_clock::now();
    _points = _dataLoader->load();
    std::for_each(_points.begin(),
                  _points.end(),
                  [] (Data::Point& p_point) { p_point.setClass(Data::NO_CLASS); });
    auto endTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    _stats.timeStats.dataLoadingTime = elapsedTime.count();
    startTime = std::chrono::high_resolution_clock::now();
    sortPoints();
    endTime = std::chrono::high_resolution_clock::now();
    elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    _stats.timeStats.pointsSortingTime = elapsedTime.count();
}

std::vector<Data::Point> Dbscan::getDataset(const Data::Point&)
{
    return _points;
}

void Dbscan::setNeighbourhood(Data::Point& p_centralPoint,
                              const std::vector<Data::Point>& p_dataset,
                              std::vector<Data::Point>& p_potentialNeighbours)
{
    p_potentialNeighbours.clear();
    std::copy_if(p_dataset.begin(),
                 p_dataset.end(),
                 std::back_inserter(p_potentialNeighbours),
                 [this, &p_centralPoint] (const auto& p_point)
                 {
                     if (p_centralPoint == p_point)
                     {
                         return true;
                     }
                     p_centralPoint.incrementCalculationsCount();
                     _stats.operationStats.distanceCalculationsCount++;
                     return Data::getDistance(p_centralPoint, p_point) <= _eps;
                 });

    std::for_each(p_potentialNeighbours.begin(),
                  p_potentialNeighbours.end(),
                  [&p_centralPoint] (const Data::Point& p_neighbour) { p_centralPoint.addNeighbourId(p_neighbour.getId()); });
}

void Dbscan::sortPoints()
{
    std::cout << "[LOG] Sorting" << std::endl;
    std::sort(_points.begin(),
              _points.end());
}

int Dbscan::getClassNumber() const
{
    const auto& p_point = std::max_element(_points.begin(),
                                           _points.end(),
                                           [] (const Data::Point& p_point1, const Data::Point& p_point2) { return p_point1.getClass() < p_point2.getClass(); });
    return p_point->getClass() + 1;
}

int Dbscan::getNoisePointsNumber() const
{
    int noisePoints = std::count_if(_points.begin(),
                                    _points.end(),
                                    [] (const Data::Point& p_point) { return p_point.getClass() == Data::NOISE; });
    return noisePoints;
}

int Dbscan::getReachablePointsNumber() const
{
    int reachablePoints = std::count_if(_points.begin(),
                                        _points.end(),
                                        [] (const Data::Point& p_point) { return !p_point.isCore() && p_point.getClass() != Data::NOISE; });
    return reachablePoints;
}

int Dbscan::getCorePointsNumber() const
{
    int corePoints = std::count_if(_points.begin(),
                                   _points.end(),
                                   [] (const Data::Point& p_point) { return p_point.isCore(); });
    return corePoints;
}

std::string Dbscan::getAlgorithmName() const
{
    return "_DBSCAN_";
}

std::string Dbscan::buildResultFilename(std::string p_prefix) const
{
    int dimension = _points[0].getCoordinates().size();
    int pointsNumber = _points.size();
    std::string dataFilename = _filePath.substr(_filePath.find_last_of("/\\") + 1);
    std::string datasetName = dataFilename.substr(0, dataFilename.find_last_of("."));

    return RESULTS_DIR + p_prefix + getAlgorithmName() + datasetName
                       + "_D" + std::to_string(dimension)
                       + "_R" + std::to_string(pointsNumber)
                       + "_mP" + std::to_string(_minPoints)
                       + "_E" + std::to_string(_eps)
                       + _refSufix + ".txt";
}

void Dbscan::fillRandIndex()
{
    size_t size{_points.size()};
    int truePositives{0};
    int trueNegatives{0};

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = i + 1; j < size; j++)
        {
            auto firstOriginalClass = _points[i].getOriginalClass();
            auto secondOriginalClass = _points[j].getOriginalClass();
            auto firstClusteredClass = _points[i].getClass();
            auto secondClusteredClass = _points[j].getClass();

            if (firstOriginalClass == secondOriginalClass && firstClusteredClass == secondClusteredClass)
            {
                truePositives++;
                continue;
            }

            if (firstOriginalClass != secondOriginalClass && firstClusteredClass != secondClusteredClass)
            {
                trueNegatives++;
            }
        }
    }

    int pairsNumber{static_cast<int>(size * (size - 1) / 2)};

    _stats.scoreStats.truePositives = truePositives;
    _stats.scoreStats.trueNegatives = trueNegatives;
    _stats.scoreStats.pairsNumber = pairsNumber;
    _stats.scoreStats.randIndex = (truePositives + trueNegatives) / static_cast<double>(pairsNumber);
}

void Dbscan::saveResults()
{
    std::cout << "[LOG] Saving results" << std::endl;
    const auto startTime = std::chrono::high_resolution_clock::now();
    saveOutputFile();
    const auto endTime = std::chrono::high_resolution_clock::now();
    const auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    _stats.timeStats.outputSavingTime = elapsedTime.count();
    fillRandIndex();
    saveStatFile();
}

void Dbscan::saveOutputFile() const
{
    std::ofstream outFile{buildResultFilename(OUT_PREFIX)};
    outFile << "id, coordinates..., calculationCount, type, class, |N_eps|, N_eps...\n";

    for (auto point : _points)
    {
        outFile << point.getId() << ", ";

        for (auto coordinate : point.getCoordinates())
        {
            outFile << coordinate << ", ";
        }

        outFile << point.getCalculationsCount() << ", ";
        outFile << (point.getClass() != Data::NOISE ? (int)point.isCore() : Data::NOISE) << ", ";
        outFile << point.getClass() << ", ";
        outFile << point.getNeighbourIds().size();
        
        for (auto id : point.getNeighbourIds())
        {
            outFile << ", " << id;
        }

        outFile << std::endl;
    }

    outFile.close();
}

std::string Dbscan::getEpsilonView() const
{
    return "eps: " + std::to_string(_eps) + '\n';
}

void Dbscan::saveStatFile() const
{
    std::ofstream outFile{buildResultFilename(STAT_PREFIX)};
    std::string dataFilename = _filePath.substr(_filePath.find_last_of("/\\") + 1);
    outFile << "Data filename: " << dataFilename << std::endl;

    int dimension = _points[0].getCoordinates().size();
    outFile << "Points dimension: " << dimension << std::endl;

    int pointsNumber = _points.size();
    outFile << "Points number: " << pointsNumber << std::endl;
    outFile << "minPoints: " << _minPoints << std::endl;
    outFile << getEpsilonView();
    outFile << getReferencePointView();

    outFile << std::endl;

    outFile << "data loading time: " << _stats.timeStats.dataLoadingTime << " microseconds" << std::endl;
    outFile << "normalizing time: " << _stats.timeStats.normalizingTime << " microseconds" << std::endl;
    outFile << "reference distance calculations time: " << _stats.timeStats.referenceDistanceCalculationsTime << " microseconds" << std::endl;
    outFile << "points sorting time: " << _stats.timeStats.pointsSortingTime << " microseconds" << std::endl;
    outFile << "output saving time: " << _stats.timeStats.outputSavingTime << " microseconds" << std::endl;
    outFile << "clustering algorithm time: " << _stats.timeStats.clusteringAlgorithmTime << " microseconds" << std::endl;

    outFile << std::endl;

    outFile << "distance calculations count: " << _stats.operationStats.distanceCalculationsCount << std::endl;
    outFile << "triangle inequality filter count: " << _stats.operationStats.triangleInequalityFilterCount << std::endl;

    outFile << std::endl;

    outFile << "classes number: " << getClassNumber() << std::endl;
    outFile << "core points number: " << getCorePointsNumber() << std::endl;
    outFile << "reachable points number: " << getReachablePointsNumber() << std::endl;
    outFile << "noise points number: " << getNoisePointsNumber() << std::endl;

    outFile << std::endl;

    outFile << "|TP|: " << _stats.scoreStats.truePositives << std::endl;
    outFile << "|TN|: " << _stats.scoreStats.trueNegatives << std::endl;
    outFile << "Number of pairs: " << _stats.scoreStats.pairsNumber << std::endl;
    outFile << "RAND index: " << _stats.scoreStats.randIndex << std::endl;

    outFile.close();
}

}

