/**
 * S19 CSCI 332 Design and Analysis of Algorithms
 *
 * Project-1 Efficient Russian Multiplication
 *
 * Balanced Search Tree Implementation
 *
 * Phillip J. Curtiss, Assistant Professor
 * pcurtiss@mtech.edu, 406-496-4807
 * Department of Computer Science, Montana Tech
 */

#ifndef BST_IMP
#define BST_IMP

#include <memory>

#include "BST.h"

template <class ItemType>
BST<ItemType>::BST() : root(nullptr) {}  // end of constructor

template <class ItemType>
BSTnode_ptr<ItemType> BST<ItemType>::insert(BSTnode_ptr<ItemType> root,
                                            const ItemType item) {
    if (root == NULL) {
        return std::make_shared<BSTnode<ItemType>>(item, nullptr, nullptr);
    }

    if (item < root->getItem()) {
        root = insert(root->getLeft(), item);
    } else if (item > root->getItem()) {
        root = insert(root->getRight(), item);
    } else {
        // equal trees are not allowed in BST, simply return
        return root;
    }

    root->setHeight(1 + max(height(root->getLeft()), height(root->getRight())));

    // return the balanced root node
    return balance(root, item);
}

template <class ItemType>
BSTnode_ptr<ItemType> BST<ItemType>::balance(BSTnode_ptr<ItemType> root,
                                             ItemType item) {
    // find the height difference.
    int balance = diff(root);

    // Check the four cases of imbalance

    // Left Left case:
    if (balance > 1 && item < root->getLeft()->getItem()) {
        return llRotation(root);
    }
    // right right case:
    if (balance < -1 && item > root->getRight()->getItem()) {
        return rrRotation(root);
    }
    // left right case:
    if (balance > 1 && item > root->getLeft()->getItem()) {
        return lrRotation(root);
    }
    // right left case:
    if (balance < -1 && item < root->getRight()->getItem()) {
        return rlRotation(root);
    }

    return root;
}

template <class ItemType>
int BST<ItemType>::height(BSTnode_ptr<ItemType> node) {
    if (node == NULL) {
        return 0;
    }
    return node->getHeight();
}

template <class ItemType>
int BST<ItemType>::max(int a, int b) {
    return a > b ? a : b;
}

template <class ItemType>
int BST<ItemType>::diff(BSTnode_ptr<ItemType> node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->getLeft()) - height(node->getRight());
}

template <class ItemType>
BSTnode_ptr<ItemType> BST<ItemType>::rightRotate(BSTnode_ptr<ItemType> node) {
    // set variables
    BSTnode_ptr<ItemType> x = node->getLeft();
    BSTnode_ptr<ItemType> T2 = x->getRight();

    // perform the rotation
    x->setRight(node);
    node->setLeft(T2);

    // update heights
    node->setHeight(max(height(node->getLeft()), height(node->getRight())) + 1);
    x->setHeight(max(height(x->getRight()), height(x->getLeft())) + 1);

    // return new root
    return x;
}

template <class ItemType>
BSTnode_ptr<ItemType> BST<ItemType>::leftRotate(BSTnode_ptr<ItemType> node) {
    // set variables
    BSTnode_ptr<ItemType> y = node->getRight();
    BSTnode_ptr<ItemType> T2 = y->getLeft();

    // perform rotation
    y->setLeft(node);
    node->setRight(T2);

    // update heights
    node->setHeight(max(height(node->getLeft()), height(node->getRight())) + 1);
    y->setHeight(max(height(y->getLeft()), height(y->getRight())) + 1);

    return y;
}

template <class ItemType>
BSTnode_ptr<ItemType> BST<ItemType>::llRotation(BSTnode_ptr<ItemType> node) {
    return rightRotate(node);
}

template <class ItemType>
BSTnode_ptr<ItemType> BST<ItemType>::rrRotation(BSTnode_ptr<ItemType> node) {
    return leftRotate(node);
}

template <class ItemType>
BSTnode_ptr<ItemType> BST<ItemType>::rlRotation(BSTnode_ptr<ItemType> node) {
    node->setRight(rightRotate(node->getRight()));
    return leftRotate(node);
}

template <class ItemType>
BSTnode_ptr<ItemType> BST<ItemType>::lrRotation(BSTnode_ptr<ItemType> node) {
    node->setLeft(leftRotate(node->getLeft()));
    return rightRotate(node);
}

template <class ItemType>
BSTnode_ptr<ItemType> BST<ItemType>::find(const ItemType item) const {
    return;
}

template <class ItemType>
BSTnode_ptr<ItemType> BST<ItemType>::getRoot() const {
    return this->root;
}

template <class ItemType>
void BST<ItemType>::inorderTraversal(BSTnode_ptr<ItemType> node,
                                     func<ItemType>(item)) const {}

#endif