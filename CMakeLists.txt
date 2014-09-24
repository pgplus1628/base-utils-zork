project(base-utils)

## ==============================================================
## Cmake environment settting

# Require the most recent version of cmake
cmake_minimum_required(VERSION 2.8)

# Enable testing
if(BUILD_TESTING)
  enable_testing()
endif(BUILD_TESTING)

## ==============================================================
## System Checks

#include(CheckLibraryExists)
#include(CheckFunctionExists)
#include(ExternalProject)
#include(CheckCXXSourceCompiles)
include(CheckCXXCompilerFlag)

# Check if on a 64bit machine
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
  message( STATUS " Build on a 64 bit system.")
elseif (CMAKE_SIZEOF_VOID_P EQUAL 4)
  message( STATUS " Build on a 32 bit system.")
endif()

# Check if MARCH is set
if(NOT MARCH)
  check_cxx_compiler_flag(-march=native HAS_MARCH_NATIVE)
  if(HAS_MARCH_NATIVE)
    set(MARCH "native")
  else()
    set(MARCH "x86-64")
  endif()
endif()

# Check if MTUNE is set
if(NOT MTUNE)
  check_cxx_compiler_flag(-mtune=native HAS_MTUNE_HATIVE)
  if(HAS_MTUNE_NATIVE)
    set(MTUNE "native")
  else()
    set(MTUNE "x86-64")
  endif()
endif()

## ============================================================
## Setup Compiler

# Set the profiling flags if profiling mode is enabled
if(COMPILE_PROFILING MATCHES 1)
  #TODO
  set(PROFILING_FLAGS "")
else()
  set(PROFILING_FLAGS "")
endif()
 
## If `CMake -D CMAKE_BUILD_TYPE=Debug` CMAKE_CXX_FLAGS_DEBUG will be used
## if CMAKE_BUILD_TYPE=Release, CMAKE_CXX_FLAGS_RELEASE will be used.


# Shared compiler flags used by all build types (debug, release)
# Use c++11
message(STATUS "C++11 is enabled")
set(CPP11_FLAGS "-std=c++11")
set(COMPILER_FLAGS "-Wall ${CPP11_FLAGS}" CACHE STRING "common compiler options")

# Set the debug flags
set(CMAKE_CXX_FLAGS_DEBUG
  "-O0 -march=${MARCH} ${PROFILING_FLAGS} ${COMPILER_FLAGS}"
  CACHE STRING "compiler options" FORCE)

# Set the release flags
set(CMAKE_CXX_FLAGS_RELEASE
  "-O3 -march=${MARCH} -mtune=${MTUNE} ${PROFILING_FLAGS} ${COMPILER_FLAGS}"
  CACHE STRING "compiler options" FORCE)

# Print flags message
if (CMAKE_BUILD_TYPE MATCHES "Debug")
  message(STATUS "Debug build with c++ flags: " ${CMAKE_CXX_FLAGS_DEBUG})
elseif (CMAKE_BUILD_TYPE MATCHES "Release")
  message(STATUS "Release build with c++ flags: " ${CMAKE_CXX_FLAGS_RELEASE})
else()
  message(FATAL_ERROR "Unknown build type : " ${CMAKE_BUILD_TYPE} " !")
endif()


## ==============================================================
# Helper macros
# Dependent on base-utils/base
macro(add_base_executable NAME)
  add_executable(${NAME} ${ARGN})
  target_link_libraries(${NAME} baseutils_base)
  add_dependencies(${NAME} baseutils_base)
  #TODO Core dependencies
endmacro(add_baseutils_executable)

#macro(add_parallel_executable NAME)
#
#endmacro(add_parallel_executable)


## ===============================================================
# Set subdirectories
add_subdirectory(base)
#add_subdirectory(parallel)
add_subdirectory(test)





