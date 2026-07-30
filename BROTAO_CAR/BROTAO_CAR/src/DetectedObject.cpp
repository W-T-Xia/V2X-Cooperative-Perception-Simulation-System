#include "DetectedObject.h"
#include <set>
#include <sstream>
#include <cmath>
#include <algorithm>

bool DetectedObject::operator==(const DetectedObject& other) const {
    return object_id == other.object_id;
}

DetectedObject DetectedObject::operator+(const DetectedObject& other) const {
    int total = detection_count + other.detection_count;
    DetectedObject result;
    result.object_id = std::min(object_id, other.object_id);
    result.type = type;  // caller guarantees same type

    result.position_x = (position_x * detection_count + other.position_x * other.detection_count) / total;
    result.position_y = (position_y * detection_count + other.position_y * other.detection_count) / total;
    result.velocity_x = (velocity_x * detection_count + other.velocity_x * other.detection_count) / total;
    result.velocity_y = (velocity_y * detection_count + other.velocity_y * other.detection_count) / total;

    result.timestamp = std::max(timestamp, other.timestamp);
    result.confidence = (confidence * detection_count + other.confidence * other.detection_count) / total;
    result.detection_count = total;

    // merge sensor sources (deduplicate and sort)
    std::set<std::string> sources;
    auto addSources = [&](const std::string& srcList) {
        std::istringstream iss(srcList);
        std::string token;
        while (std::getline(iss, token, '+')) {
            if (!token.empty()) sources.insert(token);
        }
        };
    addSources(sensor_source);
    addSources(other.sensor_source);

    std::ostringstream oss;
    bool first = true;
    for (const auto& s : sources) {
        if (!first) oss << "+";
        oss << s;
        first = false;
    }
    result.sensor_source = oss.str();
    return result;
}

std::ostream& operator<<(std::ostream& os, const DetectedObject& obj) {
    os << "ID: " << obj.object_id
        << ", Type: " << objectTypeToString(obj.type)
        << ", Pos: (" << obj.position_x << ", " << obj.position_y << ")"
        << ", Vel: (" << obj.velocity_x << ", " << obj.velocity_y << ")"
        << ", Time: " << obj.timestamp
        << ", Conf: " << obj.confidence
        << ", Source: " << obj.sensor_source
        << ", Count: " << obj.detection_count;
    return os;
}

double euclideanDistance(const DetectedObject& a, const DetectedObject& b) {
    double dx = a.position_x - b.position_x;
    double dy = a.position_y - b.position_y;
    return std::sqrt(dx * dx + dy * dy);
}