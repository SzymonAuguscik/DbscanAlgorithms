#pragma once

namespace Results
{

struct TimeStats
{
    long dataLoadingTime{};
    long normalizingTime{};
    long referenceDistanceCalculationsTime{};
    long pointsSortingTime{};
    long outputSavingTime{};
    long clusteringAlgorithmTime{};
};

}

