cmake_minimum_required(VERSION 3.20)
project("VineMain")

set(VINE_SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE SRC_FILES
    "${VINE_SRC_PATH}/*.cpp"
)

file(GLOB_RECURSE INC_FILES
    "${VINE_SRC_PATH}/*.h"
)

add_library(${PROJECT_NAME} STATIC ${SRC_FILES} ${INC_FILES})