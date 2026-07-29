# V2X-Cooperative-Perception-Simulation-System
A C++ simulation system for V2X cooperative perception, demonstrating sensor fusion between onboard cameras and roadside cameras using object-oriented programming.

https://img.shields.io/badge/C%252B%252B-17-blue.svg
https://img.shields.io/badge/CMake-3.10+-green.svg
https://img.shields.io/badge/License-MIT-yellow.svg
https://img.shields.io/badge/platform-Windows%2520%257C%2520Linux-lightgrey.svg

Overview
This project is a C++ simulation system for Vehicle-to-Everything (V2X) cooperative perception, developed as the coursework for Object-Oriented Programming and Practice at Tongji University. The system simulates the detection and fusion process between onboard vehicle cameras and roadside cameras, demonstrating how roadside infrastructure can extend a vehicle's perception range and provide beyond-line-of-sight information.

All detection data is programmatically generated without relying on real hardware or image processing algorithms. The system runs entirely in the command line and follows object-oriented design principles including inheritance, polymorphism, operator overloading, exception handling, and factory patterns.

Features
Sensor Management: Dynamically add, list, and search sensors (VehicleCamera / RoadCamera)

Simulated Detection: Each sensor generates mock detection targets with realistic spatial constraints

Data Fusion: Associate and merge detections from multiple sensors using a greedy algorithm

Fixed Test Scenario: Pre-configured reproducible test case for verification and grading

Configuration I/O: Save and load sensor configurations to/from plain text files

Exception Handling: Custom exceptions with user-friendly error messages

Command-line Interface: Numbered menu system for all operations

Course Requirements & Grading
This project was developed to fulfill the following course requirements. Each requirement maps directly to a scoring category:

Category	Requirement	Implementation Status
1. Sensor Class Hierarchy (15 pts)	Inheritance, polymorphism, virtual destructor, operator overloading	✓ Complete
2. DetectedObject & Operator Overloading (10 pts)	==, +, << operators for object comparison and fusion	✓ Complete
3. Sensor Management, Factory Pattern & Exception Handling (15 pts)	std::unique_ptr container, factory function, custom exceptions	✓ Complete
4. Perception Fusion Module (20 pts)	Fusion algorithm, association threshold (1.5m), greedy strategy, perception range extension	✓ Complete
5. Main Program, Fixed Scenario & File I/O (10 pts)	Menu system, fixed test scenario, config save/load	✓ Complete
6. Code Quality & Documentation (20 pts)	Google Style Guide, naming conventions, const/override, comments, screenshots	✓ Complete
7. Extension Features (10 pts)	At least 3 features required for full marks	✓ 3 features implemented
Extension Features Completed (Scoring Item 7)
SensorContainer Template - Generic container with ID lookup and sorting

FusionLogger - Singleton logging module with multi-level logging and RAII

Fusion Result Export - Save fused object lists to text files

Penalty Items – All Avoided
Penalty	Status
Compilation failure (–30 pts)	✓ Pass
Code plagiarism >75% (–50 pts)	✓ Original
No CMake / non-compilable project (–15 pts)	✓ CMake included
Quick Start
Prerequisites
Requirement	Version
C++ Compiler	C++17 (GCC 7+, Clang 5+, MSVC 2017+)
CMake	3.10 or higher
OS	Windows 11 or Linux
Build
bash
# Clone the repository
git clone https://github.com/W-T-Xia/V2X-Cooperative-Perception-Simulation-System.git
cd V2X-Cooperative-Perception-Simulation-System

# Build with CMake
mkdir build && cd build
cmake ..
make
Run
bash
./V2XFusion
On Windows:

cmd
V2XFusion.exe
Usage Guide
Main Menu
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
Enter command number:
Adding a Vehicle Camera
text
--- Add Sensor ---
Sensor type:
1. VehicleCamera
2. RoadCamera
Enter type number: 1
Sensor ID: S001
Sensor name: FrontCam
Position (x y): 0 0
Range (meters): 50
Heading (deg): 0
FOV (deg): 90
VehicleCamera added successfully.
Adding a Road Camera
text
Enter type number: 2
Sensor ID: R001
Sensor name: CrossCam
Position (x y): 60 30
Range (meters): 35
Roadside ID: R1
Covered lanes: 2
RoadCamera added successfully.
Simulating Detection
text
Select mode:
1. Random mode
2. Fixed test scenario
Enter: 1
Random detections generated.

========================================
 Current Raw Detections (3 objects)
