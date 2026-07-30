#include "ConfigIO.h"
#include "VehicleCamera.h"
#include "RoadCamera.h"
#include "SensorFactory.h"
#include "Exceptions.h"
#include <fstream>
#include <sstream>

void saveConfig(const std::string& filename, const std::vector<std::unique_ptr<Sensor>>& sensors) {
    std::ofstream ofs(filename);
    if (!ofs) throw ConfigException("Cannot open file: " + filename);
    ofs << "# V2X Cooperative Perception System Sensor Configuration\n";
    for (const auto& s : sensors) {
        if (auto vc = dynamic_cast<VehicleCamera*>(s.get())) {
            ofs << "VehicleCamera,"
                << vc->getId() << ","
                << vc->getName() << ","
                << vc->getX() << "," << vc->getY() << ","
                << vc->getRange() << ","
                << vc->getHeading() << "," << vc->getFov() << "\n";
        }
        else if (auto rc = dynamic_cast<RoadCamera*>(s.get())) {
            ofs << "RoadCamera,"
                << rc->getId() << ","
                << rc->getName() << ","
                << rc->getX() << "," << rc->getY() << ","
                << rc->getRange() << ","
                << rc->getRoadsideId() << "," << rc->getCoveredLanes() << "\n";
        }
    }
}

std::vector<std::unique_ptr<Sensor>> loadConfig(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs) throw ConfigException("Cannot open file: " + filename);
    std::vector<std::unique_ptr<Sensor>> sensors;
    std::string line;
    int lineNo = 0;
    while (std::getline(ifs, line)) {
        ++lineNo;
        if (line.empty() || line[0] == '#') continue;
        std::istringstream ss(line);
        std::string type;
        if (!std::getline(ss, type, ',')) {
            throw ConfigException("Line " + std::to_string(lineNo) + ": format error");
        }
        std::vector<std::string> fields;
        std::string field;
        while (std::getline(ss, field, ',')) {
            fields.push_back(field);
        }
        try {
            auto sensor = createSensor(type, fields);
            sensors.push_back(std::move(sensor));
        }
        catch (const std::exception& e) {
            throw ConfigException("Line " + std::to_string(lineNo) + ": " + e.what());
        }
    }
    return sensors;
}