cmake_minimum_required(VERSION 3.20)
project("VineMain")

set(CMAKE_CXX_STANDARD 17)

set(VINE_MAIN_SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(VINE_MAIN_ASSETS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/assets)

file(GLOB_RECURSE VINE_MAIN_SRC_FILES
    "${VINE_MAIN_SRC_PATH}/*.cpp"
)

file(GLOB_RECURSE VINE_MAIN_INC_FILES
    "${VINE_MAIN_SRC_PATH}/*.h"
)

add_executable(${PROJECT_NAME} ${VINE_MAIN_SRC_FILES} ${VINE_MAIN_INC_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${VINE_MAIN_SRC_PATH})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/VineBackend/include)

target_link_libraries(${PROJECT_NAME} PRIVATE VineBackend)
target_link_libraries(${PROJECT_NAME} PRIVATE lua_static)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)
if(TARGET SDL2::SDL2main)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main)
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE sol2::sol2)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)
target_link_libraries(${PROJECT_NAME} PRIVATE stb)
target_link_libraries(${PROJECT_NAME} PRIVATE pugixml)

add_custom_target(
    copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${VINE_MAIN_ASSETS_PATH}" "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/assets"
    COMMENT "Copying assets to output directory"
)

add_dependencies(${PROJECT_NAME} copy_assets)