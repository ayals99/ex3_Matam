cmake_minimum_required(VERSION 3.25)
project(ex3_Matam)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(ex3_master_from_github)
include_directories("tests - ex3/UnitTests")

add_executable(ex3_Matam
        ex3_master_from_github/HealthPointsExampleTest.cpp
        ex3_master_from_github/QueueExampleTests.cpp
        ex3_master_from_github/TestMain.cpp
        ex3_master_from_github/TestUtils.h
        "tests - ex3/UnitTests/catch.hpp"
        "tests - ex3/UnitTests/HealthPointsUnitTests.cpp"
        "tests - ex3/UnitTests/QueueUnitTests.cpp"
        "tests - ex3/UnitTests/relativeIncludes.h"
        "tests - ex3/UnitTests/UnitTestsMain.cpp"
        HealthPoints.h
        Queue.h)
