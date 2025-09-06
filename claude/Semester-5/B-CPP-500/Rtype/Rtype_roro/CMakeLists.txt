##
## EPITECH PROJECT, 2025
## R-Type
## File description:
## CMakeLists.txt for R-Type Advanced project
##

cmake_minimum_required(VERSION 3.16)

project(rtype
    VERSION 1.0.0
    DESCRIPTION "Advanced R-Type multiplayer game"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
endif()

# Find packages
find_package(Threads REQUIRED)

# Try to find SFML
find_package(PkgConfig)
if(PkgConfig_FOUND)
    pkg_check_modules(SFML QUIET sfml-all)
endif()

# If SFML not found, use fallback or fetch it
if(NOT SFML_FOUND)
    # For simplicity, we'll link against system SFML if available
    # In a real project, you'd use FetchContent or Conan
    find_library(SFML_GRAPHICS sfml-graphics)
    find_library(SFML_WINDOW sfml-window)
    find_library(SFML_SYSTEM sfml-system)
    find_library(SFML_NETWORK sfml-network)
    find_library(SFML_AUDIO sfml-audio)
    
    if(SFML_GRAPHICS AND SFML_WINDOW AND SFML_SYSTEM AND SFML_NETWORK)
        set(SFML_LIBRARIES ${SFML_GRAPHICS} ${SFML_WINDOW} ${SFML_SYSTEM} ${SFML_NETWORK} ${SFML_AUDIO})
        set(SFML_FOUND TRUE)
    endif()
endif()

# Include directories
include_directories(include)

# Common library
file(GLOB_RECURSE COMMON_SOURCES "src/common/*.cpp")
add_library(rtype_common STATIC ${COMMON_SOURCES})

# Engine library
file(GLOB_RECURSE ENGINE_SOURCES "src/engine/*.cpp")
add_library(rtype_engine STATIC ${ENGINE_SOURCES})
target_link_libraries(rtype_engine rtype_common)

# Server executable
file(GLOB_RECURSE SERVER_SOURCES "src/server/*.cpp")
add_executable(r-type_server ${SERVER_SOURCES})
target_link_libraries(r-type_server rtype_engine rtype_common Threads::Threads)

# Client executable (only if SFML found)
if(SFML_FOUND)
    file(GLOB_RECURSE CLIENT_SOURCES "src/client/*.cpp")
    add_executable(r-type_client ${CLIENT_SOURCES})
    target_link_libraries(r-type_client rtype_engine rtype_common ${SFML_LIBRARIES} Threads::Threads)
else()
    message(WARNING "SFML not found - client will not be built")
endif()

# Tests
enable_testing()
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
if(TEST_SOURCES)
    add_executable(rtype_tests ${TEST_SOURCES})
    target_link_libraries(rtype_tests rtype_engine rtype_common Threads::Threads)
    add_test(NAME rtype_tests COMMAND rtype_tests)
endif()

# Install
install(TARGETS r-type_server DESTINATION bin)
if(SFML_FOUND)
    install(TARGETS r-type_client DESTINATION bin)
endif()

install(DIRECTORY assets/ DESTINATION share/rtype/assets/)

# Package
set(CPACK_PACKAGE_NAME "rtype")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION ${PROJECT_DESCRIPTION})
include(CPack)