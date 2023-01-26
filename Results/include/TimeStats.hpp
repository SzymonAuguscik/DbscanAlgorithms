#pragma once

namespace Results
{

// TODO
// fix time narrowing
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

