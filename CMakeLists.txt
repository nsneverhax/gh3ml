cmake_minimum_required(VERSION 3.21.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(gh3ml VERSION 1.0.0)

add_library(${PROJECT_NAME} SHARED
  src/gh3ml/main.cpp src/gh3ml/Core.cpp "src/gh3ml/Log.cpp"
  # source files here
)

target_include_directories(${PROJECT_NAME} PUBLIC
    include/
)

# this is so stupid
set(CMAKE_SIZEOF_VOID_P 4)
if (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
  # ensure 32 bit on clang
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -target i386-pc-windows-msvc")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -target i386-pc-windows-msvc")
  add_definitions("--target=i386-pc-windows-msvc")
endif()

include(cmake/get_cpm.cmake)

CPMAddPackage("gh:TsudaKageyu/minhook#master")

target_link_libraries(${PROJECT_NAME} minhook)

# -- PORXY LAODER

add_library(ProxyLoader SHARED "src/ProxyLoader/ProxyLoader.cpp")

set_target_properties(ProxyLoader PROPERTIES
  PREFIX ""
  OUTPUT_NAME "XInput1_3"
)

if (MSVC)
  include(CheckLinkerFlag)
  check_linker_flag(CXX /NOEXP SUPPORTS_NOEXP)
  if (SUPPORTS_NOEXP)
    target_link_options(ProxyLoader PRIVATE /NOEXP)
  endif()
  target_link_options(ProxyLoader PRIVATE /NOIMPLIB /DEBUG:NONE)
endif()