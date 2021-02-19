#ifndef MY_KRONECKER_H
#define MY_KRONECKER_H

#include "containers/MyMatrix.h"

/*! my kronecker class, functor to perform kronecker product of two matrices
 * @brief MyKronecker class, functor to calc kronecker product of two matrices
 */
template <typename T>
struct MyKronecker
{
    /*! function operator, calculates kronecker product of m1 and m2, return result
     * @brief function operator, calc kronecker product of m1 and m2, return result
     * @pre type T must be capable of multiplication
     * @param[in] m1 lhs of kronecker product
     * @param[in] m2 rhs of kronecker product
     * @post calculates the kronecker product (m1 x m2)
     * @returns the calculated kronecker product (m1 x m2)
     */
    MyMatrix<T> operator()(const MyMatrix<T> &m1, const MyMatrix<T> &m2) const;
};

#include "MyKronecker.hpp"

#endif