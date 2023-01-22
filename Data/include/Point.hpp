#include <PointInterface.hpp>
#include <vector>

#pragma once

namespace Data
{

constexpr int NO_CLASS{-2};
constexpr int NOISE{-1};
constexpr int NO_ID{-99};

class Point : public PointInterface
{
public:
    Point() : _id{NO_ID}, _class{NO_CLASS}, _isCore{false}, _calculationsCount{0} {};
    Point(std::vector<double> p_coordinates) : _id{NO_ID}, _class{NO_CLASS}, _isCore{false}, _calculationsCount{0}, _coordinates{p_coordinates} {}

    void setId(int) override;
    int getId() const override;
    void setClass(int) override;
    int getClass() const override;
    void setOriginalClass(int) override;
    int getOriginalClass() const override;
    void setCore() override;
    bool isCore() const override;
    void addCoordinate(double) override;
    std::vector<double> getCoordinates() const override;
    void addNeighbourId(int) override;
    std::vector<int> getNeighbourIds() const override;
    void incrementCalculationsCount() override;
    int getCalculationsCount() const override;

    friend void normalizePoint(Point&);
private:
    int _id;
    int _class;
    int _originalClass;
    bool _isCore;
    int _calculationsCount;
    std::vector<double> _coordinates{};
    std::vector<int> _neighbourIds{};
};

}

