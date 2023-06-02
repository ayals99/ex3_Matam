#ifndef EX3_MATAM_NODETESTING_H
#define EX3_MATAM_NODETESTING_H

#include "Node.h"

namespace NodeTests {

    bool testNodeMethods(){
        Node<int> a(5);
        Node<int> b(5);
        if(a != b){
            return false;
        }
    }

    bool testModuleFunctions(){
        Node<double> c = 4.0;
    }

    bool testConstructors(){
        Node<int> newNode = new Node<int>(1);
    }

    bool NodeTestGetItem(){

    }
}

void runNodeTest(){
    bool methodsResult = NodeTests::testNodeMethods();
    if(!methodsResult){
        std::cout << "Node methods test failed" << std::endl;
        return;
    }
    bool moduleResult = NodeTests::testModuleFunctions();
    if(!moduleResult){
        std::cout << "Node module test failed" << std::endl;
        return;
    }
    bool constructorResult = NodeTests::testConstructors();
    if(!constructorResult){
        std::cout << "Node Constructor test failed" << std::endl;
        return;
    }
    bool itemTestResult = NodeTests::NodeTestGetItem();
    if(!itemTestResult){
        std::cout << "Node item test failed" << std::endl;
        return;
    }
    std::cout << "Node tests passed" << std::endl;
}



#endif //EX3_MATAM_NODETESTING_H
