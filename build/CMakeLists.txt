cmake_minimum_required(VERSION 3.7)

# For debugging
#set(CMAKE_VERBOSE_MAKEFILE on)

## Paths
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules")
set(CMAKE_SOURCE_DIR "..")

set(PBOTECTL_SRC_DIR ${CMAKE_SOURCE_DIR}/src)

include(Version)
set_version("${PBOTECTL_SRC_DIR}/version.h" PROJECT_VERSION)

project(
  pbotectl
  LANGUAGES C
  VERSION ${PROJECT_VERSION})

## Configurale options
option(WITH_STATIC "Static build" OFF)
# ToDo?
#option(WITH_CLANG  "Force Clang compiler" OFF)
#if (WITH_CLANG)
#    set (CMAKE_C_COMPILER "/usr/bin/clang")
#    set (CMAKE_CXX_COMPILER "/usr/bin/clang++")
#endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG_MODE)
else ()
    #NOOP
endif (CMAKE_BUILD_TYPE STREQUAL "Debug") 

## Handle paths nicely
include(GNUInstallDirs)

include(ExternalProject)

## Architecture
include(TargetArch)
target_architecture(ARCHITECTURE)

# Code

## libcjson stuff
set(LIBCJSON_SRC_DIR ${CMAKE_SOURCE_DIR}/lib/cjson)
set_source_files_properties(${LIBCJSON_SRC_DIR} PROPERTIES LANGUAGE C)
include_directories(${LIBCJSON_SRC_DIR})
file(GLOB LIBCJSON_SRC ${LIBCJSON_SRC_DIR}/*.c)
add_library(libcjson ${LIBCJSON_SRC})
set_target_properties(libcjson PROPERTIES PREFIX "")

## pbotectl stuff
include_directories(${PBOTECTL_SRC_DIR} ${JSONC_INCLUDE_DIRS})
FILE(GLOB PBOTECTL_SRC ${PBOTECTL_SRC_DIR}/*.c)

# Compiler flags customization
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-unused-parameter")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -pedantic")

## Check for C89 support
include(CheckCCompilerFlag)
CHECK_C_COMPILER_FLAG("-std=c89" C89_SUPPORTED)
if (C89_SUPPORTED)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c89")
else ()
    message(SEND_ERROR "C89 standard not seems to be supported by compiler. Too old version!")
endif ()

##
if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pipe")
elseif (CMAKE_C_COMPILER_ID STREQUAL "Clang")
    # more tweaks
    if (LINUX)
        # NOOP  
    endif ()
    if (NOT (MSVC OR MSYS OR APPLE))
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-const-variable -Wno-overloaded-virtual")
    endif ()
endif ()

## Compiler flags customization (by system)
if (NOT (CMAKE_SYSTEM_NAME STREQUAL "OpenBSD" OR APPLE))
    # NOOP
endif ()

#
if (WITH_STATIC)
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")

    set(BUILD_STATIC_LIBS ON)
    set(BUILD_SHARED_LIBS OFF)
endif ()

# I18N
find_package (Intl REQUIRED)
if (NOT Intl_FOUND)
    message(SEND_ERROR "Intl is not found. Please download and install it first!")
endif ()
include_directories(${Intl_INCLUDE_DIRS})

find_package (Gettext REQUIRED)
if (NOT GETTEXT_FOUND)
message(SEND_ERROR "Gettext is not found. Please download and install it first!")
endif ()


#find_program(GETTEXT_XGETTEXT_EXECUTABLE xgettext)
#find_program(GETTEXT_MSGMERGE_EXECUTABLE msgmerge)
#find_program(GETTEXT_MSGFMT_EXECUTABLE msgfmt)

#if (GETTEXT_XGETTEXT_EXECUTABLE)
#    message(DEBUG "xgettext: ${GETTEXT_XGETTEXT_EXECUTABLE}")
#    add_custom_target(
#        pot-update
#        ALL
#        COMMENT "pot-update: Done."
#        DEPENDS ${CMAKE_SOURCE_DIR}/src/po/${PROJECT_NAME}.pot)
#    add_custom_command(
#        TARGET pot-update
#        PRE_BUILD
#        COMMAND
#            ${GETTEXT_XGETTEXT_EXECUTABLE}
#            --from-code=utf-8
#            --language=c
#            --force-po
#            --output=${CMAKE_SOURCE_DIR}/src/po/${PROJECT_NAME}.pot
#            --keyword=_
#            --width=80
#            ${PBOTECTL_SRC}
#        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
#        COMMENT "pot-update: Pot file generated: ${CMAKE_SOURCE_DIR}/src/po/${PROJECT_NAME}.pot"
#    )
#endif (GETTEXT_XGETTEXT_EXECUTABLE)



#if (GETTEXT_MSGMERGE_EXECUTABLE)
#    message(DEBUG "msgmerge: ${GETTEXT_MSGMERGE_EXECUTABLE}")
#    add_custom_target(
#        pot-merge
#        ALL
#        COMMENT "pot-merge: Done."
#        DEPENDS ${CMAKE_SOURCE_DIR}/src/po/${PROJECT_NAME}.pot)
#    file(GLOB PO_FILES ${CMAKE_SOURCE_DIR}/src/po/*/${PROJECT_NAME}.po)
#    message(TRACE "PO_FILES: ${PO_FILES}")
#    foreach(PO_FILE IN ITEMS ${PO_FILES})
#        message(DEBUG "Adding msgmerge for: ${PO_FILE}")
#        add_custom_command(
#            TARGET pot-merge
#            PRE_BUILD
#            COMMAND
#                ${GETTEXT_MSGMERGE_EXECUTABLE} ${PO_FILE}
#                ${CMAKE_SOURCE_DIR}/src/po/${PROJECT_NAME}.pot
#            COMMENT "pot-merge: ${PO_FILE}"
#        )
#    endforeach()
#endif (GETTEXT_MSGMERGE_EXECUTABLE)



