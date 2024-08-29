cmake_minimum_required(VERSION 3.26)
add_definitions(-std=c++20)
project(SFMLPractice)
file(GLOB SOURCES "src/*.cpp")
option(BUILD_SHARED_LIBS "Build shared libraries" ON)
include_directories("C:/SFML-2.6.1/MinGW - 13.1.0 (32 bit)/include")
link_directories("C:/SFML-2.6.1/MinGW - 13.1.0 (32 bit)/lib")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
add_executable(${PROJECT_NAME} ${SOURCES})
set_target_properties(${TARGET} PROPERTIES WIN32_EXECUTABLE TRUE)

target_link_libraries(${PROJECT_NAME} libsfml-graphics.a libsfml-window.a libsfml-audio.a libsfml-main.a libsfml-network.a libopenal32.a libsfml-system.a)