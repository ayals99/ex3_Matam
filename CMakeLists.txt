cmake_minimum_required(VERSION 3.25)
project(ex3_Matam)

set(CMAKE_CXX_STANDARD 14)

add_executable(ex3_Matam The_Given_Tests/not_main.cpp The_Given_Tests/HealthPointsExampleTest.cpp The_Given_Tests/QueueExampleTests.cpp)
