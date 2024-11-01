cmake_minimum_required(VERSION 3.16.0)

project(kmeans)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SOURCES "src/main.cpp")

add_executable(kmeans ${SOURCES})
SET_TARGET_PROPERTIES(kmeans PROPERTIES COMPILE_FLAGS "-fopenmp"
    LINK_FLAGS "-fopenmp")