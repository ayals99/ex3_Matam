#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "Node.h"


static const int EMPTY = 0;

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
    Queue(): m_head(), m_size(EMPTY){}

    /**
     * @brief: Copy Constructor for Queue
     * @param: other queue to copy
     * @return: A new queue with the same items as the "other" queue
     */
    Queue(const Queue& other): m_head(), m_size(EMPTY) {
        queueNode *current = other.m_head;
        while (current != nullptr) {
            push(current->m_item);
            current = getNext(current);
        }
    }

    class EmptyQueue{};

    class iterator{
        class InvalidOperation{};

    private:
        queueNode* m_pointer;
        friend class Queue<T>;

    public:
        queueNode* operator*() const {
            if(*this == nullptr){
                throw InvalidOperation();
            }
            return *m_pointer;
        }

        queueNode* operator++() const{
            if(*this == nullptr){
                throw InvalidOperation();
            }
            return getNext(m_pointer);;
        }

        queueNode* operator++(int) const {
            if(*this == nullptr){
                throw InvalidOperation();
            }
            return getNext(m_pointer);;
        }

        bool operator==(const iterator& other) const {
            return m_pointer == other.m_pointer;
        }

        bool operator!=(const iterator& other) const {
            return m_pointer != other.m_pointer;
        }

        iterator& operator+(int valueToIncrement){
            queueNode current = *this;
            if(valueToIncrement < 0){
                throw InvalidOperation();
            }
            while(current != nullptr && valueToIncrement > 0){
                *this = current;
                current = getNext(current);
                valueToIncrement -= 1;
            }
            return *this;
        }

    };

    iterator begin(){
        return iterator(m_head);
    }
    const iterator begin() const{
        return iterator(m_head);
    }

    /**
     * @return reference to the one after the last element of the queue
     */
    iterator end(){
        return iterator(m_head) + m_size;
    }

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
        insertAfter(nodeToPush, lastElement); //TODO: write insertAfter
        m_size++;
        return *this;
    }

    /**
     * @param: queue
     *
     * @return reference to first element of the queue
     */
    T front(const Queue& queue) const{
        if(m_size == EMPTY){
            throw EmptyQueue();
        }
        return queueNode::nodeGetItem(m_head);
    }

    /**
     * @param: queue
     *
     * @description: removes the first element of the queue
     *
     * @return none
     */
    void popFront(Queue& queue){
        queueNode firstElement = queue.m_head;
        if(firstElement == nullptr){
            throw EmptyQueue();
        }
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
        for(auto queueIterator:queue){
            transformFunc(nodeGetItem(*queueIterator));
        }
    }

    void printQueue(const Queue queue) const{
        queueNode currentNode = m_head;
        assert(queue == nullptr);
        if(front(queue) == nullptr){
            std::cout << "Queue is empty\n";
            return;
        }
        std::cout << "Queue: ";
        for (const auto &item: queue){
            std::cout << item << " ";
        }
        std::cout << "\n";
    }

};


#endif