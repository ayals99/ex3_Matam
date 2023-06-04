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
            delete m_item;
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

    /**
     * @brief: Copy Constructor for Queue
     * @param: other queue to copy
     * @return: A new queue with the same items as the "other" queue
     */
    Queue(const Queue &other) : m_head(), m_size(EMPTY) {
        Node *current = other.m_head;
        while (current != nullptr) {
            pushBack(current->getReferenceToItem());
            current = current->getPointerToNext();
        }
    }

    class ConstIterator {
    private:
        Node *m_pointer;
        friend class Queue<T>;
    public:
        explicit ConstIterator(Node *pointer) {
            m_pointer = pointer;
        }

        class InvalidOperation {};

        /**
         * @brief: dereference operator for Iterator
         * @param: *
         * @return: pointer to the node
         */
        const T &operator*() const {
            if (this->m_pointer == nullptr) {
                throw InvalidOperation();
            }
            return m_pointer->getReferenceToItem();
        }

        const ConstIterator& operator++() {
            if (this->m_pointer == nullptr) {
                throw InvalidOperation();
            }
            m_pointer = m_pointer->getPointerToNext();
            return *this;
        }

        const ConstIterator& operator++(int) const {
            if (this->m_pointer == nullptr) {
                throw InvalidOperation();
            }
            ConstIterator tempIterator(m_pointer);
            m_pointer = m_pointer->getPointerToNext();
            return tempIterator;
        }

        bool operator==(const ConstIterator &other) const {
            return m_pointer == other.m_pointer;
        }

        bool operator!=(const ConstIterator &other) const {
            return m_pointer != other.m_pointer;
        }

        ConstIterator &operator+(int valueToIncrement) const{
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

        friend class Queue<T>;

    public:
        explicit Iterator(Node *pointer) {
            m_pointer = pointer;
        }

        class InvalidOperation {
        };

        /**
         * @brief: dereference operator for Iterator
         * @param: *
         * @return: pointer to the node
         */
        T &operator*() const {
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

        Iterator& operator++(int)  {
            if (this->m_pointer == nullptr) {
                throw InvalidOperation();
            }
            Iterator tempIterator(m_pointer);
            m_pointer = m_pointer->getPointerToNext();
            return &tempIterator;
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

    const ConstIterator begin() const {
        return ConstIterator(m_head);
    }

    /**
    * @return reference to the one after the last element of the queue
    */
    Iterator end() {
        return Iterator(nullptr);
    }

    const ConstIterator end() const {
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
        Node* nodeToPush = new Node(toInsert);
        if (this->m_size == EMPTY) {
            m_head = nodeToPush;
            m_size += 1;
            return *this;
        }
        else {
            Node *lastElement = findLast(*this);
            insertAfter(lastElement, nodeToPush);
            m_size += 1;
            return *this;
        }
    }

    /** front
     * @param: queue
     *
     * @return reference to first element of the queue
     */
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
    int size() {
        return m_size;
    }
};

template<class T>
std::ostream &operator<<(std::ostream &os, Queue<T> queue);

template<typename T, typename FUNC >
Queue<T> filter(Queue<T>& queue, FUNC filterFunction) {
    Queue<T> newFilteredQueue;
    for (typename Queue<T>::Iterator i = queue.begin(); i != queue.end(); ++i){
        if(filterFunction(*i) == true){
            newFilteredQueue.pushBack(*i);
        }
    }
    return newFilteredQueue;
}

template<typename T, typename FUNC >
void transform(Queue<T>& queue, FUNC transformFunction) {
    for (typename Queue<T>::Iterator i = queue.begin(); i != queue.end(); ++i) {
        T& itemPointer = *i;
        transformFunction(itemPointer);
    }
}

#endif