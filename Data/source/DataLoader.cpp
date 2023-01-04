#include <iostream>
#include <DataLoader.hpp>
#include <fstream>
#include <sstream>

namespace Data
{

std::vector<Point> DataLoader::load() const 
{
    const auto p_ext = _filePath.substr(_filePath.find_last_of("."));
    // TODO
    // deal with multiple extentions
    // probably switch + enums

    if (p_ext == Data::CSV_FILE)
    {
        return loadCsv();
    }
    
    return loadArff();
}

std::vector<Point> DataLoader::loadCsv() const
{
    std::vector<Point> points{};
    std::fstream file{_filePath, std::ios::in};

    if (file.is_open())
    {
        std::string line;
        // skip header
        getline(file, line);

        while (getline(file, line))
        {
            Point point{};
            std::stringstream stream(line);
            std::string cell;
            
            while (getline(stream, cell, ','))
            {
                auto coordinate = std::stof(cell);
                point.addCoordinate(coordinate);
            }

            points.push_back(point);
        }
        return points;
    }
    // TODO
    // do something better
    std::cout << "Could not open the file!\n" << std::endl;
    return points;
}

// TODO
std::vector<Point> DataLoader::loadArff() const
{
    return std::vector<Point>{};
}

}