cmake_minimum_required(VERSION 3.10)
project(DateTime)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(main src/main.cpp src/DateTime.cpp)

enable_testing()
add_executable(tests tests/tests.cpp src/DateTime.cpp)
find_package(GTest REQUIRED)
target_link_libraries(tests GTest::GTest GTest::Main)
add_test(NAME MyTests COMMAND tests)
