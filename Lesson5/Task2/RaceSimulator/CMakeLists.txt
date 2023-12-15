cmake_minimum_required(VERSION 3.5.1)

project(RaceSimulator)

set(EXECUTABLE ${PROJECT_NAME})

set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/inc")

file(GLOB INC_FILES "${INC_DIR}/*.h")

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

file(GLOB SRC_FILES "${SRC_DIR}/*.cpp")

set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/RaceLibrary")

include_directories(${INC_DIR})

add_subdirectory(${LIB_DIR})

add_executable(${EXECUTABLE} ${SRC_FILES})

target_link_libraries(${EXECUTABLE} RaceLibrary)

