cmake_minimum_required(VERSION 3.5)
project(flecs_app LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)

set(EXECUTABLE_OUTPUT_PATH
    ${PROJECT_BINARY_DIR}/bin/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE})
set(LIBRARY_OUTPUT_PATH
    ${PROJECT_BINARY_DIR}/bin/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE})

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include/components
  ${CMAKE_CURRENT_SOURCE_DIR}/include/systems)

file(GLOB SRC src/*.c src/components/*.c src/systems/*.c)
file(GLOB HEADERS include/*.h include/components/*.h include/systems/*.h)

set(FLECS_SOURCES ${SRC} ${HEADERS})

add_library(${PROJECT_NAME} STATIC ${FLECS_SOURCES} include/private.h)
target_include_directories(
  ${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
         ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/bgfx/
         ${CMAKE_CURRENT_SOURCE_DIR}/include
         ${CMAKE_CURRENT_SOURCE_DIR}/include/components
         ${CMAKE_CURRENT_SOURCE_DIR}/include/systems)

target_link_libraries(${PROJECT_NAME} SDL2 bgfx bx cimgui)

add_subdirectory(sample_app)
add_subdirectory(3rdparty/cimgui)
add_subdirectory(3rdparty/bgfx)
