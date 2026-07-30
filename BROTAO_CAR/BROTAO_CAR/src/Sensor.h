#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "DetectedObject.h"

class Sensor {
public:
    Sensor(std::string id, std::string name, double x, double y, double range);
    virtual ~Sensor() = default;

    // Getters
    const std::string& getId() const { return sensor_id_; }
    const std::string& getName() const { return name_; }
    double getX() const { return position_x_; }
    double getY() const { return position_y_; }
    double getRange() const { return range_; }

    // Setters
    void setId(const std::string& id) { sensor_id_ = id; }
    void setName(const std::string& name) { name_ = name; }
    void setPosition(double x, double y) { position_x_ = x; position_y_ = y; }
    void setRange(double range) { range_ = range; }

    // Pure virtual: simulate detection
    virtual std::vector<DetectedObject> detect() = 0;

    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const Sensor& sensor);

    // Static utility
    static double distance(const Sensor& s1, const Sensor& s2);

    // Type identification
    virtual std::string getType() const = 0;

protected:
    std::string sensor_id_;
    std::string name_;
    double position_x_;
    double position_y_;
    double range_;
};