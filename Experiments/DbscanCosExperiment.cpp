#include <iostream>
#include <DbscanCos.hpp>

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

    Algorithms::DbscanCos dbscanCos{minPoints, eps, filename};

    dbscanCos.performClustering();
    
    return 0;
}

