cmake_minimum_required(VERSION 3.7)
project("pbotectl")

#set(CMAKE_VERBOSE_MAKEFILE on) # for debugging

# configurale options
option(WITH_STATIC "Static build" OFF)

# paths
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules")
set(CMAKE_SOURCE_DIR "..")

#Handle paths nicely
include(GNUInstallDirs)

include(ExternalProject)

# architecture
include(TargetArch)
target_architecture(ARCHITECTURE)

find_package(cJSON REQUIRED)
if (NOT CJSON_FOUND)
    message(SEND_ERROR "Could not find cJSON. Please download and install it first!")
endif ()

if (WITH_STATIC)
    set(BUILD_STATIC_LIBS ON)
endif ()

set(PBOTECTL_SRC_DIR ${CMAKE_SOURCE_DIR}/src)
include_directories(${PBOTECTL_SRC_DIR} ${JSONC_INCLUDE_DIRS})
FILE(GLOB PBOTECTL_SRC ${PBOTECTL_SRC_DIR}/*.c)

include(Version)
set_version("${PBOTECTL_SRC_DIR}/version.h" PROJECT_VERSION)

# show summary
message(STATUS "Project            : ${PROJECT_NAME}")
message(STATUS "Version            : ${PROJECT_VERSION}")
message(STATUS "----------------------------------------")
message(STATUS "Build type         : ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler vendor    : ${CMAKE_C_COMPILER_ID}")
message(STATUS "Compiler version   : ${CMAKE_C_COMPILER_VERSION}")
message(STATUS "Compiler path      : ${CMAKE_C_COMPILER}")
message(STATUS "Architecture       : ${ARCHITECTURE}")
message(STATUS "Install prefix     : ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Options:")
message(STATUS "  STATIC BUILD     : ${WITH_STATIC}")
message(STATUS "----------------------------------------")

add_executable("${PROJECT_NAME}" ${PBOTECTL_SRC})

if (WITH_STATIC)
    set_target_properties("${PROJECT_NAME}" PROPERTIES LINK_FLAGS "-static")
endif ()

if (WITH_STATIC)
    set(DL_LIB ${CMAKE_DL_LIBS})
endif ()

target_link_libraries("${PROJECT_NAME}"
                      ${CJSON_LIBRARIES}
                      ${CMAKE_REQUIRED_LIBRARIES})
