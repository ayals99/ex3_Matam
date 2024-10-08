//
// Created by ayals on 6/2/2023.
//

#ifndef EX3_MATAM_HEALTPOINTS_TESTS_H
#define EX3_MATAM_HEALTPOINTS_TESTS_H

#include <iostream>
#include "../../../../../CLionProjects/just one prblem/HealthPoints.h"
#include <sstream>

namespace HealthPointsTests {
    bool testInitialization();
    bool testArithmaticOperators();
    bool testComparisonOperators();
    bool testOutputOperator();
}

void runTheirTestsForHP(){
    bool initialization = HealthPointsTests::testInitialization();
    if(!initialization) {
        std::cout << "HealthPoints: Their tests initialization failed" << std::endl;
        return;
    }

    bool arithmetic = HealthPointsTests::testArithmaticOperators();
    if(!arithmetic) {
        std::cout << "HealthPoints: Their tests arithmetic failed" << std::endl;
        return;
    }

    bool comparison = HealthPointsTests::testComparisonOperators();
    if(!comparison) {
        std::cout << "HealthPoints: Their tests comparison failed" << std::endl;
        return;
    }

    bool output = HealthPointsTests::testOutputOperator();
    if(!output) {
        std::cout << "HealthPoints: Their tests output failed" << std::endl;
        return;
    }

    std::cout << "HealthPoints: their tests passed" << std::endl;
}


namespace HealthPointsTests {

    static bool checkHealthPointsValues(const HealthPoints& healthPoints, int current, int max)
    {
        std::ostringstream expected;
        expected << current << '(' << max << ')';
        std::ostringstream result;
        result << healthPoints;
        return (expected.str() == result.str());
    }

    bool testInitialization()
    {
        bool testResult = true;

        HealthPoints healthPoints1; /* has 100 points out of 100 */
        HealthPoints healthPoints2(150); /* has 150 points out of 150 */
        bool exceptionThrown = false;
        try {
            HealthPoints healthPoints3(-100);
        }
        catch (HealthPoints::InvalidArgument& e) {
            exceptionThrown = true;
        }

        testResult = testResult && exceptionThrown;
        testResult = testResult && checkHealthPointsValues(healthPoints1, 100, 100);
        return testResult;
    }

    bool testArithmaticOperators()
    {
        bool testResult = true;
        HealthPoints healthPoints1; /* has 100 points out of 100 */
        HealthPoints healthPoints2(150); /* has 150 points out of 150 */

        healthPoints1 -= 20; /* now has 80 points out of 100 */
        testResult = testResult && checkHealthPointsValues(healthPoints1, 80, 100);

        healthPoints1 += 100; /* now has 100 points out of 100 */
        testResult = testResult && checkHealthPointsValues(healthPoints1, 100, 100);

        healthPoints1 -= 150; /* now has 0 points out of 100 */
        testResult = testResult && checkHealthPointsValues(healthPoints1, 0, 100);

        healthPoints2 = healthPoints2 - 160; /* now has 0 points out of 150 */
        testResult = testResult && checkHealthPointsValues(healthPoints2, 0, 150);

        healthPoints2 = 160 + healthPoints1; /* now has 100 out of 100 */
        testResult = testResult && checkHealthPointsValues(healthPoints2, 100, 100);

        return testResult;

    }

    bool testComparisonOperators()
    {
        bool testResult = true;
        HealthPoints healthPoints1 = HealthPoints(100); /* has 100 points out of 100 */
        HealthPoints healthPoints2 = 100; /* has 100 points out of 100 */
        bool comparisonResult;

        comparisonResult = (healthPoints1 == healthPoints2); /* returns true */
        testResult = testResult && comparisonResult;

        healthPoints2 = HealthPoints(150); /* has 150 points out of 150 */
        comparisonResult = (healthPoints1 == healthPoints2); /* returns false */
        testResult = testResult && !comparisonResult;

        healthPoints2 -= 50; /* now has 100 points out of 150 */
        comparisonResult = (healthPoints1 == healthPoints2); /* returns true */

        comparisonResult = (healthPoints1 < healthPoints2); /* returns false */
        testResult = testResult && !comparisonResult;

        healthPoints1 -= 50; /* now has 50 points out of 100 */
        comparisonResult = (healthPoints1 < healthPoints2); /* returns true */

        return testResult;
    }

    bool testOutputOperator()
    {
        bool testResult = true;
        std::ostringstream stream;

        HealthPoints healthPoints1 = HealthPoints(100); /* has 100 points out of 100 */
        healthPoints1 -= 50; /* now has 50 points out of 100 */
        stream << healthPoints1; /* stream content is "50(100)" */
        testResult = testResult && (stream.str() == "50(100)");

        HealthPoints healthPoints2 = HealthPoints(150); /* has 1500 points out of 150 */
        healthPoints2 -= 50; /* now has 100 points out of 150 */
        stream << ", " << healthPoints2; /* stream content is "50(100), 100(150)" */
        testResult = testResult && (stream.str() == "50(100), 100(150)");

        return testResult;
    }
}

