#include <iostream>
#include <DbscanCosCompletion.hpp>

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

    std::cout << "DbscanCosCompletion" << std::endl;

    Algorithms::DbscanCosCompletion dbscanCosCompletion{minPoints, 1 - eps, filename};

    dbscanCosCompletion.performClustering();
    dbscanCosCompletion.printAllPoints();
    dbscanCosCompletion.printPointsByType();
    dbscanCosCompletion.printStats();
    
    return 0;
}

