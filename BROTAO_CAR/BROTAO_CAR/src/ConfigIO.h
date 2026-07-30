#pragma once
#include <vector>
#include <memory>
#include "Sensor.h"

void saveConfig(const std::string& filename, const std::vector<std::unique_ptr<Sensor>>& sensors);
std::vector<std::unique_ptr<Sensor>> loadConfig(const std::string& filename);