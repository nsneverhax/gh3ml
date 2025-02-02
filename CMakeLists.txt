cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

include(cmake/get_cpm.cmake)

if (NOT DEFINED CPM_SOURCE_CACHE)
    message(NOTICE "Not using CPM cache (CPM_SOURCE_CACHE). "
        "It is recommended to use it to improve configure times.")
endif()

project(nylon VERSION 1.0.0 LANGUAGES CXX C)

add_library(${PROJECT_NAME} INTERFACE)

set(NYLON_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(NYLON_BIN_PATH ${NYLON_ROOT_PATH}/bin)

# mat: this is so stupid -- vultu: Too bad!
set(CMAKE_SIZEOF_VOID_P 4)
if (WIN32)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND
        CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "GNU")
        # target x86 on windows with clang
        target_compile_options(${PROJECT_NAME} INTERFACE --target=i686-pc-windows-msvc)
        target_link_options(${PROJECT_NAME} INTERFACE --target=i686-pc-windows-msvc)
        add_compile_options(--target=i686-pc-windows-msvc)
        add_link_options(--target=i686-pc-windows-msvc)
    endif()
endif()

function(copyfile targ src dst)
    add_custom_command(
        TARGET ${targ}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${src} ${dst}
    )
endfunction()

cmake_host_system_information(
    RESULT GH3_DIR
    QUERY WINDOWS_REGISTRY "HKLM/SOFTWARE/Aspyr/Guitar Hero III"
    VALUE "Path"
    VIEW 32
)
cmake_path(IS_ABSOLUTE GH3_DIR GH3_DIR_ABSOLUTE)
if (NOT ${GH3_DIR_ABSOLUTE} OR NOT EXISTS ${GH3_DIR})
    unset(GH3_DIR)
endif ()
unset(GH3_DIR_ABSOLUTE)

if (DEFINED GH3_DIR)
    message(STATUS "Guitar Hero III path set to \"${GH3_DIR}\", will install on build.")
else ()
    message(STATUS "Guitar Hero III installation not found.")
endif ()

set(MAT_JSON_AS_INTERFACE ON)
CPMAddPackage("gh:geode-sdk/json#main")
target_compile_definitions(${PROJECT_NAME} INTERFACE MAT_JSON_DYNAMIC=1)

add_subdirectory(${NYLON_ROOT_PATH}/libGH3)
target_link_libraries(${PROJECT_NAME} INTERFACE libGH3)

if (NOT EXISTS ${NYLON_BIN_PATH})
    file(MAKE_DIRECTORY ${NYLON_BIN_PATH})
endif()

if (PROJECT_IS_TOP_LEVEL)
    add_subdirectory(loader)
    target_link_libraries(${PROJECT_NAME} INTERFACE nylon-loader)
else ()
    target_link_libraries(${PROJECT_NAME} INTERFACE "${NYLON_BIN_PATH}")
endif ()
