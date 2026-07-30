#include "RoadCamera.h"
#include <random>
#include <cmath>
#define _USE_MATH_DEFINES

RoadCamera::RoadCamera(std::string id, std::string name, double x, double y,
    double range, std::string roadsideId, int lanes)
    : Sensor(std::move(id), std::move(name), x, y, range),
    roadside_id_(std::move(roadsideId)), covered_lanes_(lanes) {
}

std::vector<DetectedObject> RoadCamera::detect() {
    std::vector<DetectedObject> objects;
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> countDist(1, 4);
    int num = countDist(rng);
    std::uniform_real_distribution<double> angleDist(0, 2 * M_PI);
    std::uniform_real_distribution<double> rangeDist(5.0, range_);

    for (int i = 0; i < num; ++i) {
        double angle = angleDist(rng);
        double dist = rangeDist(rng);
        double gx = position_x_ + dist * std::cos(angle);
        double gy = position_y_ + dist * std::sin(angle);

        DetectedObject obj;
        obj.object_id = 2000 + i;
        obj.type = (i % 3 == 0) ? ObjectType::PEDESTRIAN : ObjectType::VEHICLE;
        obj.position_x = gx;
        obj.position_y = gy;
        obj.velocity_x = 0.0;
        obj.velocity_y = -2.0;
        obj.timestamp = 1;
        obj.confidence = 0.75 + 0.2 * (i % 2);
        obj.sensor_source = sensor_id_;
        obj.detection_count = 1;
        objects.push_back(obj);
    }
    return objects;
}

std::ostream& operator<<(std::ostream& os, const RoadCamera& cam) {
    os << static_cast<const Sensor&>(cam);
    os << ", Roadside ID: " << cam.roadside_id_ << ", Lanes: " << cam.covered_lanes_;
    return os;
}