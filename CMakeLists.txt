cmake_minimum_required(VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(gh3ml VERSION 1.0.0)

set(GH3_GAME_DIR "C:/Program Files (x86)/Aspyr/Guitar Hero III")

include(cmake/get_cpm.cmake)

CPMAddPackage("gh:ocornut/imgui#master")

add_library(${PROJECT_NAME} SHARED
  "src/gh3ml/main.cpp" 
  "src/gh3ml/Core.cpp"
  "src/gh3ml/Log.cpp"
  "src/gh3ml/LogSource.cpp" 
  "src/gh3ml/Config.cpp"
  "src/gh3ml/DefaultHooks.cpp" 
  "src/gh3ml/Hook.cpp" 
  "src/gh3ml/Hook.cpp"
  "src/gh3ml/Hooks/DirectXHooks.cpp"
  "src/gh3ml/ModInfo.cpp"

  "${imgui_SOURCE_DIR}/imgui.cpp"
  "${imgui_SOURCE_DIR}/imgui_demo.cpp"
  "${imgui_SOURCE_DIR}/imgui_draw.cpp"
  "${imgui_SOURCE_DIR}/imgui_tables.cpp"
  "${imgui_SOURCE_DIR}/imgui_widgets.cpp"
  "${imgui_SOURCE_DIR}/backends/imgui_impl_dx9.cpp"
  "${imgui_SOURCE_DIR}/backends/imgui_impl_win32.cpp"

  "libGH3/src/main.cpp" "libGH3/src/GH3/Qb/QbStruct.cpp" "libGH3/src/GH3/CFunc.cpp"
  # source files here
)

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(FATAL_ERROR "x64 bit libraries are not supported by x32 bit executables.")
endif()

function(copyfile targ src dst)
    if (NOT EXISTS ${src})
        return()
    endif()

    add_custom_command(
        TARGET ${targ}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${src} ${dst}
    )
endfunction()



target_include_directories(${PROJECT_NAME} PUBLIC
    "include/"
    "libGH3/include/"
    "${imgui_SOURCE_DIR}"
    "${imgui_SOURCE_DIR}/backends/"
)

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    copyfile(${PROJECT_NAME} ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pdb ${GH3_GAME_DIR}/${PROJECT_NAME}.pdb)
endif()

copyfile(${PROJECT_NAME} ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.dll ${GH3_GAME_DIR}/${PROJECT_NAME}.dll)

# this is so stupid
set(CMAKE_SIZEOF_VOID_P 4)
if (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
  # ensure 32 bit on clang
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -target i386-pc-windows-msvc")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -target i386-pc-windows-msvc")
  add_definitions("--target=i386-pc-windows-msvc")
endif()


CPMAddPackage("gh:TsudaKageyu/minhook#master")
CPMAddPackage("gh:geode-sdk/json#main")

target_link_libraries(${PROJECT_NAME} minhook)
target_link_libraries(${PROJECT_NAME} mat-json)


# -- PORXY LAODER

add_library(ProxyLoader SHARED "src/ProxyLoader/ProxyLoader.cpp")

set_target_properties(ProxyLoader PROPERTIES
  PREFIX ""
  OUTPUT_NAME "xinput1_3"
)
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    copyfile(ProxyLoader ${CMAKE_BINARY_DIR}/xinput1_3.pdb ${GH3_GAME_DIR}/xinput1_3.pdb)
endif()

copyfile(ProxyLoader ${CMAKE_BINARY_DIR}/xinput1_3.dll ${GH3_GAME_DIR}/xinput1_3.dll)

# Vultu - don't feel like working with shitty cmake rn.
# -- libGH3

# add_library(libGH3 SHARED "libGH3/src/main.cpp" "libGH3/src/GH3/Qb/QbStruct.cpp" "libGH3/src/GH3/CFunc.cpp")

#set_target_properties(libGH3 PROPERTIES
 # PREFIX ""
 # OUTPUT_NAME "libGH3"
#)

#target_include_directories(libGH3 PUBLIC
#    "libGH3/include/"
#)

if (MSVC)
  include(CheckLinkerFlag)
  check_linker_flag(CXX /NOEXP SUPPORTS_NOEXP)
  if (SUPPORTS_NOEXP)
    target_link_options(ProxyLoader PRIVATE /NOEXP)
  endif()
  target_link_options(ProxyLoader PRIVATE /NOIMPLIB /DEBUG:NONE)
endif()