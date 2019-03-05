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

// used to hold values of type int or values of unsigned long long int
// but not both - you may check the value - if the TVal.iVal < 0 then
// access the value in TVal.ullVal for the correct value
using TVal = union val {
    // 16 bits; max_int 2147483647 2^31 - 1
    int iVal = -1;
    // 64 bits; max_ullint 18446744073709551615 2^64-1
    unsigned long long ullVal;
    bool operator<(const val& t) const {
        // Check to see if the iVal has overflowed
        if (this->iVal & 0x8000 || t.iVal & 0x8000) {
            return this->ullVal < t.ullVal;
        }
        return this->iVal < t.iVal;
    }

    bool operator>(const val& t) const {
        // Check to see if the iVal has overflowed
        if ((this->iVal & 0x8000) || (t.iVal & 0x8000)) {
            return this->ullVal > t.ullVal;
        }
        return this->iVal > t.iVal;
    }

    val operator=(const val& t) {
        this->ullVal = t.ullVal;
        this->iVal = t.iVal;
        return *this;
    }
};

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

int shitftCounts = 0;

TVal russoMult(const TVal nVal, const TVal mVal) {
    // check if the value has overflowed an int
    TVal sum;
    sum.iVal = 0;
    cout << "Calculating" << endl;

    for (unsigned long long n = nVal.ullVal, m = mVal.ullVal; n >= 1;
         n >>= 1, m <<= 1) {
        // check if n is odd
        cout << "n : " << n << " m: " << m << endl;
        if (n % 2) {
            sum.ullVal += m;
            if (n == 1) {
                return sum;
            }
        }
        shitftCounts += 2;
    }
    return sum;
}

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

    BSTnode_ptr<TVal> min = multSearchTree.getMin(countAccesses);
    BSTnode_ptr<TVal> max = multSearchTree.getMax(countAccesses);

    result = russoMult(min->getItem(), max->getItem());

    multSearchTree.remove(min->getItem());
    multSearchTree.remove(max->getItem());

    auto mult = [&result, &accesses](TVal nodeItem) {
        accesses++;
        if (result.iVal < nodeItem.iVal) {
            result = russoMult(result, nodeItem);
            return;
        }
        result = russoMult(nodeItem, result);
    };

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
    cout << "Shifts performed is " << shitftCounts << " (via A La Russe)"
         << endl;
    cout << "Accesses for operands is " << accesses << " (via AVL BST)" << endl;

    // terminate the application
    return EXIT_SUCCESS;
}