#include <DataLoaderInterface.hpp>
#include <string>

#pragma once

namespace Data
{

class DataLoader : public DataLoaderInterface
{
public:
    DataLoader(const std::string& p_filePath) : _filePath{p_filePath}
    { }

    std::vector<Point> load() const override;
private:
    std::string _filePath;

    std::vector<Point> loadCsv() const;
    std::vector<Point> loadArff() const;
};

}