#pragma once

namespace Results
{

struct TimeStats
{
    int dataLoadingTime{};
    int normalizingTime{};
    int referenceDistanceCalculationsTime{};
    int pointsSortingTime{};
    int outputSavingTime{};
    int clusteringAlgorithmTime{};
};

}

