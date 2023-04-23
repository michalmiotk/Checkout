project(Receipt)
cmake_minimum_required(VERSION 3.1)
set(CMAKE_POLICY_DEFAULT_CMP0079 NEW)
set(CMAKE_PROJECT_VERSION 1.0.0)
set(CMAKE_PROJECT_VERSION_MAJOR "")
set(CMAKE_PROJECT_VERSION_MINOR "")
set(CMAKE_PROJECT_VERSION_PATCH "")

add_compile_options(-Wall -Wextra -Wpedantic --std=c++20)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include_directories(../src)

include(GoogleTest)


add_library(Checkout Checkout.cpp)

add_executable(main main.cpp)
target_link_libraries(main Checkout)

add_executable(test test.cpp)
target_link_libraries(test Checkout GTest::gtest_main GTest::gmock_main)
