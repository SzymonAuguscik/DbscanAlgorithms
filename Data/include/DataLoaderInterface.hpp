#include <string>
#include <vector>
#include <Point.hpp>

#pragma once

namespace Data
{

const std::string CSV_FILE{".csv"};
const std::string ARFF_FILE{".arff"};

class DataLoaderInterface
{
public:
    virtual std::vector<Point> load() const = 0;
};

}

