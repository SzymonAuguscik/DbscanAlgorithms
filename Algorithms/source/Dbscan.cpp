#include <Dbscan.hpp>
#include <DataLoader.hpp>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <DataUtils.hpp>
#include <deque>
#include <chrono>

namespace
{

void printPoints(const std::vector<Data::Point>& p_points)
{
    for (auto p : p_points)
    {
        for (auto c : p.getCoordinates())
        {
            std::cout << c << " ";
        }
        std::cout << "Class: " << p.getClass() << ", Core: " << p.isCore() << std::endl;
    }
}

}

namespace Data
{

double getDistance(const Point&, const Point&);

}

namespace Algorithms
{

void Dbscan::performClustering()
{
    std::cout << "eps=" << _eps << std::endl;
    const auto startTime = std::chrono::high_resolution_clock::now();
    int currentClass{0};

    for (auto& point : _points)
    {
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
    _stats.timeStats.clusteringTime = elapsedTime.count();
}

void Dbscan::loadData()
{
    auto startTime = std::chrono::high_resolution_clock::now();
    _points = _dataLoader->load();
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

void Dbscan::setNeighbourhood(const Data::Point& p_centralPoint,
                              const std::vector<Data::Point>& p_dataset,
                              std::vector<Data::Point>& p_potentialNeighbours)
{
    p_potentialNeighbours.clear();
    std::copy_if(p_dataset.begin(),
                 p_dataset.end(),
                 std::back_inserter(p_potentialNeighbours),
                 [this, &p_centralPoint] (const auto& p_point)
                 {
                     _stats.operationStats.distanceCalculationsCount++;
                     return Data::getDistance(p_centralPoint, p_point) <= _eps;
                 });
}

void Dbscan::sortPoints()
{
    std::sort(_points.begin(),
              _points.end());
}

void Dbscan::printAllPoints()
{
    std::cout << "All points: " << std::endl;
    printPoints(_points);
}

void Dbscan::printPointsByType()
{
    std::cout << "Core points: " << std::endl;
    printPoints(getCorePoints());
    std::cout << "Reachable points: " << std::endl;
    printPoints(getReachablePoints());
    std::cout << "Noise points: " << std::endl;
    printPoints(getNoisePoints());
}

void Dbscan::printStats()
{
    std::cout << "Overall stats" << std::endl;
    std::cout << "  Time stats" << std::endl;
    std::cout << "  - data loading time = " << _stats.timeStats.dataLoadingTime << " us" << std::endl;
    std::cout << "  - clustering time = " << _stats.timeStats.clusteringTime << " us" << std::endl;
    std::cout << "  - points sorting time = " << _stats.timeStats.pointsSortingTime << " us" << std::endl;
    std::cout << "  - results printing time = " << _stats.timeStats.resultsPrintingTime << " us" << std::endl;
    std::cout << "  Operations stats" << std::endl;
    std::cout << "  - distance calculations count = " << _stats.operationStats.distanceCalculationsCount << std::endl;
    std::cout << "  - triangle inequality filter count = " << _stats.operationStats.triangleInequalityFilterCount << std::endl;
}

std::vector<Data::Point> Dbscan::getNoisePoints()
{
    std::vector<Data::Point> noisePoints{};
    std::copy_if(_points.begin(),
                 _points.end(),
                 std::back_inserter(noisePoints),
                 [] (const Data::Point& p_point) { return p_point.getClass() == Data::NOISE; });
    return noisePoints;
}

std::vector<Data::Point> Dbscan::getReachablePoints()
{
    std::vector<Data::Point> reachablePoints{};
    std::copy_if(_points.begin(),
                 _points.end(),
                 std::back_inserter(reachablePoints),
                 [] (const Data::Point& p_point) { return !p_point.isCore() && p_point.getClass() != Data::NOISE; });
    return reachablePoints;
}

std::vector<Data::Point> Dbscan::getCorePoints()
{
    std::vector<Data::Point> corePoints{};
    std::copy_if(_points.begin(),
                 _points.end(),
                 std::back_inserter(corePoints),
                 [] (const Data::Point& p_point) { return p_point.isCore(); });
    return corePoints;
}

}

