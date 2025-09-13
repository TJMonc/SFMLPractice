cmake_minimum_required(VERSION 3.26)
project(SFMLPractice)
include(FetchContent)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)
set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/deps)
set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${FETCHCONTENT_BASE_DIR}/lib)

set(SFML_INCLUDE_DIR ${FETCHCONTENT_BASE_DIR}/sfml-src/include)

set(INCLUDE_DIR ${SFML_INCLUDE_DIR})
set(LINK_DIR ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
set(LINKED_LIBS sfml-graphics sfml-window sfml-audio sfml-network sfml-system)
set(COMPILE_OPTIONS -std=c++20 -O3 -Werror -Wno-trigraphs)

FetchContent_Declare(
	SFML
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG 2.6.1
)



FetchContent_MakeAvailable(SFML)

file(GLOB SOURCES "src/*.cpp")
add_executable(shipGame WIN32 ${SOURCES})

target_compile_options(shipGame PRIVATE ${COMPILE_OPTIONS})
target_include_directories(shipGame PRIVATE ${INCLUDE_DIR})
target_link_directories(shipGame PRIVATE ${LINK_DIR})
target_link_libraries(shipGame ${LINKED_LIBS})

set_target_properties(sfml-graphics sfml-window sfml-audio sfml-network sfml-system 
PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_dependencies(shipGame sfml-graphics sfml-window sfml-audio sfml-network sfml-system)