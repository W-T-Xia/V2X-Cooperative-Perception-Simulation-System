#include "FusionCenter.h"
#include "Sensor.h"
#include "FusionLogger.h"
#include "Exceptions.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>

FusionCenter::FusionCenter(std::vector<std::unique_ptr<Sensor>>& sensors)
    : sensors_(sensors) {
}

void FusionCenter::collectDetections() {
    current_detections_.clear();
    for (auto& sensor : sensors_) {
        auto detections = sensor->detect();
        current_detections_.insert(current_detections_.end(),
            detections.begin(), detections.end());
    }
    FusionLogger::instance().log("Collected " + std::to_string(current_detections_.size()) +
        " raw detections.", LogLevel::INFO);
}

void FusionCenter::setCurrentDetections(const std::vector<DetectedObject>& detections) {
    current_detections_ = detections;
    FusionLogger::instance().log("Set fixed detections: " + std::to_string(detections.size()) +
        " objects.", LogLevel::INFO);
}

void FusionCenter::printCurrentDetections() const {
    std::cout << "\n========================================\n";
    std::cout << " Current Raw Detections (" << current_detections_.size() << " objects)\n";
    for (const auto& obj : current_detections_) {
        std::cout << obj << "\n";
    }
    std::cout << "========================================\n";
}

void FusionCenter::fuse() {
    if (current_detections_.empty()) {
        throw FusionException("No cached detections. Please run detection first.");
    }
    FusionLogger::instance().log("Starting fusion...", LogLevel::INFO);

    const double ASSOCIATION_THRESHOLD = 1.5;
    int n = static_cast<int>(current_detections_.size());
    std::vector<bool> used(n, false);
    fused_objects_.clear();

    struct Pair {
        double dist;
        int i, j;
        bool operator<(const Pair& o) const {
            if (std::abs(dist - o.dist) > 1e-9) return dist < o.dist;
            return std::min(i, j) < std::min(o.i, o.j);
        }
    };
    std::vector<Pair> candidates;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (current_detections_[i].type == current_detections_[j].type) {
                double d = euclideanDistance(current_detections_[i], current_detections_[j]);
                if (d < ASSOCIATION_THRESHOLD) {
                    candidates.push_back({ d, i, j });
                }
            }
        }
    }
    std::sort(candidates.begin(), candidates.end());

    std::vector<int> groupId(n, -1);
    int nextGroup = 0;
    for (const auto& p : candidates) {
        if (!used[p.i] && !used[p.j]) {
            used[p.i] = used[p.j] = true;
            groupId[p.i] = groupId[p.j] = nextGroup++;
        }
    }

    std::vector<std::vector<int>> groups(nextGroup);
    for (int i = 0; i < n; ++i) {
        if (groupId[i] >= 0) {
            groups[groupId[i]].push_back(i);
        }
    }

    for (auto& group : groups) {
        std::sort(group.begin(), group.end(), [&](int a, int b) {
            return current_detections_[a].object_id < current_detections_[b].object_id;
            });
        DetectedObject merged = current_detections_[group[0]];
        for (size_t k = 1; k < group.size(); ++k) {
            merged = merged + current_detections_[group[k]];
        }
        fused_objects_.push_back(merged);
        FusionLogger::instance().log("Fused group of " + std::to_string(group.size()) +
            " -> ID " + std::to_string(merged.object_id), LogLevel::INFO);
    }

    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            fused_objects_.push_back(current_detections_[i]);
            FusionLogger::instance().log("Unassociated: ID " + std::to_string(current_detections_[i].object_id),
                LogLevel::INFO);
        }
    }

    FusionLogger::instance().log("Fusion complete. Total fused objects: " +
        std::to_string(fused_objects_.size()), LogLevel::INFO);
}

void FusionCenter::printFusedObjects() const {
    std::cout << "========================================\n";
    std::cout << " Fused Global Object List (" << fused_objects_.size() << " objects)\n";
    for (const auto& obj : fused_objects_) {
        std::cout << obj << "\n";
    }
    std::cout << "========================================\n";
}

DetectedObject* FusionCenter::findObjectById(int id) {
    for (auto& obj : fused_objects_) {
        if (obj.object_id == id) return &obj;
    }
    return nullptr;
}

void FusionCenter::saveFusedObjects(const std::string& filename) const {
    std::ofstream ofs(filename);
    if (!ofs) throw ConfigException("Cannot open file: " + filename);
    ofs << "# Fused object list\n";
    for (const auto& obj : fused_objects_) {
        ofs << obj.object_id << ","
            << objectTypeToString(obj.type) << ","
            << obj.position_x << "," << obj.position_y << ","
            << obj.velocity_x << "," << obj.velocity_y << ","
            << obj.timestamp << "," << obj.confidence << ","
            << obj.sensor_source << "," << obj.detection_count << "\n";
    }
    FusionLogger::instance().log("Fused objects saved to " + filename, LogLevel::INFO);
}