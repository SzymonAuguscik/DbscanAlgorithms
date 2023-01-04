#include <DataUtils.hpp>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cmath>
#include <iterator>
#include <iostream>

namespace Data
{

bool operator==(const Point& p_left, const Point& p_right)
{
    return p_left.getCoordinates() == p_right.getCoordinates();
}

bool operator<(const Point& p_left, const Point& p_right)
{
    return p_left.getCoordinates()[0] < p_right.getCoordinates()[0];
}

double getDistance(const Point& p_left, const Point& p_right)
{
    std::vector<double> differences{};
    const auto& leftCoordinates = p_left.getCoordinates();
    const auto& rightCoordinates = p_right.getCoordinates();

    std::transform(leftCoordinates.begin(),
                   leftCoordinates.end(),
                   rightCoordinates.begin(),
                   std::back_inserter(differences),
                   std::minus<double>());

    return std::sqrt(std::accumulate(differences.begin(),
                                     differences.end(),
                                     ZERO,
                                     [] (double p_number1, double p_number2) { return p_number1 + p_number2 * p_number2; } ));
}

double getLength(const Point& p_point)
{
    const auto& coordinates = p_point.getCoordinates();
    return std::sqrt(std::accumulate(coordinates.begin(),
                                     coordinates.end(), 
                                     ZERO, 
                                     [] (double p_coordinate1, double p_coordinate2) { return p_coordinate1 + p_coordinate2 * p_coordinate2; }));
}

double getCosSim(const Point& p_left, const Point& p_right, std::map<Data::Point, double> p_lengths)
{
    const auto& leftCoordinates = p_left.getCoordinates();
    const auto& rightCoordinates = p_right.getCoordinates();

    if (leftCoordinates == rightCoordinates)
    {
        return 1.0;
    }

    std::vector<double> products{};

    std::transform(leftCoordinates.begin(),
                   leftCoordinates.end(),
                   rightCoordinates.begin(),
                   std::back_inserter(products),
                   std::multiplies<double>());

    double productSum = std::accumulate(products.begin(), products.end(), ZERO);
    
    return productSum / (p_lengths[p_left] * p_lengths[p_right]);
}

double getCosSimCompletion(const Point& p_left, const Point& p_right, std::map<Data::Point, double> p_lengths)
{
    return 1.0 - getCosSim(p_left, p_right, p_lengths);
}

void normalizePoint(Point& p_point)
{
    auto& coordinates = p_point._coordinates;
    const auto length = getLength(p_point);
    
    for (auto& coordinate : coordinates)
    {
        coordinate /= length;
    }
}

void normalizePoints(std::vector<Point>& p_points)
{
    std::for_each(p_points.begin(),
                  p_points.end(),
                  [] (Point& p_point) { normalizePoint(p_point); });
}

}

