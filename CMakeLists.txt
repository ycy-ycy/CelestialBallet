cmake_minimum_required(VERSION 3.10)
project(StellarBallet)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenMP REQUIRED)

set(SOURCES
    celestialBody.cpp
    rk45.cpp
    entity.cpp
    gravity.cpp
    position.cpp
)

add_executable(StellarBallet ${SOURCES})

if(OpenMP_CXX_FOUND)
    target_link_libraries(StellarBallet PUBLIC OpenMP::OpenMP_CXX)
endif()