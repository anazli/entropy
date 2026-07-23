cmake_minimum_required(VERSION 3.25)
project(entropy-demos LANGUAGES CXX)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG master
)
set(SFML_BUILD_NETWORK OFF CACHE INTERNAL "")
set(SFML_BUILD_AUDIO   OFF CACHE INTERNAL "")
set(SFML_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(SFML_BUILD_DOC OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(SFML)

set(BALLISTIC_DEMO ballistic-demo)
add_executable(${BALLISTIC_DEMO}
  ballistic_demo.cpp
  ballistic_demo.hpp
)
target_include_directories(${BALLISTIC_DEMO} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${BALLISTIC_DEMO} PRIVATE entropy sfml-graphics sfml-window sfml-system)