/**
 * S19 CSCI 332 Design and Analysis of Algorithms
 *
 * Project-1 Efficient Russian Multiplication
 *
 * Balanced Search Tree Node class
 *
 * Phillip J. Curtiss, Assistant Professor
 * pcurtiss@mtech.edu, 406-496-4807
 * Department of Computer Science, Montana Tech
 */

#ifndef BSTNODE_H
#define BSTNODE_H

#include <memory>

using std::shared_ptr;

// forward declaration of the templated BSTnode class
template <class ItemType>
class BSTnode;

// alias (typedef) for a shared pointer to the templated BSTnode
template <class ItemType>
using BSTnode_ptr = shared_ptr<BSTnode<ItemType> >;

// Stores a node item and pointers to the left and right child nodes
// in a Binary Search Tree
template <class ItemType>
class BSTnode {
   private:
    // the item stored at the node
    ItemType item;

    // shared pointers to the left and right subtrees
    BSTnode_ptr<ItemType> left, right;

    int height;

   public:
    // constructor
    BSTnode(const ItemType item, const BSTnode_ptr<ItemType> left,
            const BSTnode_ptr<ItemType> right);

    // accessors - getters
    ItemType getItem() const;
    BSTnode_ptr<ItemType> getLeft() const;
    BSTnode_ptr<ItemType> getRight() const;
    int getHeight() const;

    // mutators - setters
    void setItem(const ItemType item);
    void setLeft(const BSTnode_ptr<ItemType> left);
    void setRight(const BSTnode_ptr<ItemType> right);
    void setHeight(const int h);
};  // end BSTnode class

#include "BSTnode.cpp"
#endif