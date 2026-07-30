#pragma once
#include "Sensor.h"

class VehicleCamera : public Sensor {
public:
    VehicleCamera(std::string id, std::string name, double x, double y,
        double range, double heading, double fov,
        int resW = 1920, int resH = 1080);

    std::vector<DetectedObject> detect() override;
    std::string getType() const override { return "VehicleCamera"; }

    double getHeading() const { return heading_; }
    double getFov() const { return fov_; }

    friend std::ostream& operator<<(std::ostream& os, const VehicleCamera& cam);

private:
    double heading_;   // degrees, 0 = +x axis, counter-clockwise
    double fov_;       // total field of view in degrees
    int resolution_width_;
    int resolution_height_;
};