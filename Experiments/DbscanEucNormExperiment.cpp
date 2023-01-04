#include <iostream>
#include <DbscanEucNorm.hpp>
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

    std::cout << "DbscanEucNorm" << std::endl;

    Algorithms::DbscanEucNorm dbscanEucNorm{minPoints, std::sqrt(2 - 2 * eps), filename};

    dbscanEucNorm.performClustering();
    dbscanEucNorm.printAllPoints();
    dbscanEucNorm.printPointsByType();
    dbscanEucNorm.printStats();
    
    return 0;
}

