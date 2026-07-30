V2X Cooperative Perception Simulation System
https://img.shields.io/badge/C%252B%252B-17-blue.svg
https://img.shields.io/badge/CMake-3.10+-green.svg
https://img.shields.io/badge/License-MIT-yellow.svg

A C++ simulation system for V2X cooperative perception, demonstrating sensor fusion between onboard cameras and roadside cameras. Developed for the Object-Oriented Programming and Practice course at Tongji University.

Course Requirements & Scoring
Requirement	Points	Status
Sensor class hierarchy (inheritance, polymorphism, virtual destructor, operator<<)	15pts	✓
DetectedObject & operator overloading (==, +, <<)	10pts	✓
Sensor management, factory pattern & exception handling	15pts	✓
Fusion module (algorithm, 1.5m threshold, greedy strategy, perception extension)	20pts	✓
Main program, fixed test scenario & file I/O	10pts	✓
Code quality, naming, const/override, screenshots, documentation	20pts	✓
Extension features (3 features for full marks)	10pts	✓ (3 features)
Total	100pts	
Extensions Completed (3/3 for full marks):

SensorContainer<T> template container with ID lookup and sorting

FusionLogger singleton with multi-level logging and RAII

Fusion results export to file

Penalties Avoided:

Compilation failure (–30): ✓ Pass

Code plagiarism >75% (–50): ✓ Original

No CMake (–15): ✓ CMake included

Quick Start
bash
git clone https://github.com/W-T-Xia/V2X-Cooperative-Perception-Simulation-System.git
cd V2X-Cooperative-Perception-Simulation-System
mkdir build && cd build
cmake ..
make
./V2XFusion
Usage
text
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
Fixed Test Scenario
Select option 3 → 2 to load the fixed test scenario for grading verification.

Sensors:

S001: VehicleCamera at (0,0), range=50m, heading=0°, FOV=90°

R001: RoadCamera at (60,30), range=35m, roadside_id=R1, lanes=2

Raw detections (4 total):

A: S001, ID=101, VEHICLE, (20,0), conf=0.90

B1: S001, ID=102, VEHICLE, (38.2,7.6), conf=0.85

B2: R001, ID=201, VEHICLE, (38.8,8.1), conf=0.80

C: R001, ID=202, PEDESTRIAN, (58,8), conf=0.88

Expected fusion result (3 total):

A: vehicle-only (ID=101)

B: fused (ID=102, source "R001+S001", count=2)

C: roadside-only, beyond line-of-sight (extends perception range)

Configuration File
Example sample_config.txt:

txt
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
Author
Xia Wentao | Student ID: 2353575 | Tongji University | June 30, 2026

License
MIT License

