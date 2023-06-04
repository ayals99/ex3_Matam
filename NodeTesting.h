#ifndef EX3_MATAM_NODETESTING_H
#define EX3_MATAM_NODETESTING_H

#include "Node.h"

namespace NodeTests {

    bool testNodeMethods(){
        return true;
    }

    bool testModuleFunctions(){

        return true;
    }

    bool testConstructors(){
        Node a(5);
        Node<int> b(5);
        if(a != b){
            return false;
        }
        Node<double> c(4.0);
        Node<double> d (5.0);
        if(c == d){
            return false;
        }
        return true;
    }

    bool NodeTestGetItem(){
        Node<char> a = Node<char>('a');
        char d = *(a.Node<char>::getPointerToItem());
        if(d != 'a'){
            return false;
        }

        Node<int> b(2);
        int e = *(b.Node<int>::getPointerToItem());
        if(e != 2){
            return false;
        }

        Node<double> c(3.0);
        double f = *(c.Node<double>::getPointerToItem());
        if(f != 3.0){
            return false;
        }

        Node<int> q(3);
        Node<int> t(4);
        q.Node<int>::setPointerToNext(&t);
        if(*(q.getPointerToNext()->getPointerToItem()) != 4){
            return false;
        }

        return true;
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
