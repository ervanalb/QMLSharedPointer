cmake_minimum_required(VERSION 2.8.11)

project(qsp)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Werror")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O2 -ffast-math -march=native")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2 -ffast-math -march=native")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb3 -O2 -ffast-math -march=native")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -ffast-math -march=native")
set(CMAKE_CXX_STANDARD 14)

find_package(Qt5Core REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5Qml REQUIRED)

set(qsp_LIBRARIES)
list(APPEND qsp_LIBRARIES
    Qt5::Quick
    Qt5::Qml
    )

add_executable(qsp WIN32
    src/main.cpp
    src/ExampleQmlObject.cpp
              )

target_link_libraries(qsp ${qsp_LIBRARIES})
