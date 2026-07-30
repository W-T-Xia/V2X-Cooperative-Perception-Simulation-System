#pragma once
#include <vector>
#include <memory>
#include "DetectedObject.h"

class Sensor;

class FusionCenter {
public:
    explicit FusionCenter(std::vector<std::unique_ptr<Sensor>>& sensors);

    void collectDetections();
    void setCurrentDetections(const std::vector<DetectedObject>& detections);
    void fuse();
    void printFusedObjects() const;
    void printCurrentDetections() const;        
    DetectedObject* findObjectById(int id);
    void saveFusedObjects(const std::string& filename) const;

    const std::vector<DetectedObject>& getCurrentDetections() const { return current_detections_; }
    const std::vector<DetectedObject>& getFusedObjects() const { return fused_objects_; }

private:
    std::vector<std::unique_ptr<Sensor>>& sensors_;
    std::vector<DetectedObject> current_detections_;
    std::vector<DetectedObject> fused_objects_;
};