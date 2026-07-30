V2X Cooperative Perception Simulation System
A C++ simulation system for Vehicle-to-Everything (V2X) cooperative perception, developed for the Object-Oriented Programming course at Tongji University.

https://img.shields.io/badge/C%252B%252B-17-blue.svg
https://img.shields.io/badge/CMake-3.10+-green.svg
https://img.shields.io/badge/License-MIT-yellow.svg

Overview
This system simulates cooperative perception between onboard vehicle cameras and roadside cameras. It generates mock detection data, fuses detections from multiple sensors, and produces a unified global object list. The project demonstrates key OOP principles including inheritance, polymorphism, operator overloading, exception handling, and factory patterns.

Features
Add and manage VehicleCamera and RoadCamera sensors

Simulate detection with random or fixed test data

Fuse detections using greedy association algorithm (1.5m threshold)

Fixed test scenario for reproducible verification

Save / load sensor configuration to text files

Three extension features: template container, logging module, fusion result export

Course Requirements & Grading
1. Sensor Class Hierarchy (15 pts) – Inheritance, polymorphism, virtual destructor, operator overloading – Complete

2. DetectedObject & Operator Overloading (10 pts) – ==, +, << operators – Complete

3. Sensor Management, Factory Pattern & Exception Handling (15 pts) – std::unique_ptr, factory function, custom exceptions – Complete

4. Perception Fusion Module (20 pts) – Greedy fusion algorithm, 1.5m association threshold, perception range extension – Complete

5. Main Program, Fixed Scenario & File I/O (10 pts) – Menu system, fixed test scenario, config save/load – Complete

6. Code Quality & Documentation (20 pts) – Google Style Guide, naming conventions, comments, screenshots – Complete

7. Extension Features (10 pts) – Three features implemented (SensorContainer, FusionLogger, result export) – Complete

Penalties Avoided: Compilation failure (–30), plagiarism (–50), missing CMake (–15)

Quick Start
git clone https://github.com/W-T-Xia/V2X-Cooperative-Perception-Simulation-System.git
cd V2X-Cooperative-Perception-Simulation-System
mkdir build && cd build
cmake ..
make
./V2XFusion

Usage
========================================
 V2X Cooperative Perception System
 (Onboard + Roadside Sensor Fusion)
========================================
1. Add sensor (Vehicle/Roadside)
2. Display / Find sensors
3. Simulate sensor detections
4. Execute perception fusion
5. View fused global target list
6. Find fused target by ID
7. Save / Load sensor configuration
8. Exit system
9. Save fusion results to file
========================================
Adding a Vehicle Camera:

Enter type: 1, then provide ID, name, position, range, heading, FOV.

Adding a Road Camera:

Enter type: 2, then provide ID, name, position, range, roadside ID, covered lanes.

Fixed Test Scenario:

Select option 3, then option 2. The system loads:

S001: VehicleCamera at (0,0), range 50m, heading 0°, FOV 90°

R001: RoadCamera at (60,30), range 35m

Four targets: A (S001), B1 (S001), B2 (R001), C (R001)

Expected fusion result: 3 objects (A, B fused, C). Target C at (58,8) is beyond vehicle range, demonstrating roadside extension.


Configuration File
Example sample_config.txt:

# V2X Cooperative Perception - Sensor Configuration
VehicleCamera,S001,FrontCam,0,0,50,0,90
RoadCamera,R001,CrossCam,60,30,35,R1,2
Project Structure
text
├── CMakeLists.txt
├── sample_config.txt
└── src/
    ├── main.cpp
    ├── Sensor.h/cpp
    ├── VehicleCamera.h/cpp
    ├── RoadCamera.h/cpp
    ├── DetectedObject.h/cpp
    ├── FusionCenter.h/cpp
    ├── SensorFactory.h/cpp
    ├── ConfigIO.h/cpp
    ├── SensorContainer.h
    ├── FusionLogger.h/cpp
    └── Exceptions.h
Extension Features
SensorContainer<T> – Generic container with add, findById, and sort functions.

FusionLogger – Singleton logging with INFO/WARNING/ERROR levels, outputs to console and fusion.log, RAII compliant.

Fusion Result Export – Save fused object lists to text files via menu option 9.

License
MIT License. See LICENSE file for details.

Author
Xia Wentao | Student ID: 2353575 | Tongji University | June 30, 2026

