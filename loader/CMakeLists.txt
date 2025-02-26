cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(nylon-loader VERSION 1.0.0 LANGUAGES C CXX)

if (NOT CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(FATAL_ERROR "32-bit executables only support loading 32-bit libraries. (CMAKE_SIZEOF_VOID_P = ${CMAKE_SIZEOF_VOID_P})")
endif ()

add_library(${PROJECT_NAME} SHARED
    "src/main.cpp"
    "src/Core.cpp"
    "src/Logging/Log.cpp"
    "src/Config.cpp"
    "src/Hooks/DefaultHooks.cpp"
    "src/Hooks/Hook.cpp"
    "src/Hooks/DirectXHooks.cpp"
    "src/ModInfo.cpp"
    "src/VersionInfo.cpp"

    "src/CFunc/CFuncManager.cpp"
    "src/CFunc/DefaultCFuncs.cpp"
    "src/Logging/LogFile.cpp"
    "src/Logging/LogSource.cpp"
    "src/CommandConsole.cpp"

    "src/Hooks/CFuncHooks.cpp"

    "src/Imgui/ImGui.cpp"
)

target_include_directories(${PROJECT_NAME} PUBLIC
    "include/"
)
target_include_directories(${PROJECT_NAME} PRIVATE
    "src/"
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    PREFIX ""
    OUTPUT_NAME "nylon"
)
target_compile_definitions(${PROJECT_NAME} PRIVATE NYLON_PLATFORM_PC)

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    copyfile(${PROJECT_NAME} ${CMAKE_CURRENT_BINARY_DIR}/nylon.pdb ${NYLON_OUT_PATH}/nylon.pdb)
endif ()
copyfile(${PROJECT_NAME} ${CMAKE_CURRENT_BINARY_DIR}/nylon.dll ${NYLON_OUT_PATH}/nylon.dll)

target_compile_definitions(${PROJECT_NAME} PUBLIC MAT_JSON_EXPORTING)
target_link_libraries(${PROJECT_NAME} nylon mat-json-impl)

CPMAddPackage("gh:TsudaKageyu/minhook#master")
target_link_libraries(${PROJECT_NAME} minhook)

target_link_libraries(${PROJECT_NAME} "$ENV{DXSDK_DIR}Lib/x86/xinput.lib")

target_link_libraries(${PROJECT_NAME} "$ENV{DXSDK_DIR}Lib/x86/d3dx9.lib")
target_include_directories(${PROJECT_NAME} PUBLIC "$ENV{DXSDK_DIR}Include/")

CPMAddPackage("gh:ocornut/imgui#master")
add_library(imgui STATIC
    "${imgui_SOURCE_DIR}/imgui.cpp"
    "${imgui_SOURCE_DIR}/imgui_demo.cpp"
    "${imgui_SOURCE_DIR}/imgui_draw.cpp"
    "${imgui_SOURCE_DIR}/imgui_tables.cpp"
    "${imgui_SOURCE_DIR}/imgui_widgets.cpp"
    "${imgui_SOURCE_DIR}/backends/imgui_impl_dx9.cpp"
    "${imgui_SOURCE_DIR}/backends/imgui_impl_win32.cpp"
)
target_include_directories(imgui PUBLIC
    "${imgui_SOURCE_DIR}"
    "${imgui_SOURCE_DIR}/backends/"
)
target_link_libraries(${PROJECT_NAME} imgui)

add_subdirectory(proxy)

# install
if (DEFINED GH3_DIR)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${NYLON_OUT_PATH} ${GH3_DIR}
    )
endif ()
