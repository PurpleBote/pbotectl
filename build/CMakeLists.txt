cmake_minimum_required(VERSION 3.7)
project("pbotectl" LANGUAGES C)

#set(CMAKE_VERBOSE_MAKEFILE on) # for debugging

# paths
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules")
set(CMAKE_SOURCE_DIR "..")

#Handle paths nicely
include(GNUInstallDirs)

include(ExternalProject)

# architecture
include(TargetArch)
target_architecture(ARCHITECTURE)

set(PBOTECTL_SRC_DIR ${CMAKE_SOURCE_DIR}/src)
include_directories(${PBOTECTL_SRC_DIR})
FILE(GLOB PBOTECTL_SRC ${PBOTECTL_SRC_DIR}/*.c)

# read version

file(READ "${PBOTECTL_SRC_DIR}/version.h" ver)

string(REGEX MATCH "PBOTECTL_VERSION_MAJOR ([0-9]*)" _ ${ver})
set(ver_major ${CMAKE_MATCH_1})

string(REGEX MATCH "PBOTECTL_VERSION_MINOR ([0-9]*)" _ ${ver})
set(ver_minor ${CMAKE_MATCH_1})

string(REGEX MATCH "PBOTECTL_VERSION_MICRO ([0-9]*)" _ ${ver})
set(ver_micro ${CMAKE_MATCH_1})

set(CMAKE_PROJECT_VERSION "${ver_major}.${ver_minor}.${ver_micro}")

include_directories(SYSTEM)

# show summary
message(STATUS "Project              ${PROJECT_NAME}")
message(STATUS "Version              ${CMAKE_PROJECT_VERSION}")
message(STATUS "----------------------------------------")
message(STATUS "Build type         : ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler vendor    : ${CMAKE_C_COMPILER_ID}")
message(STATUS "Compiler version   : ${CMAKE_C_COMPILER_VERSION}")
message(STATUS "Compiler path      : ${CMAKE_C_COMPILER}")
message(STATUS "Architecture       : ${ARCHITECTURE}")
message(STATUS "Install prefix     : ${CMAKE_INSTALL_PREFIX}")
message(STATUS "----------------------------------------")

add_executable("${PROJECT_NAME}" ${PBOTECTL_SRC})

target_link_libraries("${PROJECT_NAME}")
