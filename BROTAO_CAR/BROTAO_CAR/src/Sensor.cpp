#include "Sensor.h"
#include <cmath>

Sensor::Sensor(std::string id, std::string name, double x, double y, double range)
    : sensor_id_(std::move(id)), name_(std::move(name)),
    position_x_(x), position_y_(y), range_(range) {
}

std::ostream& operator<<(std::ostream& os, const Sensor& sensor) {
    os << "[" << sensor.getType() << "] ID: " << sensor.sensor_id_
        << ", Name: " << sensor.name_
        << ", Pos: (" << sensor.position_x_ << ", " << sensor.position_y_ << ")"
        << ", Range: " << sensor.range_ << "m";
    return os;
}

double Sensor::distance(const Sensor& s1, const Sensor& s2) {
    double dx = s1.position_x_ - s2.position_x_;
    double dy = s1.position_y_ - s2.position_y_;
    return std::sqrt(dx * dx + dy * dy);
}