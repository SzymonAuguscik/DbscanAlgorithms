#include <iostream>
#include <DataLoader.hpp>
#include <fstream>
#include <sstream>
#include <algorithm>

namespace
{

}

namespace Data
{

std::vector<Point> DataLoader::load() 
{
    const auto p_ext = _filePath.substr(_filePath.find_last_of("."));
    // TODO
    // deal with multiple extentions
    // probably switch + enums
    std::function<void (std::fstream&, std::string&)> skipHeader = (p_ext == Data::CSV_FILE) ?
                                                                  std::bind(&DataLoader::skipCsvHeader,
                                                                            this,
                                                                            std::placeholders::_1,
                                                                            std::placeholders::_2) :
                                                                  std::bind(&DataLoader::skipArffHeader,
                                                                            this,
                                                                            std::placeholders::_1,
                                                                            std::placeholders::_2);
    
    return loadFile(skipHeader);
}

std::vector<Point> DataLoader::loadFile(std::function<void(std::fstream&, std::string&)> p_skipHeader) const
{
    std::vector<Point> points{};
    std::fstream file{_filePath, std::ios::in};

    if (file.is_open())
    {
        std::string line;
        p_skipHeader(file, line);
        int lineNumber = 0;
        int count;

        while (getline(file, line))
        {
            Point point{};
            std::stringstream stream(line);
            std::string cell;
            count = 0;

            while (getline(stream, cell, ','))
            {

                if (count != std::count(line.begin(), line.end(), ','))
                {
                    count++;
                    auto coordinate = std::stod(cell);
                    point.addCoordinate(coordinate);
                    continue;
                }

                point.setOriginalClass(std::stoi(cell));
            }

            point.setId(lineNumber);
            points.push_back(point);
            lineNumber++;
        }
        return points;
    }
    // TODO
    // do something better
    std::cout << "Could not open the file!\n" << std::endl;
    return points;
}

void DataLoader::skipCsvHeader(std::fstream& p_file, std::string& p_line)
{
    getline(p_file, p_line);
}

void DataLoader::skipArffHeader(std::fstream& p_file, std::string& p_line)
{
    do
    {
        getline(p_file, p_line);
    } while (p_line.find("@DATA") == std::string::npos && p_line.find("@data") == std::string::npos);
}


}