#include "SensorFactory.h"
#include "VehicleCamera.h"
#include "RoadCamera.h"
#include "Exceptions.h"

std::unique_ptr<Sensor> createSensor(const std::string& type,
    const std::vector<std::string>& fields) {
    if (type == "VehicleCamera") {
        if (fields.size() < 7) throw ConfigException("Insufficient parameters for VehicleCamera");
        std::string id = fields[0];
        std::string name = fields[1];
        double x = std::stod(fields[2]);
        double y = std::stod(fields[3]);
        double range = std::stod(fields[4]);
        double heading = std::stod(fields[5]);
        double fov = std::stod(fields[6]);
        return std::make_unique<VehicleCamera>(id, name, x, y, range, heading, fov);
    }
    else if (type == "RoadCamera") {
        if (fields.size() < 7) throw ConfigException("Insufficient parameters for RoadCamera");
        std::string id = fields[0];
        std::string name = fields[1];
        double x = std::stod(fields[2]);
        double y = std::stod(fields[3]);
        double range = std::stod(fields[4]);
        std::string rsid = fields[5];
        int lanes = std::stoi(fields[6]);
        return std::make_unique<RoadCamera>(id, name, x, y, range, rsid, lanes);
    }
    else {
        throw ConfigException("Unknown sensor type: " + type);
    }
}