#ifndef EX3_MATAM_NODE_H
#define EX3_MATAM_NODE_H


template<class S>
class Node{
    typedef Node& NodePtr;

private:
    S& m_item;
    NodePtr m_next;
    NodePtr m_previous;

public:
    /**
     * @description: Constructor for Node
     * @param: node
     * @return: item of the node
     */
    Node():m_item(nullptr), m_next(nullptr), m_previous(nullptr){}

    /**
     * @description: Constructor for Node
     * @param: item to insert to the node
     * @note: the item is copied, not inserted itself into the node
     * @return: Node
     */
    explicit Node(S* item): m_next(nullptr), m_previous(nullptr){
        m_item = new S(*item);
    }

    /**
     * @description: Copy Constructor for Node
     * @param: other node to copy
     * @return: Node
     */
    Node(const Node& other){
        this->m_item = new S(*nodeGetItem(other));
        this->m_next = getNext(other);
        this->m_previous = getPrevious(other);
    }

    /**
     * @description: Destructor for Node
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
    S& nodeGetItem(NodePtr node) const {
        return m_item;
    }

    /**
     * @description: Getter for the next node
     * @param: node
     * @return: next node
     */
    NodePtr getNext(NodePtr node) const {
        return m_next;
    }
};



#endif
