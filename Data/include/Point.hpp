#include <PointInterface.hpp>
#include <vector>

#pragma once

namespace Data
{

constexpr int NO_CLASS{-1};
constexpr int NOISE{-2};

class Point : public PointInterface
{
public:
    Point() : _class{NO_CLASS}, _isCore{false} {};
    Point(std::vector<double> p_coordinates) : _class{NO_CLASS}, _isCore{false}, _coordinates{p_coordinates} {}

    void setClass(int) override;
    int getClass() const override;
    void setCore() override;
    bool isCore() const override;
    void addCoordinate(double) override;
    std::vector<double> getCoordinates() const override;

    friend void normalizePoint(Point&);
private:
    int _class;
    bool _isCore;
    std::vector<double> _coordinates{};
};

}

