cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(main src/main.cpp src/my_class.cpp)

enable_testing()
add_executable(tests tests/my_class_test.cpp src/my_class.cpp)
find_package(GTest REQUIRED)
target_link_libraries(tests GTest::GTest GTest::Main)
add_test(NAME MyTests COMMAND tests)