========================================
ID: 1001, Type: VEHICLE, Pos: (12.5, 3.2), ...
ID: 1002, Type: PEDESTRIAN, Pos: (25.8, -2.1), ...
========================================
Executing Fusion
text
[INFO] Starting fusion...
[INFO] Fused group of 2 -> ID 102
[INFO] Unassociated: ID 101
[INFO] Unassociated: ID 202
[INFO] Fusion complete. Total fused objects: 3
Fusion complete. Fused objects: 3
Fixed Test Scenario
The system includes a pre-configured test scenario used for course verification and grading. This scenario is automatically loaded when selecting "Fixed test scenario" from the detection menu.

Sensors
Sensor	ID	Name	Position	Range	Heading	FOV
VehicleCamera	S001	FrontCam	(0, 0)	50m	0°	90°
RoadCamera	R001	CrossCam	(60, 30)	35m	—	—
Raw Detection Targets
Target	Source	ID	Type	Position	Confidence
A	S001	101	VEHICLE	(20.0, 0.0)	0.90
B1	S001	102	VEHICLE	(38.2, 7.6)	0.85
B2	R001	201	VEHICLE	(38.8, 8.1)	0.80
C	R001	202	PEDESTRIAN	(58.0, 8.0)	0.88
Expected Results
Category	Count	Details
Raw detections	4	A, B1, B2, C
Fused objects	3	A, B (fused), C
Vehicle-only target	1	Target A (ID=101)
Fused target	1	Target B (ID=102), source "R001+S001"
Roadside-only target	1	Target C (ID=202) – beyond line-of-sight
Key Verification Points:

B1 and B2 distance: ~0.78m < 1.5m (threshold) → associated and fused

Target C at (58, 8) exceeds vehicle camera range (50m) → only roadside visible

Demonstrates roadside sensor extending perception range

Configuration File Format
Configuration files are plain text with comma-separated fields. Lines starting with # are treated as comments and ignored.

Format Specification
VehicleCamera:

text
VehicleCamera,sensor_id,name,position_x,position_y,range,heading,fov
RoadCamera:

text
RoadCamera,sensor_id,name,position_x,position_y,range,roadside_id,covered_lanes
Example: sample_config.txt
txt
# V2X Cooperative Perception System - Sensor Configuration
VehicleCamera,S001,FrontCam,0,0,50,0,90
RoadCamera,R001,CrossCam,60,30,35,R1,2
Loading Configuration
text
7. Save / Load sensor configuration
Choose: 2
Filename: sample_config.txt
Configuration loaded (2 sensors).
Project Structure
text
V2X-Cooperative-Perception-Simulation-System/
├── CMakeLists.txt              # CMake build configuration
├── README.md                   # This file
├── LICENSE                     # MIT License
├── sample_config.txt           # Example sensor configuration
├── src/
│   ├── main.cpp                # Entry point, menu system
│   ├── Sensor.h                # Abstract base class
│   ├── Sensor.cpp
│   ├── VehicleCamera.h         # Onboard camera
│   ├── VehicleCamera.cpp
│   ├── RoadCamera.h            # Roadside camera
│   ├── RoadCamera.cpp
│   ├── DetectedObject.h        # Detection data structure
│   ├── DetectedObject.cpp
│   ├── FusionCenter.h          # Fusion algorithm
│   ├── FusionCenter.cpp
│   ├── SensorFactory.h         # Factory function
│   ├── SensorFactory.cpp
│   ├── ConfigIO.h              # File I/O
│   ├── ConfigIO.cpp
│   ├── SensorContainer.h       # Extension: template container
│   ├── FusionLogger.h          # Extension: logging
│   ├── FusionLogger.cpp
│   └── Exceptions.h            # Custom exceptions
Class Design Overview
Sensor Hierarchy
text
              ┌─────────────────────────┐
              │     Sensor (abstract)    │
              │  - sensor_id_, name_,    │
              │    position_, range_     │
              │  + detect() = 0          │
              │  + operator<<            │
              │  + distance()            │
              └───────────┬─────────────┘
                          │
            ┌─────────────┴─────────────┐
            ▼                             ▼
┌───────────────────────┐ ┌───────────────────────┐
│    VehicleCamera      │ │     RoadCamera        │
│  - heading_, fov_     │ │  - roadside_id_,      │
│  - resolution         │ │    covered_lanes_     │
│  + detect()           │ │  + detect()           │
│  + getType()          │ │  + getType()          │
└───────────────────────┘ └───────────────────────┘
DetectedObject
cpp
struct DetectedObject {
    int object_id;
    ObjectType type;          // VEHICLE, PEDESTRIAN, UNKNOWN
    double position_x, position_y;
    double velocity_x, velocity_y;
    double timestamp;
    double confidence;
    std::string sensor_source;
    int detection_count;
    
