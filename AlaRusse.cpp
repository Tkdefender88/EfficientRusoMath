/**
 * S19 CSCI 332 Design and Analysis of Algorithms
 *
 * Project-1 Efficient Russian Multiplication
 *
 * A La Russe Multiplication Algorithm implementation
 *
 * Phillip J. Curtiss, Assistant Professor
 * pcurtiss@mtech.edu, 406-496-4807
 * Department of Computer Science, Montana Tech
 */

#ifndef ALA_RUSSE_CPP
#define ALA_RUSSE_CPP

#include "AlaRusse.h"
int shiftCounts = 0;

TVal Multiply(TVal nVal, TVal mVal) {
    // check if the value has overflowed an int
    TVal sum;
    sum.iVal = 0;
    for (unsigned long long n = nVal.ullVal, m = mVal.ullVal; n >= 1;
         n >>= 1, m <<= 1) {
        // check if n is odd
        if (n % 2) {
            sum.ullVal += m;
            if (n == 1) {
                return sum;
            }
        }
        shiftCounts += 2;
    }
    return sum;
}
#endif