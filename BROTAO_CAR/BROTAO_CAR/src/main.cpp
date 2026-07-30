#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <limits>
#include <algorithm>

#include "Sensor.h"
#include "VehicleCamera.h"
#include "RoadCamera.h"
#include "DetectedObject.h"
#include "FusionCenter.h"
#include "SensorFactory.h"
#include "ConfigIO.h"
#include "FusionLogger.h"
#include "SensorContainer.h"
#include "Exceptions.h"

void printMenu() {
    std::cout << "\n========================================\n";
    std::cout << " V2X Cooperative Perception System\n";
    std::cout << " (Onboard + Roadside Sensor Fusion)\n";
    std::cout << "========================================\n";
    std::cout << "1. Add sensor (Vehicle/Roadside)\n";
    std::cout << "2. Display / Find sensors\n";
    std::cout << "3. Simulate sensor detections (generate targets)\n";
    std::cout << "4. Execute perception fusion\n";
    std::cout << "5. View fused global target list\n";
    std::cout << "6. Find fused target by ID\n";
    std::cout << "7. Save / Load sensor configuration\n";
    std::cout << "8. Exit system\n";
    std::cout << "9. Save fusion results to file\n";
    std::cout << "========================================\n";
}

void loadFixedScenario(std::vector<std::unique_ptr<Sensor>>& sensors,
    std::vector<DetectedObject>& detections) {
    sensors.clear();
    detections.clear();

    auto vc = std::make_unique<VehicleCamera>("S001", "FrontCam", 0, 0, 50, 0, 90);
    auto rc = std::make_unique<RoadCamera>("R001", "CrossCam", 60, 30, 35, "R1", 2);
    sensors.push_back(std::move(vc));
    sensors.push_back(std::move(rc));

    // Target A
    DetectedObject a;
    a.object_id = 101;
    a.type = ObjectType::VEHICLE;
    a.position_x = 20; a.position_y = 0;
    a.velocity_x = 10; a.velocity_y = 0;
    a.timestamp = 1;
    a.confidence = 0.90;
    a.sensor_source = "S001";
    a.detection_count = 1;
    detections.push_back(a);

    // Target B (vehicle)
    DetectedObject b1;
    b1.object_id = 102;
    b1.type = ObjectType::VEHICLE;
    b1.position_x = 38.2; b1.position_y = 7.6;
    b1.velocity_x = 5; b1.velocity_y = 0;
    b1.timestamp = 1;
    b1.confidence = 0.85;
    b1.sensor_source = "S001";
    b1.detection_count = 1;
    detections.push_back(b1);

    // Target B (roadside)
    DetectedObject b2;
    b2.object_id = 201;
    b2.type = ObjectType::VEHICLE;
    b2.position_x = 38.8; b2.position_y = 8.1;
    b2.velocity_x = 5; b2.velocity_y = 0;
    b2.timestamp = 1;
    b2.confidence = 0.80;
    b2.sensor_source = "R001";
    b2.detection_count = 1;
    detections.push_back(b2);

    // Target C
    DetectedObject c;
    c.object_id = 202;
    c.type = ObjectType::PEDESTRIAN;
    c.position_x = 58; c.position_y = 8;
    c.velocity_x = 0; c.velocity_y = -1;
    c.timestamp = 1;
    c.confidence = 0.88;
    c.sensor_source = "R001";
    c.detection_count = 1;
    detections.push_back(c);
}

