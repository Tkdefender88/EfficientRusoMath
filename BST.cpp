/**
 * S19 CSCI 332 Design and Analysis of Algorithms
 *
 * Project-1 Efficient Russian Multiplication
 *
 * Balanced Search Tree Implementation
 *
 * Justin S. Bak, SE student
 * jbak@mtech.edu, 406-240-6477
 * Department of Computer Science, Montana Tech
 */

#ifndef BST_IMP
#define BST_IMP

#include <iostream>
#include <memory>

#include "BST.h"

template <class ItemType>
BST<ItemType>::BST() : root(nullptr) {}  // end of constructor

template <class ItemType>
void BST<ItemType>::insert(const ItemType item) {
    this->root = insert(root, item);
}

template <class ItemType>
BSTnode_ptr<ItemType> BST<ItemType>::insert(BSTnode_ptr<ItemType> root,
                                            const ItemType item) {
    if (root == NULL) {
        return std::make_shared<BSTnode<ItemType>>(item, nullptr, nullptr);
    }

    if (item < root->getItem()) {
        root->setLeft(insert(root->getLeft(), item));
    } else if (item > root->getItem()) {
        root->setRight(insert(root->getRight(), item));
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

    // return the unchanged node
    return root;
}

template <class ItemType>
int BST<ItemType>::height(BSTnode_ptr<ItemType> node) {
    if (node == nullptr) {
        return 0;
    }
    return node->getHeight();
}

template <class ItemType>
int BST<ItemType>::max(int a, int b) { return a > b ? a : b; }

template <class ItemType>
int BST<ItemType>::diff(BSTnode_ptr<ItemType> node) {
    if (node == nullptr) {
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
    return find(this->root, item);
}

template <class ItemType>
BSTnode_ptr<ItemType> BST<ItemType>::find(BSTnode_ptr<ItemType> root,
                                          const ItemType item) const {
    if (root->getItem() == item) {
        return root;
    }
    if (root == nullptr) {
        return root;
    }

    BSTnode_ptr x = (item < node->getItem()) ? find(root->getLeft(), item)
                                             : find(root->getRight(), item);

    return x;
}

template <class ItemType>
BSTnode_ptr<ItemType> BST<ItemType>::remove(BSTnode_ptr<ItemType> root,
                                            const ItemType item) {
    // begin with standard BST removal
    if (root == nullptr) {
        return root;
    }

    if (item < root->getItem()) {
        root->setLeft(remove(root->getLeft(), item));
    } else if (item > root->getItem()) {
        root->setRight(remove(root->getRight(), item));
    } else {  // if the item is the same, then this is the node to kill ;'(
        if ((root->getLeft() == nullptr) || (root->getRight() == nullptr)) {
            BSTnode_ptr<ItemType> temp = (root->getLeft() != nullptr)
                                             ? root->getLeft()
                                             : root->getRight();
            // in the case of no children
            if (temp == nullptr) {
                temp = nullptr;
                root = nullptr;
            } else {
                root = temp;
            }
        } else {
            BSTnode_ptr<ItemType> temp = getMinVal(root->getRight());

            root->setItem(temp->getItem());

            root->setRight(remove(root->getRight(), temp->getItem()));
        }
    }

    if (root == nullptr) {
        return root;
    }

    root->setHeight(1 + max(height(root->getLeft()), height(root->getRight())));

    return balance(root, item);
}

template <class ItemType>
BSTnode_ptr<ItemType> BST<ItemType>::getMinVal(BSTnode_ptr<ItemType> root) {
    // traverse the tree
    BSTnode_ptr<ItemType> current = root;
    for (; current->getLeft() != nullptr; current = current->getLeft()) {
    }
    return current;
}

template <class ItemType>
void BST<ItemType>::remove(const ItemType item) {
    this->root = remove(this->root, item);
}

template <class ItemType>
BSTnode_ptr<ItemType> BST<ItemType>::getRoot() const {
    return this->root;
}

template <class ItemType>
bool BST<ItemType>::isEmpty() const {
    return this->root == nullptr;
}

template <class ItemType>
BSTnode_ptr<ItemType> BST<ItemType>::getMin(func<ItemType> fptr) const {
    BSTnode_ptr<ItemType> n;
    for (n = this->root; n->getLeft() != nullptr; n = n->getLeft()) {
        if (fptr != nullptr) {
            fptr(n->getItem());
        }
    }
    return n;
}

template <class ItemType>
BSTnode_ptr<ItemType> BST<ItemType>::getMax(func<ItemType> fptr) const {
    BSTnode_ptr<ItemType> n;
    // move n along the tree until it can't move further
    for (n = this->root; n->getRight() != nullptr; n = n->getRight()) {
        // execute the function on every node as long as it's not nullptr
        if (fptr != nullptr) {
            fptr(n->getItem());
        }
    }
    // give back n
    return n;
}

template <class ItemType>
void BST<ItemType>::inorderTraversal(BSTnode_ptr<ItemType> node,
                                     func<ItemType> fptr) const {
    if (node->getLeft() != nullptr) {
        inorderTraversal(node->getLeft(), fptr);
    }
    // ensure the function passed is not null
    if (fptr != nullptr) {
        fptr(node->getItem());
    }
    if (node->getRight() != nullptr) {
        inorderTraversal(node->getRight(), fptr);
    }
}

#endif
