# CMakeList.txt: BROTAO_CAR 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 收集所有源文件
set(SOURCES
    src/main.cpp
    src/Sensor.cpp
    src/VehicleCamera.cpp
    src/RoadCamera.cpp
    src/DetectedObject.cpp
    src/FusionCenter.cpp
    src/SensorFactory.cpp
    src/ConfigIO.cpp
    src/FusionLogger.cpp
)

# 将源代码添加到此项目的可执行文件。
add_executable (BROTAO_CAR ${SOURCES})

# 包含头文件路径
target_include_directories(BROTAO_CAR PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_definitions(BROTAO_CAR PRIVATE _USE_MATH_DEFINES)

# 可选的编译器警告（保留原有风格，无额外强制）
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET BROTAO_CAR PROPERTY CXX_STANDARD 17)
endif()