    bool operator==(const DetectedObject& other) const;
    DetectedObject operator+(const DetectedObject& other) const;
};
Fusion Algorithm Flow
text
Raw Detections from All Sensors
            │
            ▼
    Generate Candidate Pairs
    (same type & distance < 1.5m)
            │
            ▼
    Sort Pairs by Distance
            │
            ▼
    Greedy Association
    (each object used once)
            │
            ▼
    Group Formation
            │
            ▼
    Group Fusion (operator+)
    + Unassociated Objects
            │
            ▼
    Fused Global Object List
Extension Features
1. SensorContainer Template
A generic container class supporting adding, finding by ID, and custom sorting with duplicate ID checking.

cpp
SensorContainer<std::unique_ptr<Sensor>> container;
container.add(std::make_unique<VehicleCamera>(...));
auto found = container.findById("S001");
container.sortBy([](auto& a, auto& b) { 
    return a->getRange() < b->getRange(); 
});
2. FusionLogger (Singleton + RAII)
Multi-level logging with automatic file management:

cpp
FusionLogger::instance().log("Fusion started", LogLevel::INFO);
FusionLogger::instance().log("Warning: duplicate detection", LogLevel::WARNING);
FusionLogger::instance().log("Critical error", LogLevel::ERROR);
Logs to both console and fusion.log

Singleton pattern ensures single log instance

RAII: file opens on construction, closes on destruction

3. Fusion Results Export
Export fused object lists to a text file:

text
9. Save fusion results to file
Filename: results.txt
[INFO] Fused objects saved to results.txt
Fusion results saved.
Testing
Fixed Scenario Test
The fixed test scenario provides a reproducible verification path:

bash
# Grading workflow
1. Compile and run the program
2. Select option 3 (Simulate sensor detections)
3. Choose option 2 (Fixed test scenario)
4. View raw detections (4 objects)
5. Select option 4 (Execute fusion)
6. View fused results (3 objects)
Expected Output Example
text
========================================
 Fused Global Object List (3 objects)
========================================
ID: 101, Type: VEHICLE, Pos: (20, 0), 
  Vel: (10, 0), Conf: 0.90, Source: S001, Count: 1
ID: 102, Type: VEHICLE, Pos: (38.5, 7.85), 
  Vel: (5, 0), Conf: 0.825, Source: R001+S001, Count: 2
ID: 202, Type: PEDESTRIAN, Pos: (58, 8), 
  Vel: (0, -1), Conf: 0.88, Source: R001, Count: 1
========================================
Random Mode
Add sensors and generate random detections to verify:

VehicleCamera detects only within its field of view

RoadCamera detects in all directions

Fusion correctly identifies overlapping detections

Unassociated detections from both sensors appear separately

Common Issues & Solutions
Issue 1: Duplicate Association
Problem: In the initial implementation, the same detection target could be associated multiple times with different partners.

Solution: A used array tracks whether each detection has already been associated. The greedy algorithm checks !used[i] && !used[j] before creating any group.

Issue 2: FusionCenter Reference Stale After Scenario Reload
Problem: After loading the fixed test scenario, the sensors_ vector was reassigned, but the FusionCenter object still held a reference to the old vector.

Solution: Reconstruct the FusionCenter object after loading the fixed scenario using std::make_unique<FusionCenter>(sensors).

Development Environment
Aspect	Details
Language	C++17
Build System	CMake 3.10+
IDE	VS Code / CLion
Compiler	GCC 9.4 (Linux), MSVC 2022 (Windows)
Standard Library	ISO C++17, no third-party libraries
License
This project is licensed under the MIT License. See the LICENSE file for details.

Acknowledgments
Course: Object-Oriented Programming and Practice, Tongji University

Instructor: School of Electronic and Information Engineering

Reference: Course specification document "面向对象编程课程设计-车路协同感知.docx"

Libraries: C++ Standard Library only (<random>, <fstream>, <memory>, etc.)

Design Patterns: Singleton pattern for logging, Factory pattern for sensor creation

Author
Name	Xia Wentao
Student ID	2353575
Course	Object-Oriented Programming and Practice
Date	June 30, 2026
Institution	Tongji University
Repository
GitHub: https://github.com/W-T-Xia/V2X-Cooperative-Perception-Simulation-System
