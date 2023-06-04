#ifndef EX3_MATAM_QUEUE_TESTS_H
#define EX3_MATAM_QUEUE_TESTS_H
#define AGREGATE_TEST_RESULT(res, cond) (res) = ((res) && (cond))
#include "Queue.h"
#include <iostream>

void runMyTestsForQueue();

void runTheirTestsForQueue();
namespace theirQueueTests{
    bool testQueueMethods();
    bool testModuleFunctions();
    bool testExceptions();
    bool testConstQueue();
}

namespace myQueueTests{
    bool testQueueConstructor(){
        Queue<int> queue1;
        queue1.pushBack(1);
        queue1.pushBack(2);
        std::cout << queue1.size() << std::endl;
        if(queue1.front() != 1){
            return false;
        }
        queue1.popFront();
        if(queue1.front() != 2){
            return false;
        }
        queue1.popFront();
        std::cout << queue1.size() << std::endl;
        return true;
    }

    bool testModuleFunctions(){
        return true;
    }
    bool testExceptions(){
        return true;
    }
    bool testConstQueue(){
        return true;
    }
}

void runMyTestsForQueue(){
    bool constructorResults = myQueueTests::testQueueConstructor();
    if(!constructorResults){
        std::cout << "Their tests methods failed" << std::endl;
        return;
    }
    bool moduleResult = myQueueTests::testModuleFunctions();
    if(!moduleResult){
        std::cout << "Their tests module failed" << std::endl;
        return;
    }
    bool exceptionsResult = myQueueTests::testExceptions();
    if(!exceptionsResult){
        std::cout << "Their tests exceptions failed" << std::endl;
        return;
    }
    bool constQueueResult = myQueueTests::testConstQueue();
    if(!constQueueResult){
        std::cout << "Their tests const queue failed" << std::endl;
        return;
    }
    std::cout << "My tests passed" << std::endl;
}










static bool isEven(int n)
{
    return (n % 2) == 0;
}

static void setFortyTwo(int& n)
{
    n = 42;
}

void runTheirTestsForQueue(){
    bool methodsResult = theirQueueTests::testQueueMethods();
    if(!methodsResult){
        std::cout << "Their tests methods failed" << std::endl;
        return;
    }
    bool moduleResult = theirQueueTests::testModuleFunctions();
    if(!moduleResult){
        std::cout << "Their tests module failed" << std::endl;
        return;
    }
    bool exceptionsResult = theirQueueTests::testExceptions();
    if(!exceptionsResult){
        std::cout << "Their tests exceptions failed" << std::endl;
        return;
    }
    bool constQueueResult = theirQueueTests::testConstQueue();
    if(!constQueueResult){
        std::cout << "Their tests const queue failed" << std::endl;
        return;
    }
    std::cout << "Their tests passed" << std::endl;
}

namespace theirQueueTests {

    bool testQueueMethods()
    {
        bool testResult = true;

        Queue<int> queue1;
        queue1.pushBack(1);
        queue1.pushBack(2);
        int front1 = queue1.front();
        AGREGATE_TEST_RESULT(testResult, front1 == 1);

        queue1.front() = 3;
        front1 = queue1.front();
        AGREGATE_TEST_RESULT(testResult, front1 == 3);

        queue1.popFront();
        front1 = queue1.front();
        AGREGATE_TEST_RESULT(testResult, front1 == 2);

        int size1 = queue1.size();
        AGREGATE_TEST_RESULT(testResult, size1 == 1);

        return testResult;
    }

    bool testModuleFunctions()
    {
        bool testResult = true;

        Queue<int> queue3;
        for (int i = 1; i <= 10; i++) {
            queue3.pushBack(i);
        }
        Queue<int> queue4 = filter(queue3, isEven);
        for (int i = 2; i <= 10; i+=2) {
            int front4 = queue4.front();
            AGREGATE_TEST_RESULT(testResult, front4 == i);
            queue4.popFront();
        }


        Queue<int> queue5;
        for (int i = 1; i <= 5; i++) {
            queue5.pushBack(i);
        }
        transform(queue5, setFortyTwo);
        for (Queue<int>::Iterator i = queue5.begin(); i != queue5.end(); ++i) {
            AGREGATE_TEST_RESULT(testResult,(*i == 42));
        }

        return testResult;
    }

    bool testExceptions()
    {
        bool testResult = true;

        bool exceptionThrown = false;
        Queue<int> queue6;
        try {
            queue6.front() = 5;
        }
        catch (Queue<int>::EmptyQueue& e) {
            exceptionThrown = true;
        }
        AGREGATE_TEST_RESULT(testResult, exceptionThrown);

        exceptionThrown = false;
        Queue<int>::Iterator endIterator = queue6.end();
        try {
            ++endIterator;
        }
        catch (Queue<int>::Iterator::InvalidOperation& e) {
            exceptionThrown = true;
        }
        AGREGATE_TEST_RESULT(testResult, exceptionThrown);

        return testResult;
    }

    bool testConstQueue()
    {
        bool testResult = true;

        Queue<int> queue5;
        for (int i = 1; i <= 5; i++) {
            queue5.pushBack(42);
        }
        const Queue<int> constQueue = queue5;
        for (Queue<int>::ConstIterator i = constQueue.begin(); static_cast<Queue<int>::ConstIterator>(i) != constQueue.end(); ++i) {
            AGREGATE_TEST_RESULT(testResult, (*i == 42));
        }

        bool exceptionThrown = false;
        Queue<int>::ConstIterator endConstIterator = constQueue.end();
        try {
            ++endConstIterator;
        }
        catch (Queue<int>::ConstIterator::InvalidOperation& e) {
            exceptionThrown = true;
        }
        AGREGATE_TEST_RESULT(testResult, exceptionThrown);

        return testResult;
    }

}

#endif //EX3_MATAM_QUEUE_TESTS_H