#set(AVAILABLE_LANGS "en")
#if (GETTEXT_MSGFMT_EXECUTABLE)
#    message(DEBUG "msgmerge: ${GETTEXT_MSGFMT_EXECUTABLE}")
#    file(GLOB PO_LANGS LIST_DIRECTORIES true ${CMAKE_SOURCE_DIR}/src/po/*)
#    message(TRACE "PO_LANGS: ${PO_LANGS}")
#    add_custom_target(
#        po-compile
#        ALL
#        COMMENT "po-compile: Done.")
#    foreach(PO_LANG IN ITEMS ${PO_LANGS})
#        if(IS_DIRECTORY ${PO_LANG})
#            get_filename_component(DIR_NAME "${PO_LANG}" NAME)
#            list(APPEND AVAILABLE_LANGS ${DIR_NAME})
#            message(DEBUG "Adding msgfmt for: ${DIR_NAME}")
#            add_custom_command(
#                TARGET po-compile
#                PRE_BUILD
#                COMMAND
#                    ${GETTEXT_MSGFMT_EXECUTABLE}
#                    --output-file=${PROJECT_NAME}.mo
#                    ${PROJECT_NAME}.po
#                WORKING_DIRECTORY ${PO_LANG}
#                COMMENT "po-compile: ${PO_LANG}"
#            )
#        endif()
#    endforeach()
#endif (GETTEXT_MSGFMT_EXECUTABLE)

#GETTEXT_CREATE_TRANSLATIONS()

set(GETTEXT_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/locales")
set(GETTEXT_LANGUAGES "en" "ru")

# Show summary
message(STATUS "Project            : ${PROJECT_NAME}")
message(STATUS "Version            : ${PROJECT_VERSION}")
message(STATUS "----------------------------------------")
message(STATUS "Build type         : ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler vendor    : ${CMAKE_C_COMPILER_ID}")
message(STATUS "Compiler version   : ${CMAKE_C_COMPILER_VERSION}")
message(STATUS "Compiler path      : ${CMAKE_C_COMPILER}")
message(STATUS "Architecture       : ${ARCHITECTURE}")
message(STATUS "Langs              : ${GETTEXT_LANGUAGES}")
message(STATUS "Install prefix     : ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Options:")
message(STATUS "  STATIC BUILD     : ${WITH_STATIC}")
message(STATUS "----------------------------------------")

add_executable("${PROJECT_NAME}" ${PBOTECTL_SRC})

target_compile_definitions(${PROJECT_NAME} PUBLIC "GETTEXT_DOMAIN=\"${PROJECT_NAME}\"")
target_compile_definitions(${PROJECT_NAME} PUBLIC "GETTEXT_OUTPUT_DIR=\"${GETTEXT_OUTPUT_DIR}\"")

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/Gettext_helpers.cmake")

CONFIGURE_GETTEXT(
    DOMAIN "${PROJECT_NAME}"
    TARGET_NAME "${PROJECT_NAME}-gettext"
    SOURCES "${PBOTECTL_SRC}"
    POTFILE_DESTINATION "${GETTEXT_OUTPUT_DIR}"
    XGETTEXT_ARGS "--keyword=_" "--keyword=N_" "--keyword=P_:1,2"
        "--package-name=${PROJECT_NAME}" "--package-version=${PROJECT_VERSION}"
    LANGUAGES ${GETTEXT_LANGUAGES}
    BUILD_DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}>/${GETTEXT_OUTPUT_DIR}
    ALL
)

if (WITH_STATIC)
    set_target_properties("${PROJECT_NAME}" PROPERTIES LINK_FLAGS "-static")
endif ()

if (WITH_STATIC)
    set(DL_LIB ${CMAKE_DL_LIBS})
endif ()

set(LIBS
    libcjson
    ${Intl_LIBRARIES}
    ${CMAKE_REQUIRED_LIBRARIES})

target_link_libraries ("${PROJECT_NAME}" ${LIBS})

#add_dependencies ("${PROJECT_NAME}" "${PROJECT_NAME}-gettext")
