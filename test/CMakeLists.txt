cmake_minimum_required(VERSION 3.25)
project(entropy-tests LANGUAGES CXX)

include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main
  )
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
  include(GoogleTest)

 add_executable(${PROJECT_NAME}
  dummy-test.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest GTest::gtest_main gmock entropy)
gtest_discover_tests(${PROJECT_NAME})