int main() {
    FusionLogger::instance().log("System started", LogLevel::INFO);
    std::vector<std::unique_ptr<Sensor>> sensors;

    auto fusion = std::make_unique<FusionCenter>(sensors);
    bool hasCachedDetections = false;

    while (true) {
        printMenu();
        std::cout << "Enter command number: ";
        int cmd;
        std::cin >> cmd;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        try {
            switch (cmd) {
            case 1: {
                std::cout << "\n--- Add Sensor ---\n";
                std::cout << "Sensor type:\n1. VehicleCamera\n2. RoadCamera\nEnter type number: ";
                int type;
                std::cin >> type;
                std::string typeStr = (type == 1) ? "VehicleCamera" : "RoadCamera";

                std::string id, name;
                double x, y, range;
                std::cout << "Sensor ID: ";
                std::cin >> id;
                std::cout << "Sensor name: ";
                std::cin.ignore(); std::getline(std::cin, name);
                std::cout << "Position (x y): ";
                std::cin >> x >> y;
                std::cout << "Range (meters): ";
                std::cin >> range;

                std::vector<std::string> fields;
                fields.push_back(id);
                fields.push_back(name);
                fields.push_back(std::to_string(x));
                fields.push_back(std::to_string(y));
                fields.push_back(std::to_string(range));

                if (type == 1) {
                    double heading, fov;
                    std::cout << "Heading (deg): ";
                    std::cin >> heading;
                    std::cout << "FOV (deg): ";
                    std::cin >> fov;
                    fields.push_back(std::to_string(heading));
                    fields.push_back(std::to_string(fov));
                }
                else {
                    std::string rsid;
                    int lanes;
                    std::cout << "Roadside ID: ";
                    std::cin >> rsid;
                    std::cout << "Covered lanes: ";
                    std::cin >> lanes;
                    fields.push_back(rsid);
                    fields.push_back(std::to_string(lanes));
                }

                auto sensor = createSensor(typeStr, fields);
                sensors.push_back(std::move(sensor));
                std::cout << typeStr << " added successfully.\n";
                FusionLogger::instance().log("Added sensor " + id, LogLevel::INFO);
                break;
            }
            case 2: {
                std::cout << "\n1. List all sensors\n2. Find sensor by ID\nChoose: ";
                int sub;
                std::cin >> sub;
                if (sub == 1) {
                    int vcCount = 0, rcCount = 0;
                    for (const auto& s : sensors) {
                        if (dynamic_cast<VehicleCamera*>(s.get())) ++vcCount;
                        else if (dynamic_cast<RoadCamera*>(s.get())) ++rcCount;
                    }
                    std::cout << "\n========================================\n";
                    std::cout << "Total sensors: " << sensors.size()
                        << " (Vehicle: " << vcCount << ", Roadside: " << rcCount << ")\n";
                    for (const auto& s : sensors) {
                        if (auto vc = dynamic_cast<VehicleCamera*>(s.get()))
                            std::cout << *vc << "\n";
                        else if (auto rc = dynamic_cast<RoadCamera*>(s.get()))
                            std::cout << *rc << "\n";
                    }
                    std::cout << "========================================\n";
                }
                else if (sub == 2) {
                    std::cout << "Enter sensor ID: ";
                    std::string sid;
                    std::cin >> sid;
                    auto it = std::find_if(sensors.begin(), sensors.end(),
                        [&](const std::unique_ptr<Sensor>& s) { return s->getId() == sid; });
                    if (it == sensors.end()) {
                        throw SensorException("Sensor with ID " + sid + " not found.");
                    }
                    if (auto vc = dynamic_cast<VehicleCamera*>(it->get()))
                        std::cout << *vc << "\n";
                    else if (auto rc = dynamic_cast<RoadCamera*>(it->get()))
                        std::cout << *rc << "\n";
                }
                break;
            }
            case 3: {
                std::cout << "Select mode:\n1. Random mode\n2. Fixed test scenario\nEnter: ";
                int mode;
                std::cin >> mode;
                if (mode == 2) {
                    std::vector<DetectedObject> fixedDets;
                    loadFixedScenario(sensors, fixedDets);
                    fusion = std::make_unique<FusionCenter>(sensors);
                    fusion->setCurrentDetections(fixedDets);
                    hasCachedDetections = true;
                    std::cout << "Fixed scenario loaded.\n";
                    fusion->printCurrentDetections();  
                }
                else {
                    if (sensors.empty()) {
                        std::cout << "No sensors available. Please add sensors first.\n";
                        break;
                    }
                    fusion->collectDetections();
                    hasCachedDetections = true;
                    std::cout << "Random detections generated.\n";
                    fusion->printCurrentDetections();  
                }
                break;
            }
            case 4: {
                if (!hasCachedDetections) {
                    std::cout << "Please run detection first (menu 3).\n";
                    break;
                }
                fusion->fuse();
                std::cout << "Fusion complete. Fused objects: " << fusion->getFusedObjects().size() << "\n";
                break;
            }
            case 5: {
                fusion->printFusedObjects();
                break;
            }
            case 6: {
                std::cout << "Enter object ID: ";
                int id;
                std::cin >> id;
                auto* obj = fusion->findObjectById(id);
                if (obj) {
                    std::cout << *obj << "\n";
                }
                else {
                    std::cout << "No fused object with ID " << id << " found.\n";
                }
                break;
            }
            case 7: {
                std::cout << "1. Save config\n2. Load config\nChoose: ";
                int sub;
                std::cin >> sub;
                if (sub == 1) {
                    std::string filename;
                    std::cout << "Filename: ";
                    std::cin >> filename;
                    saveConfig(filename, sensors);
                    std::cout << "Configuration saved to " << filename << "\n";
                }
                else if (sub == 2) {
                    std::string filename;
                    std::cout << "Filename: ";
                    std::cin >> filename;
                    auto newSensors = loadConfig(filename);
                    sensors = std::move(newSensors);
                    fusion = std::make_unique<FusionCenter>(sensors);
                    hasCachedDetections = false;
                    std::cout << "Configuration loaded (" << sensors.size() << " sensors).\n";
                }
                break;
            }
            case 8: {
                FusionLogger::instance().log("System exit", LogLevel::INFO);
                return 0;
            }
            case 9: {
                std::string filename;
                std::cout << "Filename: ";
                std::cin >> filename;
                fusion->saveFusedObjects(filename);
                std::cout << "Fusion results saved.\n";
                break;
            }
            default:
                std::cout << "Invalid command. Try again.\n";
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            FusionLogger::instance().log(std::string("Exception: ") + e.what(), LogLevel::ERROR);
        }
    }
    return 0;
}