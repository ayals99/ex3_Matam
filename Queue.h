#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"
#include <iostream>

static int EMPTY = 0;

template<class T>
class Queue{
    typedef Node<T> queueNode;

private:
    queueNode m_head;
    int m_size;

public:
    /**
     * @brief: Constructor for Queue
     */
    Queue(): m_head(EMPTY), m_size(0){}

    class iterator{

    private:
        queueNode* m_pointer;
        friend class Queue<T>;

    public:
        queueNode* operator*() const {
            return *m_pointer;
        }

        queueNode* operator++() const{
            assert(*this == nullptr);
            return getNext(m_pointer);;
        }

        queueNode* operator++(int) const {
            assert(*this == nullptr);
            return getNext(m_pointer);;
        }

        bool operator==(const iterator& other) const {
            return m_pointer == other.m_pointer;
        }

        bool operator!=(const iterator& other) const {
            return m_pointer != other.m_pointer;
        }
        //TODO: iterator needs to be finished
    };

    /**
     * @param: item to insert to the
     *
     * @return reference to the queue, so we can concatenate functions
     *
     * @note: the item is copied, not inserted itself into the queue
     */
    Queue& pushBack(const T toInsert){
        queueNode nodeToPush = new queueNode(toInsert);
        queueNode lastElement = findLast(m_head);
        insertAfter(nodeToPush, lastElement);
        m_size++;
        return *this;
    }

    /**
     * @param: queue
     *
     * @return reference to first element of the queue
     */
    queueNode front(const Queue& queue) const{
        return m_head;
    }

    /**
     * @param: queue
     *
     * @description: removes the first element of the queue
     *
     * @return none
     */
    void popFront(Queue& queue){
        queueNode firstElement = front(queue);
        m_head = getNext(firstElement);
        delete firstElement;
        m_size--;
    }

    /**
     * @param: queue
     *
     * @return number of elements in the queue
     */
    int size(Queue& queue){
        return m_size;
    }

    Queue& filter(Queue& queue){

    }

    void transform(Queue& queue, void (*transformFunc)(T&)){
        queueNode currentNode = m_head;
        while(currentNode != nullptr){
            T& item = getItem(currentNode);
            transformFunc(item);
            currentNode = getNext(currentNode);
        }
    }
};


#endif