void runMyTestsForHP(){
    HealthPoints healthPoints1;
    HealthPoints healthPoints(150); /* has 150 points out of 150 */

    if(healthPoints != 150){
        std::cout << "HealthPoints: The constructor doesn't work well" << std::endl;
        return;
    }

//    try {
//        HealthPoints healthPoints0(-100);
//    }
//    catch (HealthPoints::InvalidArgument& e) {
//        std::cout << "InvalidArgument exception caught" << std::endl;
//        return 0;
//    }
//    catch (...) {
//        std::cout << "Other exception caught" << std::endl;
//        return 0;
//    }

    HealthPoints healthPointsDouble(10.5);
    if(healthPointsDouble != 10){
        std::cout << "HealthPoints: The constructor with double doesn't work well" << std::endl;
        return;
    }

    HealthPoints healthPointsChar('a');
    if(healthPointsDouble == (int)'a'){
        std::cout << "HealthPoints: The constructor with char doesn't work well" << std::endl;
        return;
    }

    healthPoints1 -= 20; /* now has 80 points out of 100 */
    if(healthPoints1 != 80){
        std::cout << "HealthPoints: The -= operator doesn't work well first time" << std::endl;
        return;
    }

    healthPoints1 +=100; /* now has 100 points out of 100 */
    if(healthPoints1 != 100){
        std::cout << "HealthPoints: The += operator doesn't work well" << std::endl;
        return;
    }

    healthPoints1 -= 150; /* now has 0 points out of 100 */
    if(healthPoints1 != 0){
        std::cout << "HealthPoints: The -= operator doesn't work well second time" << std::endl;
        return;
    }

    HealthPoints healthPoints2;
    healthPoints2 = healthPoints2 - 160; /* now has 0 points out of 150 */
    if(healthPoints2 != 0){
        std::cout << "HealthPoints: The -= operator doesn't work well" << std::endl;
        return;
    }

    healthPoints2 = 160 + healthPoints2; /* now has 100 out of 100 */
    if(healthPoints2 != 100){
        std::cout << "HealthPoints: The += operator doesn't work well for 160" << std::endl;
        return ;
    }

    bool comparisonResult;
    HealthPoints healthPoints3(100);
    if(healthPoints3 != 100){
        std::cout << "HealthPoints: The constructor with int doesn't work well" << std::endl;
        return ;
    }

    HealthPoints healthPoints4 = 100; /* 100 points out of 100 */

    if(healthPoints4 != 100){
        std::cout << "HealthPoints: The assignment operator from int doesn't work well" << std::endl;
        return ;
    }

    comparisonResult = (healthPoints3 == healthPoints4); /* returns true */
    if(!comparisonResult){
        std::cout << "HealthPoints: The == operator doesn't work well" << std::endl;
        return ;
    }

    healthPoints4 = HealthPoints(150); /* has 150 points out of 150 */
    if (healthPoints4 != 150){
        std::cout << "HealthPoints: The assignment operator from constructor doesn't work well" << std::endl;
        return ;
    }

    comparisonResult = (healthPoints3 == healthPoints4); /* returns false */
    if(comparisonResult){
        std::cout << "HealthPoints: The == operator doesn't work well" << std::endl;
        return ;
    }

    healthPoints4 -= 50; /* now has 100 points out of 150 */
    if(healthPoints4 != 100){
        std::cout << "HealthPoints: The -= operator doesn't work well" << std::endl;
        return ;
    }

    comparisonResult = (100 == healthPoints4); /* returns true */
    if(!comparisonResult){
        std::cout << "HealthPoints: The == operator doesn't work well" << std::endl;
        return ;
    }

    comparisonResult = (healthPoints3 < healthPoints4); /* returns false */
    if(comparisonResult){
        std::cout << "HealthPoints: The < operator doesn't work well" << std::endl;
        return ;
    }

    healthPoints3 -= 50; /* now has 50 points out of 100 */
    if(healthPoints3 != 50){
        std::cout << "HealthPoints: The -= operator doesn't work well" << std::endl;
        return ;
    }

    comparisonResult = (healthPoints3 < healthPoints4); /* returns true */
    if(!comparisonResult){
        std::cout << "HealthPoints: The < operator doesn't work well" << std::endl;
        return ;
    }

    std::cout << "HealthPoints: my tests passed!" << std::endl;
}


#endif //EX3_MATAM_HEALTPOINTS_TESTS_H
