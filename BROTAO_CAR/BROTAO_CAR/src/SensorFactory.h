#pragma once
#include <memory>
#include <vector>
#include <string>
#include "Sensor.h"

// Simple factory function: creates a sensor from type string and field vector.
std::unique_ptr<Sensor> createSensor(const std::string& type,
    const std::vector<std::string>& fields);