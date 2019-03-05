/**
 * S19 CSCI 332 Design and Analysis of Algorithms
 *
 * Project-1 Efficient Russian Multiplication
 *
 * A La Russe Multiplication Algorithm class
 *
 * Phillip J. Curtiss, Assistant Professor
 * pcurtiss@mtech.edu, 406-496-4807
 * Department of Computer Science, Montana Tech
 */

#ifndef ALA_RUSSE_H
#define ALA_RUSSE_H

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

// A value to count the number of bit shifts beformed by Multiply
extern int shiftCounts;

// Takes two values of TVal and performs russian peasant multiplication. It then
// returns a TVal with the result.
TVal Multiply(const TVal nVal, const TVal mVal);
#endif