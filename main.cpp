/**
 * S19 CSCI 332 Design and Analysis of Algorithms
 *
 * Project-1 Efficient Russian Multiplication
 *
 * Main driver program
 *
 * Phillip J. Curtiss, Assistant Professor
 * pcurtiss@mtech.edu, 406-496-4807
 * Department of Computer Science, Montana Tech
 */

#include <climits>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

#include "AlaRusse.h"
#include "BST.h"
#include "BSTnode.h"

using std::cout;
using std::endl;
using std::string;

/**
 * Using a binary search tree and your alarusse object
 * compute the result of multiplying the numbers given
 * as command line arguments in the most efficient
 * algorithmically
 *
 * @param argc - the number of command line arguments
 *               includes the name of the program
 * @param argv - an array of character pointers representing
 *               each command line argument
 */
extern int shiftCounts;

int main(int argc, char* argv[]) {
    // initialize a binary search tree
    BST<TVal> multSearchTree;

    // insert each of the command line arguments into
    // the binary search tree by converting each command
    // line argument to an integer and then inserting into the BST
    for (int ndx = 1; ndx < argc; ndx++) {
        // convert the command line argument to an int
        TVal nodeItem;
        nodeItem.iVal = atoi(argv[ndx]);
        // output the numbers processed
        // cout << "Inserting " << nodeItem.iVal << " into BST." << endl;
        multSearchTree.insert(nodeItem);
        // insert argInt into binary search tree
    }  // end for

    // if BST is empty, return EXIT_FAILURE
    if (multSearchTree.isEmpty()) {
        return EXIT_FAILURE;
    }

    // perform alarusse with the tree in the most efficient way possible
    TVal result;
    result.iVal = 16;

    int accesses = 0;

    auto countAccesses = [&accesses](TVal nodeItem) { accesses++; };

    // get the largest and smallest values from the tree to seed the
    // multiplication
    BSTnode_ptr<TVal> min = multSearchTree.getMin(countAccesses);
    BSTnode_ptr<TVal> max = multSearchTree.getMax(countAccesses);

    // find the initial seed result with the largest two values
    result = Multiply(min->getItem(), max->getItem());

    // remove the largest and smallest values from the tree
    multSearchTree.remove(min->getItem());
    multSearchTree.remove(max->getItem());

    auto mult = [&result, &accesses](TVal nodeItem) {
        accesses++;
        if (result.iVal < nodeItem.iVal) {
            result = Multiply(result, nodeItem);
            return;
        }
        result = Multiply(nodeItem, result);
    };

    // perform in order traversal multiplying items together as it traverses the
    // tree
    multSearchTree.inorderTraversal(multSearchTree.getRoot(), mult);

    // output the result and the efficiency metric(s)
    auto print = [](TVal i) {
        if (i.iVal > 0) {
            cout << i.iVal << " ";
            return;
        }
        cout << i.ullVal << " ";
        return;
    };

    cout << "Multiplication of the operands below is: " << result.ullVal
         << endl;
    multSearchTree.inorderTraversal(multSearchTree.getRoot(), print);
    cout << endl;
    cout << "Shifts performed is " << shiftCounts << " (via A La Russe)"
         << endl;
    cout << "Accesses for operands is " << accesses << " (via AVL BST)" << endl;

    // terminate the application
    return EXIT_SUCCESS;
}