cmake_minimum_required(VERSION 3.20)
project("VineBackend")

set(CMAKE_CXX_STANDARD 17)

set(VINE_BACKEND_SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(VINE_BACKEND_INC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/source_group.cmake)

set(SDL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external/sdl)
set(SOL2_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external/sol2)
set(LUA_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external/lua)
set(SPDLOG_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external/spdlog)
set(GLM_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external/glm)
set(GLAD_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external/glad)

add_subdirectory(${LUA_PATH})
add_subdirectory(${SDL_PATH})
add_subdirectory(${SOL2_PATH})
add_subdirectory(${SPDLOG_PATH})
add_subdirectory(${GLM_PATH})
add_subdirectory(${GLAD_PATH})

file(GLOB_RECURSE VINE_BACKEND_SRC_FILES
    "${VINE_BACKEND_SRC_PATH}/*.cpp"
)

file(GLOB_RECURSE VINE_BACKEND_INC_FILES
    "${VINE_BACKEND_INC_PATH}/*.h"
)

add_compile_definitions(SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE)

add_library(${PROJECT_NAME} STATIC ${VINE_BACKEND_SRC_FILES} ${VINE_BACKEND_INC_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${VINE_BACKEND_INC_PATH})
target_include_directories(${PROJECT_NAME} PUBLIC ${SPDLOG_PATH}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${LUA_PATH}/lua-5.4.6/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL_PATH}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${SOL2_PATH}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${GLM_PATH})
target_include_directories(${PROJECT_NAME} PUBLIC ${GLAD_PATH}/include)