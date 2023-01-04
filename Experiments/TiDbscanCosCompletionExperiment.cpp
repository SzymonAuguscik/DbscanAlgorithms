#include <iostream>
#include <TiDbscanCosCompletion.hpp>

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

    std::cout << "TiDbscanCosCompletion" << std::endl;

    Algorithms::TiDbscanCosCompletion tiDbscanCosCompletion{minPoints, 1 - eps, filename, Data::Point{{1,0}}};

    tiDbscanCosCompletion.performClustering();
    tiDbscanCosCompletion.printAllPoints();
    tiDbscanCosCompletion.printPointsByType();
    tiDbscanCosCompletion.printStats();
    
    return 0;
}

