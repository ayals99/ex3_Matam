#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

static const int EMPTY = 0;

/**
 * @brief: Queue class
 * @tparam T: type of the items in the queue
 */
template<class T>
class Queue {

private:

    class Node {
    private:
        T* m_item;
        Node* m_next;

    public:
        /**
         * @description: Constructor for Node
         * @param: item to insert to the node
         * @note: the item is copied, not inserted itself into the node
         * @return: Node
         */
        explicit Node(const T& item) : m_next(nullptr) {
            T* newItem = new T(item);
            m_item = newItem;
        }

        /**
         * @description: Copy Constructor for Node
         * @param: other node to copy
         * @return: Node
         */
        Node(const Node &other) : m_item(new T(*other.m_item)), m_next(other.m_next) {}

        /**
         * @description: Assignment operator for Node
         * @param: other node to copy
         * @return: Node
         */
        Node &operator=(const Node &other) {
            if (this != &other) {
                delete m_item;
                m_item = new T(nodeGetItem(other));
                m_next = getNext(other);
            }
            return *this;
        }

        /**
         * @description: Destructor for Node, deletes the item
         */
        ~Node() {
            if(m_item != nullptr) {
                delete m_item;
            }
        }

        /** Getters */

        /**
         * @description: Getter the item of the node
         * @param: node
         * @return: item of the node
         */
        T& getReferenceToItem() const {
            return *m_item;
        }

        /**
         * @description: Getter for the next node
         * @param: node
         * @return: next node
         */
        Node* getPointerToNext() const {
            return m_next;
        }

        /** Setters */
        Node& setPointerToNext(Node *next) {
            m_next = next;
            return *this;
        }
    };

    Node *m_head;
    int m_size;

public:
    /** Exceptions*/
    class EmptyQueue {
    };

    /**
     * @brief: Constructor for Queue
     */
    Queue() : m_head(nullptr), m_size(EMPTY) {}

    /** Copy constructor for Queue
     * @param: other queue to copy
     *
     * @return: A new queue with the same items as the "other" queue, independent of the "other" queue
     */
    Queue(const Queue& other) : m_head(nullptr), m_size(EMPTY) {
        try{
            for (Queue<T>::ConstIterator it = other.begin(); it != other.end(); ++it) {
                pushBack(*it);
            }
        }
        catch(std::bad_alloc& e){
            while(m_size > 0){
                popFront();
            }
            throw e;
        }
    }

    void setLastNextToNull (Node* head, int size){
        Node *last = head;
        for (int i = 0; i < size; i++) {
            last = last->getPointerToNext();
        }
        last->setPointerToNext(nullptr);
    }

    /** Assignment operator for Queue
     * @param: other queue to copy
     *
     * @constraints: in case of fail of alloc, need to throw std::bad_alloc and leave the original queue as is
     * @constraints: in case of self assignment, do nothing
     * @constraints: The nodes that are created when initializing the temporary queue should not be deleted, but should
     * be inserted to the new queue we are creating
     *
     * @return: A new queue with the same items as the "other" queue
     */
    Queue<T>& operator=(const Queue&other) {
        if(this == &other) {
            return *this;
        }
        int successfulAlloc = 0;
        int originalSize = m_size;
        try {
            for(Queue<T>::ConstIterator it = other.begin(); it != other.end(); ++it) {
                pushBack(*it);
                successfulAlloc++;
            }
            for(int i = 0; i < originalSize; ++i) {
                popFront();
            }
        } catch (const std::bad_alloc& e) {
            Node *originalHead = (originalSize == 0) ? nullptr : m_head;
            if(originalSize != 0) {// Save the original queue's data
                // Find the pointer to the node where the nodes we successfully allocated start
                Node *lastOfOriginalNodes = m_head;
                Node *startOfNewQueue;
                for (int i = 0; i < originalSize - 1; ++i) {
                    lastOfOriginalNodes = lastOfOriginalNodes->getPointerToNext();
                }
                startOfNewQueue = lastOfOriginalNodes->getPointerToNext();
                lastOfOriginalNodes->setPointerToNext(nullptr);
                m_head = startOfNewQueue;
            }

            // Delete the nodes we successfully allocated
            for(int i = 0; i < successfulAlloc; ++i) {
                popFront();
            }
            // Return the original queue to its original state
            m_head = originalHead;

            // Assigning nullptr to the m_next of the last node in the original queue
//           setLastNextToNull(m_head, originalSize);
            throw e;
        }
        return *this;
    }

    ~Queue() {
        while(m_size > 0) {
            popFront();
        }
    }

    class ConstIterator {
    private:
        Node *m_pointer;
        friend class Queue<T>; // TODO: Check if this is needed
    public:
        /** Constructor for ConstIterator */
        explicit ConstIterator(Node* pointer) {
            m_pointer = pointer;
        }

        /** Assignment operator for ConstIterator */
        ConstIterator& operator=(const ConstIterator& other) {
            if(this != &other) {
                m_pointer = other.m_pointer;
            }
            return *this;
        }

        /**Exception for invalid operation*/
        class InvalidOperation {};

        /**
         * @brief: dereference operator for Iterator
         * @param: *
         * @return: pointer to the node
         */
        const T& operator*() const {
            if (this->m_pointer == nullptr) {
                throw InvalidOperation();
            }
            return m_pointer->getReferenceToItem();
        }

        /** Operator implementations */
        void operator++() {
            if (this->m_pointer == nullptr) {
                throw InvalidOperation();
            }
            m_pointer = m_pointer->getPointerToNext();
        }

