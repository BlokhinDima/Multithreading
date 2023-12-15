cmake_minimum_required(VERSION 3.5.1)

project(RaceLibrary)

set(INC_DIR "inc")

file(GLOB_RECURSE INC_FILES "${INC_DIR}/*.h")

set(SRC_DIR "src")

file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.cpp")

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(${PROJECT_NAME} SHARED
    ${INC_FILES}
    ${SRC_FILES}
)

target_include_directories(${PROJECT_NAME} PUBLIC
    "${INC_DIR}"
    "${INC_DIR}/vehicles"
    "${INC_DIR}/races"
    "${INC_DIR}/exceptions"
)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})