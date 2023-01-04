#include <OperationsStats.hpp>
#include <TimeStats.hpp>

#pragma once

namespace Results
{

struct OverallStats
{
    OperationStats operationStats{};
    TimeStats timeStats{};
};

}

