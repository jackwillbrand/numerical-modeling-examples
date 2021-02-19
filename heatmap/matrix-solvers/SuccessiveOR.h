#ifndef SUCCESSIVE_OR_H
#define SUCCESSIVE_OR_H

#include "../containers/MyMatrix.h"
using std::min;

/*!
 * @brief successiveor class, a functor to wrap around  successive 
 *        over-relaxation method
 */
class SuccessiveOR;

/*!
 * @brief relaxation parameter function, returns optimal relaxation param.
 * @pre none
 * @param[in] x i index loc. to help solve for relaxation param.
 * @param[in] y j index loc. to help solve for relaxation param.
 * @post returns relaxation param. value at given pos (x, y)
 * @returns relaxation param. for given pos (x, y)
 */
double get_w_value(const int x, const int y);
double get_w_value() { return 1.6; }

/*!
 * @brief swap function, swaps contents of a and b
 * @pre none
 * @param[in,out] a lhs of SuccessiveOR swap
 * @param[in,out] b lhs of SuccessiveOR swap
 * @post swaps the contents of SuccessiveOR objects a and b
 */
void swap(SuccessiveOR &a, SuccessiveOR &b);

/*!
 * @brief successiveor class, a functor to wrap around  successive 
 *        over-relaxation method
 */
class SuccessiveOR
{
    private:
        MyMatrix<double> A; //! matrix A to solve equation Ax = b
        int n; //! amount of rows/columns in matrix A
    
    public:
        /*!
         * @brief default constructor, initialize empty A matrix of size 0
         * @pre none
         * @post creates a successiveor object with empty member vars.
         */
        SuccessiveOR(): A(MyMatrix<double>()), n(0) {}

        /*!
         * @brief param. constructor, given existing nxn matrix m
         * @pre matrix m must be symmetric, positive-definite banded matrix
         * @param[in] m matrix to be used in successive or algorithm
         * @post creates successiveor object to use on matrix A
         */
        explicit SuccessiveOR(const MyMatrix<double> &m);

        /*!
         * @brief copy constructor, given existing successive or
         * @pre none
         * @param[in] bg existing successiveor object to copy
         * @post creates successiveor object identical to bg
         */
        SuccessiveOR(const SuccessiveOR &bg);

        /*!
         * @brief assignment operator, assigns calling object equal to bg
         * @pre none
         * @param[in] bg successiveor object to copy to calling obj
         * @post copies contents of bg to calling object
         * @returns the modified calling object after assignment
         */
        SuccessiveOR& operator=(SuccessiveOR &bg);

        /*!
         * @brief eval operator, solves matrix Ax = b efficiently via successive
         *        over-relaxation
         * @pre w must be in (1, 2), es must be positive, b must be same size as A
         * @param[in] b rhs of linear system Ax = b
         * @param[in] w relaxation parameter, weight of previous/next iteration
         * @param[in] es acceptable error threshold, algorithm stopping condition
         * @throw std::invalid_argument if w not in (1, 2), es not positive, b wrong size
         * @post performs successive over-relaxation to solve Ax = b
         * @returns solution vector x after linear system sufficiently solved
         */
        MyVector<double> operator()(const MyVector<double> &b, const double w, const double es);

        /*!
         * @brief access operator, return value of vector at matrix index i
         * @pre i must be in range of matrix A
         * @param[in] i matrix index to access
         * @throw std::out_of_range if i out of range of matrix A
         * @post return copy of matrix vector at index i
         * @returns the accessed matrix vector at index i
         */
        MyVector<double> operator[](const size_t i) const;

        /*!
         * @brief access operator, return reference to vector at matrix index i
         * @pre i must be in range of matrix A
         * @param[in] i matrix index to access
         * @throw std::out_of_range if i out of range of matrix A
         * @post access matrix vector at index i of A
         * @returns reference to accessed matrix vector at index i
         */
        MyVector<double>& operator[](const size_t i);

        /*!
         * @brief size function, returns size of member obj. matrix A
         * @pre none
         * @post gets the size of matrix A
         * @returns the size of matrix A
         */
        int size() const { return n; }

        /*!
         * @brief swap function, swaps contents of a and b
         * @pre none
         * @param[in,out] a lhs of SuccessiveOR swap
         * @param[in,out] b lhs of SuccessiveOR swap
         * @post swaps the contents of SuccessiveOR objects a and b
         */
        friend void swap(SuccessiveOR &a, SuccessiveOR &b);
};

#include "SuccessiveOR.hpp"

#endif