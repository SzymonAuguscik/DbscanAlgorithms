#include <iostream>
#include <TiDbscanEucNorm.hpp>
#include <cmath>

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        std::cerr << "Not enough arguments!" << std::endl;
        return 1;
    }

    std::string filename{argv[1]};
    double eps{std::stod(argv[2])};
    int minPoints{std::stoi(argv[3])};

    std::cout << std::endl << "TiDbscanEucNorm" << std::endl;

    Algorithms::TiDbscanEucNorm tiDbscanEucNorm{minPoints, std::sqrt(2 - 2 * eps), filename, Data::Point{{1,0}}};

    tiDbscanEucNorm.performClustering();
    tiDbscanEucNorm.printAllPoints();
    tiDbscanEucNorm.printPointsByType();
    tiDbscanEucNorm.printStats();
    
    return 0;
}

