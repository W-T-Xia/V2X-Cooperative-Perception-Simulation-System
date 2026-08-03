# V2X Cooperative Perception Simulation System

C++17 | CMake 3.10+ | Windows / Linux

---

## Overview

A C++ simulation system for V2X cooperative perception, developed for the "Object-Oriented Programming and Practice" course at Tongji University. The system simulates onboard and roadside camera detection, then fuses the results into a unified perception list using sensor fusion algorithms.

---

## Features

- Add and manage VehicleCamera / RoadCamera sensors
- Simulate detection with random or fixed test data
- Fuse detections using greedy association (1.5m threshold)
- View raw and fused object lists
- Save / load sensor configurations from text files
- Fixed test scenario for reproducible grading
- Command-line menu interface

---

## Course Requirements & Scoring

**1. Sensor Class Hierarchy (15 pts)**
Inheritance, polymorphism, virtual destructor, operator overloading.
Status: Completed

**2. DetectedObject & Operator Overloading (10 pts)**
Operator ==, +, << for comparison, fusion, and output.
Status: Completed

**3. Sensor Management, Factory & Exceptions (15 pts)**
std::unique_ptr container, factory function, custom exceptions.
Status: Completed

**4. Perception Fusion Module (20 pts)**
Association algorithm, 1.5m threshold, greedy strategy, range extension.
Status: Completed

**5. Main Program, Fixed Scenario & File I/O (10 pts)**
Menu system, fixed test scenario, config save/load.
Status: Completed

**6. Code Quality & Documentation (20 pts)**
Google Style Guide, naming conventions, const/override, comments.
Status: Completed

**7. Extension Features (10 pts)**
Three features implemented: SensorContainer template, FusionLogger (singleton + RAII), fusion result export.
Status: Completed (3 features)

**Penalties Avoided:**
- Compilation failure: Pass
- Code plagiarism: Original work
- No CMake: CMakeLists.txt included

---

## Quick Start

Prerequisites: C++17 compiler, CMake 3.10+, Windows/Linux

Build:
```
mkdir build && cd build
cmake ..
make
```

Run:
```
./V2XFusion
```

---

## Usage

### Main Menu

When the program starts, the following menu is displayed:

```
========================================
 V2X Cooperative Perception System
 (Onboard + Roadside Sensor Fusion)
========================================
1. Add sensor (Vehicle/Roadside)
2. Display / Find sensors
3. Simulate sensor detections (generate targets)
4. Execute perception fusion
5. View fused global target list
6. Find fused target by ID
7. Save / Load sensor configuration
8. Exit system
9. Save fusion results to file
========================================
Enter command number:
```

Enter a number and press Enter to execute the corresponding function.

### 1. Add Sensor

Select option 1 to add a new sensor. The system will prompt for sensor type and parameters.

**Adding a Vehicle Camera:**
```
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
```

**Adding a Road Camera:**
```
Enter type number: 2
Sensor ID: R001
Sensor name: CrossCam
Position (x y): 60 30
Range (meters): 35
Roadside ID: R1
Covered lanes: 2
RoadCamera added successfully.
```

### 2. Display / Find Sensors

Select option 2 to view sensor information.

**List all sensors:**
```
1. List all sensors
2. Find sensor by ID
Choose: 1

========================================
Total sensors: 2 (Vehicle: 1, Roadside: 1)
[VehicleCamera] ID: S001, Name: FrontCam, Pos: (0, 0), Range: 50m, Heading: 0°, FOV: 90°
[RoadCamera] ID: R001, Name: CrossCam, Pos: (60, 30), Range: 35m, Roadside ID: R1, Lanes: 2
========================================
```

**Find sensor by ID:**
```
Choose: 2
Enter sensor ID: S001
[VehicleCamera] ID: S001, Name: FrontCam, Pos: (0, 0), Range: 50m, Heading: 0°, FOV: 90°
```

### 3. Simulate Sensor Detections

Select option 3 to generate detection data. The system requires choosing between random mode and fixed test scenario.

```
Select mode:
1. Random mode
2. Fixed test scenario
Enter:
```

**Random Mode:** Each sensor generates random targets based on its capabilities.
- VehicleCamera: 1-3 targets within heading +/- FOV/2, distance 5m to range
- RoadCamera: 1-4 targets in all directions, distance 5m to range

Example output:
```
Random detections generated.

========================================
 Current Raw Detections (3 objects)
========================================
ID: 1001, Type: VEHICLE, Pos: (12.5, 3.2), Vel: (5.0, 0.0), Time: 1, Conf: 0.85, Source: S001, Count: 1
ID: 1002, Type: PEDESTRIAN, Pos: (25.8, -2.1), Vel: (0.0, -2.0), Time: 1, Conf: 0.92, Source: S001, Count: 1
ID: 2001, Type: VEHICLE, Pos: (55.0, 15.0), Vel: (3.0, 0.0), Time: 1, Conf: 0.78, Source: R001, Count: 1
========================================
```

**Fixed Test Scenario:** Loads a pre-configured test case for verification.

