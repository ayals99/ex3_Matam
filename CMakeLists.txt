cmake_minimum_required(VERSION 3.25)
project(ex3_Matam)

set(CMAKE_CXX_STANDARD 14)

add_executable(ex3_Matam ex3_master_from_github/not_main.cpp ex3_master_from_github/HealthPointsExampleTest.cpp ex3_master_from_github/QueueExampleTests.cpp)
