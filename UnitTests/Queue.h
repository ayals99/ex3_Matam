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
        Node& operator=(const Node &other) {
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
    class EmptyQueue {};

    /** Constructor for Queue */
    Queue() : m_head(nullptr), m_size(EMPTY) {}

    /** Copy constructor for Queue
     * @param: other queue to copy
     *
     * @return: A new queue with the same items as the "other" queue, independent of the "other" queue
     */
    Queue(const Queue& other) : m_head(nullptr), m_size(EMPTY) {
        try{
            for (Queue<T>::ConstIterator it = other.begin(); it != other.end(); ++it) {
                // Since pushback creates a new node from the item, even though we use a constIterator, the created Queue should not be const.
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

    /** Assignment operator for Queue
     * @param: other queue to copy
     *
     * @note: In case of self assignment, do nothing
     * @constraints: In case of alloc fail ,need to throw std::bad_alloc and leave the original queue unchanged
     * @constraints: The nodes that are created when initializing the temporary queue should not be deleted, but should
     * be inserted to the new queue we are creating
     *
     * @explain: We try to add all "other" queue's items to the end of the original queue with pushBack().
     *           If all allocations succeed, we remove the original queue's data with popFront().
     *           If an allocation fails, we remove the additional nodes we successfully allocated with popFront()
     *           and leave the original queue's data untouched.
     *
     * @return: Reference to a new queue with the same items as the "other" queue, independent of the "other" queue
     */
    Queue<T>& operator=(const Queue& other) {
        if(this == &other) {
            return *this;
        }
        int successfulAllocCount = 0;
        int originalSize = m_size;
        Node* originalHead = (originalSize == 0) ? nullptr : m_head;
        try {
            // Try allocating all the nodes (and items) of the "other" queue to the end of the original queue
            for(Queue<T>::ConstIterator it = other.begin(); it != other.end(); ++it) {
                pushBack(*it);
                successfulAllocCount++;
            }
            // Remove the original queue's data if all new node (and item) allocations succeeded
            for(int i = 0; i < originalSize; ++i) {
                popFront();
            }
        }
        catch (const std::bad_alloc& e) {
            if(originalSize != 0) { //  If the original queue had data then we need to leave that data untouched
                // Find the pointer to the node where the nodes we successfully allocated start
                Node* lastOfOriginalNodes = m_head;
                for (int i = 0; i < originalSize - 1; ++i) {
                    lastOfOriginalNodes = lastOfOriginalNodes->getPointerToNext();
                }
                // Save the pointer to the first of the additional nodes we successfully allocated:
                Node* startOfAddedNodes = lastOfOriginalNodes->getPointerToNext();
                // Set the m_next in the last node of the original queue to "nullptr",
                // to mark the end of the original queue:
                lastOfOriginalNodes->setPointerToNext(nullptr);
                // Temporarily set the m_head to the first node of the additional nodes
                // in order to later remove them by using popFront():
                m_head = startOfAddedNodes;
            }
            for(int i = 0; i < successfulAllocCount; ++i) { // Remove the additional nodes we successfully allocated
                popFront();
            }
            // Restore the original queue to its untouched state
            m_head = originalHead;
            throw e;
        }
        return *this;
    }

    /** Destructor for Queue*/
    ~Queue() {
        while(m_size > 0) {
            popFront();
        }
    }

    class ConstIterator {
    private:
        Node const* m_pointer; // const here isn't necessary since operator * returns const T&, but we'll keep it

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
        Node* m_pointer;

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
        class InvalidOperation {};

        /** Operator implementations */

        /**
         * Dereference operator for Iterator
         * @return: reference to m_item
         */
        T& operator*() {
            if (this->m_pointer == nullptr) {
                throw InvalidOperation();
            }
            return m_pointer->getReferenceToItem();
        }


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

        Iterator& operator+(int valueToIncrement) {
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

    ConstIterator begin() const {
        return ConstIterator(m_head);
    }

    /** end() function for non-const iterators
    * @return reference to the one after the last element of the queue
    */
    Iterator end() {
        return Iterator(nullptr);
    }

    /** end() function for const iterators
    * @return reference to the one after the last element of the queue, but const so can't change the value
    */
    ConstIterator end() const {
        return ConstIterator(nullptr);
    }

    // Used in pushBack function
    Node* findLastNode(Queue<T>& queue) {
        if (queue.m_size == EMPTY) {
            return m_head;
        }
        Node* last = queue.m_head;
        while (last->Node::getPointerToNext() != nullptr) {
            last = last->Node::getPointerToNext();
        }
        return last;
    }

    // Used in pushBack function
    void insertAfter(Node *firstNode, Node *secondNode) {
        firstNode->Node::setPointerToNext(secondNode);
    }

    /** pushBack function
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
            Node* lastElement = findLastNode(*this);
            insertAfter(lastElement, nodeToPush);
        }
        m_size += 1;
        return *this;
    }

    /** front function
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

template<typename T, typename FUNC>
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

template<typename T, typename FUNC>
void transform(Queue<T>& queueToTransform, FUNC transformFunction) {
    for (typename Queue<T>::Iterator i = queueToTransform.begin(); i != queueToTransform.end(); ++i) {
        T& itemPointer = *i;
        transformFunction(itemPointer);
    }
}

#endif