#include <Point.hpp>
#include <vector>
#include <map>

#pragma once

namespace Data
{

constexpr double ZERO{0};

bool operator==(const Point&, const Point&);
bool operator<(const Point&, const Point&);
double getDistance(const Point&, const Point&);
double getLength(const Point&);
double getCosSim(const Point&, const Point&, std::map<Data::Point, double>);
double getCosSimCompletion(const Point&, const Point&, std::map<Data::Point, double>);
void normalizePoint(Point&);
void normalizePoints(std::vector<Point>&);

}

