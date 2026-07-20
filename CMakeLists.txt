cmake_minimum_required(VERSION 3.25)
project(entropy LANGUAGES CXX)

include(FetchContent)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FetchContent_Declare(
    math
    GIT_REPOSITORY https://github.com/anazli/math.git
    GIT_TAG main
)
set(MATH_BUILD_TESTS OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(math)

add_library(${PROJECT_NAME} STATIC "")
target_sources(${PROJECT_NAME}
    PRIVATE
        src/dummy.cpp
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS include
        FILES
            include/engine/dummy.hpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        math
)

if(ENABLE_TESTING)
    enable_testing()
    add_subdirectory(test)
endif()

if(PROJECT_IS_TOP_LEVEL)
    set(PROJECT_DEMO ${PROJECT_NAME}-demo)
    add_executable(${PROJECT_DEMO} demo/dummy-demo.cpp)
    target_link_libraries(${PROJECT_DEMO}
        PRIVATE
            ${PROJECT_NAME}
    )
endif()