```
Fixed scenario loaded.

========================================
 Current Raw Detections (4 objects)
========================================
ID: 101, Type: VEHICLE, Pos: (20.0, 0.0), Vel: (10.0, 0.0), Time: 1, Conf: 0.90, Source: S001, Count: 1
ID: 102, Type: VEHICLE, Pos: (38.2, 7.6), Vel: (5.0, 0.0), Time: 1, Conf: 0.85, Source: S001, Count: 1
ID: 201, Type: VEHICLE, Pos: (38.8, 8.1), Vel: (5.0, 0.0), Time: 1, Conf: 0.80, Source: R001, Count: 1
ID: 202, Type: PEDESTRIAN, Pos: (58.0, 8.0), Vel: (0.0, -1.0), Time: 1, Conf: 0.88, Source: R001, Count: 1
========================================
```

### 4. Execute Perception Fusion

Select option 4 to fuse the current raw detections. This step requires that detections have been generated first.

```
[INFO] Starting fusion...
[INFO] Fused group of 2 -> ID 102
[INFO] Unassociated: ID 101
[INFO] Unassociated: ID 202
[INFO] Fusion complete. Total fused objects: 3
Fusion complete. Fused objects: 3
```

If no detections are available:
```
Please run detection first (menu 3).
```

### 5. View Fused Global Target List

Select option 5 to display the fused object list after fusion has been executed.

```
========================================
 Fused Global Object List (3 objects)
========================================
ID: 101, Type: VEHICLE, Pos: (20.0, 0.0), Vel: (10.0, 0.0), Time: 1, Conf: 0.90, Source: S001, Count: 1
ID: 102, Type: VEHICLE, Pos: (38.5, 7.85), Vel: (5.0, 0.0), Time: 1, Conf: 0.825, Source: R001+S001, Count: 2
ID: 202, Type: PEDESTRIAN, Pos: (58.0, 8.0), Vel: (0.0, -1.0), Time: 1, Conf: 0.88, Source: R001, Count: 1
========================================
```

### 6. Find Fused Target by ID

Select option 6 to search for a specific target in the fused list.

```
Enter object ID: 102
ID: 102, Type: VEHICLE, Pos: (38.5, 7.85), Vel: (5.0, 0.0), Time: 1, Conf: 0.825, Source: R001+S001, Count: 2
```

If the ID is not found:
```
No fused object with ID 999 found.
```

### 7. Save / Load Sensor Configuration

Select option 7 to save or load sensor configurations.

```
1. Save config
2. Load config
Choose: 1
Filename: my_config.txt
Configuration saved to my_config.txt
```

**Load:**
```
Choose: 2
Filename: sample_config.txt
Configuration loaded (2 sensors).
```

If the file does not exist:
```
Error: Cannot open file: invalid.txt
```

### 8. Exit System

Select option 8 to exit the program.

```
[INFO] System exit
```

### 9. Save Fusion Results to File

Select option 9 to export fused objects to a text file.

```
Filename: results.txt
[INFO] Fused objects saved to results.txt
Fusion results saved.
```

---

## Fixed Test Scenario

The fixed test scenario is used for grading verification. To run it:

```
Enter command number: 3
Select mode:
1. Random mode
2. Fixed test scenario
Enter: 2
```

**Sensors loaded:**
- VehicleCamera S001: position (0,0), range 50m, heading 0°, FOV 90°
- RoadCamera R001: position (60,30), range 35m, roadside_id R1, lanes 2

**Raw detections (4 targets):**
- Target A: ID 101, VEHICLE, (20,0), from S001 (vehicle-only)
- Target B1: ID 102, VEHICLE, (38.2,7.6), from S001
- Target B2: ID 201, VEHICLE, (38.8,8.1), from R001
- Target C: ID 202, PEDESTRIAN, (58,8), from R001 (roadside-only)

**Expected fusion results (3 targets):**
- Target A: ID 101, VEHICLE, (20,0), source S001, count 1
- Target B: ID 102, VEHICLE, (38.5,7.85), source R001+S001, count 2 (B1+B2 fused)
- Target C: ID 202, PEDESTRIAN, (58,8), source R001, count 1 (beyond vehicle range)

Target B1 and B2 are 0.78m apart (less than 1.5m threshold), so they are associated and fused.

---

## Configuration File Format

sample_config.txt:

```
# V2X Cooperative Perception System - Sensor Configuration
VehicleCamera,S001,FrontCam,0,0,50,0,90
RoadCamera,R001,CrossCam,60,30,35,R1,2
```

Fields:
- VehicleCamera: type,id,name,x,y,range,heading,fov
- RoadCamera: type,id,name,x,y,range,roadside_id,covered_lanes

---

## Project Structure

```
CMakeLists.txt
CMakePresets.json
sample_config.txt
src/
  main.cpp
  Sensor.h / Sensor.cpp
  VehicleCamera.h / VehicleCamera.cpp
  RoadCamera.h / RoadCamera.cpp
  DetectedObject.h / DetectedObject.cpp
  FusionCenter.h / FusionCenter.cpp
  SensorFactory.h / SensorFactory.cpp
  ConfigIO.h / ConfigIO.cpp
  SensorContainer.h
  FusionLogger.h / FusionLogger.cpp
  Exceptions.h
```

---

## Extension Features

SensorContainer<T>: Template container with ID lookup and custom sorting

FusionLogger: Singleton logging with INFO/WARNING/ERROR levels, RAII file handling

Fusion Export: Save fused object lists to text files

---

## License

MIT License

---

## Author

夏文韬(Also known as 夏文韜 or Wen-Tao Xia) | Tongji University | June 30, 2026
