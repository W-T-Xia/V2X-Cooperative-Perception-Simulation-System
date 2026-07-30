#include "VehicleCamera.h"
#include <cmath>
#include <random>
#define _USE_MATH_DEFINES

VehicleCamera::VehicleCamera(std::string id, std::string name, double x, double y,
    double range, double heading, double fov, int resW, int resH)
    : Sensor(std::move(id), std::move(name), x, y, range),
    heading_(heading), fov_(fov),
    resolution_width_(resW), resolution_height_(resH) {
}

std::vector<DetectedObject> VehicleCamera::detect() {
    std::vector<DetectedObject> objects;
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> countDist(1, 3);
    int num = countDist(rng);
    std::uniform_real_distribution<double> angleDist(-fov_ / 2.0, fov_ / 2.0);
    std::uniform_real_distribution<double> rangeDist(5.0, range_);

    for (int i = 0; i < num; ++i) {
        double angle = heading_ + angleDist(rng);
        double rad = angle * M_PI / 180.0;
        double dist = rangeDist(rng);
        double gx = position_x_ + dist * std::cos(rad);
        double gy = position_y_ + dist * std::sin(rad);

        DetectedObject obj;
        obj.object_id = 1000 + i;
        obj.type = (i % 2 == 0) ? ObjectType::VEHICLE : ObjectType::PEDESTRIAN;
        obj.position_x = gx;
        obj.position_y = gy;
        obj.velocity_x = 5.0;
        obj.velocity_y = 0.0;
        obj.timestamp = 1;
        obj.confidence = 0.8 + 0.15 * (i % 2);
        obj.sensor_source = sensor_id_;
        obj.detection_count = 1;
        objects.push_back(obj);
    }
    return objects;
}

std::ostream& operator<<(std::ostream& os, const VehicleCamera& cam) {
    os << static_cast<const Sensor&>(cam);
    os << ", Heading: " << cam.heading_ << "¢X, FOV: " << cam.fov_ << "¢X";
    return os;
}