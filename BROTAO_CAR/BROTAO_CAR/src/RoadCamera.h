#pragma once
#include "Sensor.h"
#include <string>

class RoadCamera : public Sensor {
public:
    RoadCamera(std::string id, std::string name, double x, double y,
        double range, std::string roadsideId, int lanes);

    std::vector<DetectedObject> detect() override;
    std::string getType() const override { return "RoadCamera"; }

    const std::string& getRoadsideId() const { return roadside_id_; }
    int getCoveredLanes() const { return covered_lanes_; }

    friend std::ostream& operator<<(std::ostream& os, const RoadCamera& cam);

private:
    std::string roadside_id_;
    int covered_lanes_;
};