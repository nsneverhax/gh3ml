﻿cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(libGH3)

add_library(${PROJECT_NAME} STATIC
    "src/main.cpp"
    "src/GH3/Qb/QbStruct.cpp"
    "src/GH3/CFunc.cpp"
    "src/GH3/CRC.cpp"
    "src/GH3/Addresses.cpp"
 "src/GH3/Lst/Node.cpp" "src/GH3/Script/CComponentType.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC "include/")
