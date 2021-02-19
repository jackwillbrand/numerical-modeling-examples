#ifndef CHOLESKY_DECOMP_H
#define CHOLESKY_DECOMP_H

#include "../containers/MyMatrix.h"
#include "../containers/MyVector.h"
#include <cmath>

/*!
 * @brief cholesky decomp class, a functor to wrap around decomposed matrix
 */
class CholeskyDecomp;

/*!
 * @brief swap function, swaps contents of a and b
 * @pre none
 * @param[in,out] a lhs of CholeskyDecomp swap
 * @param[in,out] b rhs of CholeskyDecomp swap
 * @post swaps the contents of CholeskyDecomp objects a and b
 */
void swap(CholeskyDecomp &a, CholeskyDecomp &b);

/*!
 * @brief output operator, outputs contents of cholesky 'cd' to console
 * @pre none
 * @param[in,out] out ostream object to print contents
 * @param[in] cd choleskydecomp object to print to console
 * @post prints contents of cd to stdout
 * @returns the modified ostream object after printing
 */
ostream& operator<<(ostream &out, const CholeskyDecomp &cd);

/*!
 * @brief cholesky decomp class, a functor to wrap around decomposed matrix
 */
class CholeskyDecomp
{
    private:
        MyMatrix<double> A; //! cholesky decomposed matrix A
        int n; //! number of rows (and cols) of double matrix A

    public:
        /*!
         * @brief default constructor, create empty matrix of size zero
         * @pre none
         * @post creates choleskydecomp object with size 0
         */
        CholeskyDecomp(): A(MyMatrix<double>()), n(0) {}

        /*!
         * @brief param. constructor, given existing nxn matrix m
         * @pre matrix m must be able to be cholesky decomposed
         * @param[in] m matrix to be converted to cholesky object
         * @post creates choleskydecomp object given existing matrix m
         */
        explicit CholeskyDecomp(const MyMatrix<double> &m);

        /*!
         * @brief copy constructor, given existing choleskydecomp object
         * @pre none
         * @param[in] cd existing choleskydecomp object to copy
         * @post creates choleskydecomp object identical to cd
         */
        CholeskyDecomp(const CholeskyDecomp &cd);

        /*!
         * @brief assignment operator, assigns calling object equal to cd
         * @pre none
         * @param[in] cd choleskydecomp object to copy to calling obj
         * @post copies contents of cd to calling object
         * @returns the modified calling object after swap
         */
        CholeskyDecomp& operator=(CholeskyDecomp &cd);

        /*!
         * @brief eval operator, solves matrix equation Ax=b efficiently
         *        using upper and triangle matrices to reduce time complexity
         * @pre matrix A and vector b must have equal number of rows
         * @param[in] b b vector of equation Ax = b
         * @throw std::invalid_argument if b and A have different sizes
         * @post performs double back substitution to solve for x
         * @returns a vector representing x values
         */
        MyVector<double> operator()(MyVector<double> b);

        /*!
         * @brief helper function, decomposes a matrix, stores result in l
         * @pre a and l must be matrices of the same size
         * @param[in] a original matrix, to be decomposed
         * @param[out] l result matrix, stores decomposed result
         * @throw std::invalid_argument if a, l are different sizes
         * @post decomposes matrix a via cholesky decomposition, stores in l
         */
        void decompose(const MyMatrix<double> &a, MyMatrix<double> &l);

        /*!
         * @brief const access operator, access vector in matrix A at index i
         * @pre i must be in range of matrix A
         * @param[in] i matrix index to access
         * @throw std::out_of_range if i out of range of matrix A
         * @post access the matrix vector at index i
         * @returns the accessed matrix vector at index i
         */
        MyVector<double> operator[](const size_t i) const;

        /*!
         * @brief access operator, return reference to vector in at matrix index i
         * @pre i must be in range of matrix A
         * @param[in] i matrix index to access
         * @throw std::out_of_range if i out of range of matrix A
         * @post access matrix vector at index i
         * @returns the reference to accessed matrix vector at index i
         */
        MyVector<double>& operator[](const size_t i);

        /*!
         * @brief size function, returns size of member obj. matrix A 
         * @pre none
         * @post gets the size of the matrix A
         * @returns the size of the matrix A
         */
        int size() const { return n; }

        /*!
         * @brief swap function, swaps contents of a and b
         * @pre none
         * @param[in,out] a lhs of CholeskyDecomp swap
         * @param[in,out] b rhs of CholeskyDecomp swap
         * @post swaps the contents of CholeskyDecomp objects a and b
         */
        friend void swap(CholeskyDecomp &a, CholeskyDecomp &b);

        /*!
         * @brief output operator, outputs contents of cholesky 'cd' to console
         * @pre none
         * @param[in,out] out ostream object to print contents
         * @param[in] cd choleskydecomp object to print to console
         * @post prints contents of cd to stdout
         * @returns the modified ostream object after printing
         */
        friend ostream& operator<<(ostream &out, const CholeskyDecomp &cd);
};

#include "CholeskyDecomp.hpp"

#endif