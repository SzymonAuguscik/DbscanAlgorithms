#include <DataLoaderInterface.hpp>
#include <string>
#include <functional>

#pragma once

namespace Data
{

class DataLoader : public DataLoaderInterface
{
public:
    DataLoader(const std::string& p_filePath) : _filePath{p_filePath}
    { }

    std::vector<Point> load() override;
private:
    std::vector<Point> loadFile(std::function<void(std::fstream&, std::string&)>) const;
    void skipCsvHeader(std::fstream&, std::string&);
    void skipArffHeader(std::fstream&, std::string&);

    std::string _filePath;
};

}