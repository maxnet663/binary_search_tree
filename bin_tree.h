#ifndef REGISTRY_REGISTRY_H
#define REGISTRY_REGISTRY_H

#include "cstdlib"
#include <iostream>

//Binary search tree
template <class Key, class T>
class BinTree {

    class Node {
        friend BinTree<Key, T>;
        Key key;
        T data;

        /**
         * In order not to repeat elements already present in the tree,
         * their presence will be simulated with the help of a counter
         */
        size_t counter;

        Node* left;
        Node* right;

        //this constructor available only for the tree
        Node(Key in_key, T in_data)
            : key(in_key), data(in_data), counter(1), left(0), right(0) {};
    public:
        //keys are not allowed to be changed.
        const Key& getKey() const { return key; };

        T& getData() {return data; }
        const T& getData() const {return data; }

        size_t inline getCount() const { return counter; }

        Node* getLeft() { return left; }
        const Node* getLeft() const { return left; }

        Node* getRight() { return right; }
        const Node* getRight() const { return right; }

        void operator++(int) { counter++; } //postfix increment
        Node& operator=(const Node &other);
    };

    Node *root; // root of the tree

    // todo
    BinTree(const BinTree<Key, T> &other); //banned

public:
    BinTree() : root(0) {}
    ~BinTree() { clear(); }
    bool empty() { return !root; }

    // methods will be recursive, not iterative
    void add(Key k, T d);
    void remove(Key k);
    Node* find(Key k);
    void print();
    void clear();
    bool contains(Key k);
    size_t count(Key k);
private:
    void addToTree(const Key &k, const T &d);
    void deleteNode(Node* &curr_node, const Key &k);

    /**
     * this method is not quite typical
     * if the function does not find an element with such a key,
     * then it returns the expected parent
     * this will allow us to make it more useful for other methods
     */
    Node* search(Node *curr_node, const Key &k);

    Node* findMax(Node *curr_node);
    void print(const Node *curr_node);
    void clear(Node *curr_node);
};

template <class Key, class T>
void BinTree<Key, T>::add(Key k, T d) {
    if (empty()) { //if tree is empty create root
        root = new Node(k, d);
    } else {
        addToTree(k, d);
    }
}

template<class Key, class T>
void BinTree<Key, T>::addToTree(const Key &k, const T &d) {
    auto p = search(root, k);
    if (p->key == k) {
        p->counter++; //pretending to actually add a new element
    } else {
        p->key > k ? p->left = new Node(k, d) : p->right = new Node(k, d);
    }
}

template<class Key, class T>
void BinTree<Key, T>::remove(Key k) {
    if (empty()) {
        return;
    }
    Node* node_to_delete = search(root, k);

    /* if it's the intended parent, there's nothing to delete
     * this is the same as calling contains() and got false
     */
    if (node_to_delete->key != k) {
        return;
    }
    deleteNode(node_to_delete, k);
}

template<class Key, class T>
void BinTree<Key, T>::deleteNode(Node* &curr_node, const Key &k) {
    //if the node is a leaf
    if (!curr_node->left && !curr_node->right) {
        delete(curr_node);
        curr_node = 0;
    }
    //if the node has two children
    else if (curr_node->left && curr_node->right) {

        // we must find its unordered predecessor node
        Node *replacement = findMax(curr_node->left);

        //assignment operator is overloaded, so tree structures are safe
        *curr_node = *replacement;

        //by the way, the predecessor will either be a leaf
        //or will only have a left son
        deleteNode(curr_node->left, replacement->key);
    }
    //if the node has one child
    else {
        Node *child = curr_node->left ? curr_node->left : curr_node->right;
        Node *tmp = curr_node;
        curr_node = child;
        delete tmp;
    }
}


template <class Key, class T>
typename BinTree<Key, T>::Node* BinTree<Key, T>::find(Key k) {
    return search(root, k);
}

template <class Key, class T>
typename BinTree<Key, T>::Node*
BinTree<Key, T>::search(BinTree::Node *curr_node, const Key &k) {
    if (!curr_node) {
        return nullptr;
    }
    if (curr_node->key > k) {
        return curr_node->left ? search(curr_node->left, k) : curr_node;
    } else if (curr_node->key < k) {
        return curr_node->right ? search(curr_node->right, k) : curr_node;
    } else {
        return curr_node;
    }
}

template <class Key, class T>
typename BinTree<Key, T>::Node*
BinTree<Key, T>::findMax(BinTree::Node *curr_node) {
    return curr_node->right ? findMax(curr_node->right) : curr_node;
}

template <class Key, class T>
void BinTree<Key, T>::print() {
    print(root);
}

template <class Key, class T>
void BinTree<Key, T>::print(const Node *curr_node) {
    if (!curr_node)
        return;
    print(curr_node->left);
    for (int i = 0; i < curr_node->counter; i++) {
        std::cout << "[" << curr_node->key << "]: "
        << curr_node->data << std::endl;
    }
    print(curr_node->right);
}

template<class Key, class T>
void BinTree<Key, T>::clear() {
    clear(root);
}

template<class Key, class T>
void BinTree<Key, T>::clear(Node *curr_node) {
    if (!curr_node) {
        return;
    }
    clear(curr_node->left);
    clear(curr_node->right);
    delete curr_node;
}

template <class Key, class T>
typename BinTree<Key, T>::Node&
BinTree<Key, T>::Node::operator=(const BinTree::Node &other) {
    if (&other == this)
        return *this;
    key = other.key;
    data = other.data;
    counter = other.counter;
    return *this;
}

template <class Key, class T>
bool BinTree<Key, T>::contains(Key k) {
    if (empty()) {
        return false;
    }
    return search(root, k)->key == k;
}

template <class Key, class T>
size_t BinTree<Key, T>::count(Key k) {
    if (empty())
        return 0;
    auto res = search(root, k);
    return res->key == k ? res->getCount() : 0;
}


#endif //REGISTRY_REGISTRY_H
