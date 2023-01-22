#include <OperationsStats.hpp>
#include <TimeStats.hpp>
#include <ScoreStats.hpp>

#pragma once

namespace Results
{

struct OverallStats
{
    OperationStats operationStats{};
    TimeStats timeStats{};
    ScoreStats scoreStats{};
};

}

