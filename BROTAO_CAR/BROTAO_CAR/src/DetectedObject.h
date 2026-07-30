#pragma once
#include <string>
#include <iostream>

enum class ObjectType { VEHICLE, PEDESTRIAN, UNKNOWN };

inline std::string objectTypeToString(ObjectType t) {
    switch (t) {
    case ObjectType::VEHICLE:   return "VEHICLE";
    case ObjectType::PEDESTRIAN: return "PEDESTRIAN";
    default:                     return "UNKNOWN";
    }
}

struct DetectedObject {
    int object_id = 0;
    ObjectType type = ObjectType::UNKNOWN;
    double position_x = 0.0;
    double position_y = 0.0;
    double velocity_x = 0.0;
    double velocity_y = 0.0;
    double timestamp = 0.0;
    double confidence = 0.0;
    std::string sensor_source;
    int detection_count = 1;

    bool operator==(const DetectedObject& other) const;

    DetectedObject operator+(const DetectedObject& other) const;

    friend std::ostream& operator<<(std::ostream& os, const DetectedObject& obj);
};

double euclideanDistance(const DetectedObject& a, const DetectedObject& b);