        bool operator==(const ConstIterator &other) const {
            return m_pointer == other.m_pointer;
        }

        bool operator!=(const ConstIterator &other) const {
            return m_pointer != other.m_pointer;
        }

        ConstIterator& operator+(int valueToIncrement) const{
            Node *current = this->m_pointer;
            if (valueToIncrement < 0) {
                throw InvalidOperation();
            }
            while (current->getPointerToNext() != nullptr && valueToIncrement > 0) {
                this->m_pointer = current;
                current = current->getPointerToNext();
                valueToIncrement -= 1;
            }
            return *this;
        }
    };

    class Iterator {
    private:
        Node *m_pointer;
        friend class Queue<T>; // TODO: Check if this is needed

    public:
        /** Constructor for Iterator*/
        explicit Iterator(Node *pointer) {
            m_pointer = pointer;
        }

        /** Assignment operator for Iterator */
        Iterator& operator=(Iterator& other){
            if(this != &other) {
                m_pointer = other.m_pointer;
            }
            return *this;
        }

        /**Exception for invalid operation*/
        class InvalidOperation {
        };

        /**
         * @brief: dereference operator for Iterator
         * @return: pointer to the node
         */
        T& operator*() {
            if (this->m_pointer == nullptr) {
                throw InvalidOperation();
            }
            return m_pointer->getReferenceToItem();
        }

        /** Operator implementations */
        Iterator& operator++() {
            if (this->m_pointer == nullptr) {
                throw InvalidOperation();
            }
            m_pointer = m_pointer->getPointerToNext();
            return *this;
        }

        bool operator==(const Iterator &other) const {
            return m_pointer == other.m_pointer;
        }

        bool operator!=(const Iterator &other) const {
            return m_pointer != other.m_pointer;
        }

        Iterator &operator+(int valueToIncrement) {
            Node *current = this->m_pointer;
            if (valueToIncrement < 0) {
                throw InvalidOperation();
            }
            while (current->getPointerToNext() != nullptr && valueToIncrement > 0) {
                this->m_pointer = current;
                current = current->getPointerToNext();
                valueToIncrement -= 1;
            }
            return *this;
        }
    };

    Iterator begin() {
        return Iterator(m_head);
    }

    ConstIterator begin() const { // TODO: CHeck if const can be removed
        return ConstIterator(m_head);
    }

    /**
    * @return reference to the one after the last element of the queue
    */
    Iterator end() {
        return Iterator(nullptr);
    }

    ConstIterator end() const { // TODO: CHeck if const can be removed
        return ConstIterator(nullptr);
    }

    Node *findLast(Queue<T> &queue) {
        if (queue.m_size == EMPTY) {
            return m_head;
        }
        Node *last = queue.m_head;
        while (last->Node::getPointerToNext() != nullptr) {
            last = last->Node::getPointerToNext();
        }
        return last;
    }

    void insertAfter(Node *firstNode, Node *secondNode) {
        firstNode->Node::setPointerToNext(secondNode);
    }

    /** pushBack
     * @param: item to insert to the
     *
     * @return reference to the queue, so we can concatenate functions
     *
     * @note: the item is copied, not inserted itself into the queue
     */
    Queue<T>& pushBack(const T& toInsert) {
        Node* nodeToPush;
        try{
            nodeToPush = new Node(toInsert);
        }
        catch(std::bad_alloc& e){
            throw e;
        }
        if (this->m_size == EMPTY) {
            m_head = nodeToPush;
        }
        else {
            Node *lastElement = findLast(*this);
            insertAfter(lastElement, nodeToPush);
        }
        m_size += 1;
        return *this;
    }

    /** front
     * @param: queue
     *
     * @return reference to first element of the queue
     */
    const T& front() const{
        if (m_size == EMPTY) {
            throw EmptyQueue();
        }
        T& itemPointer = m_head->Node::getReferenceToItem();
        return itemPointer;
    }

    T& front() {
        if (m_size == EMPTY) {
            throw EmptyQueue();
        }
        T& itemPointer = m_head->Node::getReferenceToItem();
        return itemPointer;
    }

    /**
     * @param: queue
     *
     * @description: removes the first element of the queue
     *
     * @return none
     */
    void popFront() {
        Node* firstElement = m_head;
        if (firstElement == nullptr) {
            throw EmptyQueue();
        }
        m_head = m_head->Node::getPointerToNext();
        delete firstElement;
        m_size--;
    }

    /**
     * @param: queue
     *
     * @return number of elements in the queue
     */
    int size() const{
        return m_size;
    }
};

template<class T>
std::ostream &operator<<(std::ostream &os, Queue<T> queue);

template<typename T, typename FUNC >
Queue<T> filter(const Queue<T>& queueToFilter, FUNC filterFunction) {
    Queue<T> newFilteredQueue;
    for (typename Queue<T>::ConstIterator i = queueToFilter.begin(); i != queueToFilter.end(); ++i){
        if(filterFunction(*i) == true){
            try {
                newFilteredQueue.pushBack(*i);
            }
            catch(std::bad_alloc& e) {
                throw e;
            }
        }
    }
    return newFilteredQueue;
}

template<typename T, typename FUNC >
void transform(Queue<T>& queueToTransform, FUNC transformFunction) {
    for (typename Queue<T>::Iterator i = queueToTransform.begin(); i != queueToTransform.end(); ++i) {
        T& itemPointer = *i;
        transformFunction(itemPointer);
    }
}

#endif