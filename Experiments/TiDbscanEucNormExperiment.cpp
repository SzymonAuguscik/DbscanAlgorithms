#include <iostream>
#include <TiDbscanEucNorm.hpp>

int main(int argc, char *argv[])
{
    if (argc < 5)
    {
        std::cerr << "Not enough arguments!" << std::endl;
        return 1;
    }

    std::string filename{argv[1]};
    double eps{std::stod(argv[2])};
    int minPoints{std::stoi(argv[3])};
    std::string referencePointMode{argv[4]};

    Algorithms::TiDbscanEucNorm tiDbscanEucNorm{minPoints, eps, filename, referencePointMode};

    tiDbscanEucNorm.performClustering();
    
    return 0;
}

