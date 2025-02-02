cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(ProxyLoader VERSION 1.0.0 LANGUAGES C CXX)

add_library(${PROJECT_NAME} SHARED "src/ProxyLoader.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES
    PREFIX ""
    OUTPUT_NAME "xinput1_3"
)

#if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
#    copyfile(${PROJECT_NAME} ${CMAKE_CURRENT_BINARY_DIR}/xinput1_3.pdb ${NYLON_OUT_PATH}/xinput1_3.pdb)
#endif ()
copyfile(${PROJECT_NAME} ${CMAKE_CURRENT_BINARY_DIR}/xinput1_3.dll ${NYLON_OUT_PATH}/xinput1_3.dll)

if (DEFINED GH3_DIR)
    #if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    #    copyfile(${PROJECT_NAME} ${NYLON_OUT_PATH}/xinput1_3.pdb ${GH3_DIR}/xinput1_3.pdb)
    #endif ()
    copyfile(${PROJECT_NAME} ${NYLON_OUT_PATH}/xinput1_3.dll ${GH3_DIR}/xinput1_3.dll)
endif ()

if (MSVC)
    include(CheckLinkerFlag)
    check_linker_flag(CXX /NOEXP SUPPORTS_NOEXP)
    if (SUPPORTS_NOEXP)
        target_link_options(${PROJECT_NAME} PRIVATE /NOEXP)
    endif ()
    target_link_options(${PROJECT_NAME} PRIVATE /NOIMPLIB /DEBUG:NONE)
endif ()
