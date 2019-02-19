/**
 * S19 CSCI 332 Design and Analysis of Algorithms
 *
 * Project-1 Efficient Russian Multiplication
 *
 * Balanced Search Tree Node implementation
 *
 * Phillip J. Curtiss, Assistant Professor
 * pcurtiss@mtech.edu, 406-496-4807
 * Department of Computer Science, Montana Tech
 */

#ifndef BSTNODE_IMP
#define BSTNODE_IMP

#include <memory>

#include "BSTnode.h"

// constructor
template <class ItemType>
BSTnode<ItemType>::BSTnode(const ItemType item,
                           const BSTnode_ptr<ItemType> left,
                           const BSTnode_ptr<ItemType> right)
    : item(item), left(left), right(right) {}  // end constructor

// return the item at this node
template <class ItemType>
ItemType BSTnode<ItemType>::getItem() const {
    return this->item;
}  // end getItem

// return a shared BSTnode pointer for the left subtree at this node
template <class ItemType>
BSTnode_ptr<ItemType> BSTnode<ItemType>::getLeft() const {
    return this->left;
}  // end getLeft

// return a shared BSTnode pointer for the right subtree at this node
template <class ItemType>
BSTnode_ptr<ItemType> BSTnode<ItemType>::getRight() const {
    return this->right;
}  // end getRight

template <class ItemType>
int BSTnode<ItemType>::getHeight() const {
    return this->height;
}

// set the item at this node
template <class ItemType>
void BSTnode<ItemType>::setItem(const ItemType anItem) {
    this->item = anItem;
}  // end setItem

// set the left shared BSTnode pointer at this node to the subtree parameter
template <class ItemType>
void BSTnode<ItemType>::setLeft(const BSTnode_ptr<ItemType> subtree) {
    this->left = subtree;
}  // end setLeft

// set the right shared BSTnode pointer at this node to the subtree parameter
template <class ItemType>
void BSTnode<ItemType>::setRight(const BSTnode_ptr<ItemType> subtree) {
    this->right = subtree;
}  // end setRight

template <class ItemType>
void BSTnode<ItemType>::setHeight(const int h) {
    this->height = h;
}

#endif