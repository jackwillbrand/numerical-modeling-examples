#ifndef POISSON_MATRIX_MAKER_H
#define POISSON_MATRIX_MAKER_H

#include "../containers/MyMatrix.h"
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
using std::string;

/*!
 * @brief func to examine bwm_sep matrix in order, returning the index of 'des_j'th 'B' char
 * @pre des_j must be positive, bwm_sep must contain 'des_j' 'B' values
 * @param[in] bwm_sep vector of strings to iterate through to find 'B' values
 * @param[in] des_j the specific 'B' value to search for in the string vector
 * @param[out] j_i the i index of the desired 'B' value
 * @param[out] j_j the j index of the desired 'B' value
 * @throw std::out_of_range if there are not des_j unknowns, or if des_j not positive
 * @post find i, j values of desired 'B' value, return these through reference vars
 */
void find_jth_unknown(const MyVector<string> bwm_sep, const int des_j, int &j_i, int &j_j);

/*!
 * @brief func to get distance from 'B' value to next 'B' value above/below
 * @pre first_i, first_j, sec_i must all be in range of bwm_sep matrix
 * @param[in] bwm_sep vector of strings to iterate through to find 'B' values
 * @param[in] first_i i index value of the first 'B' value
 * @param[in] first_j j index value of the first 'B' value (and second 'B' value)
 * @param[in] sec_i i index value of the second 'B' value
 * @throw std::out_of_range if first_i, first_j, sec_i out of range of bwm_sep
 * @post gets the distance between the two desired 'B' values 
 * @returns the distance between two desired 'B' values
 */
int get_unknown_dist(const MyVector<string> bwm_sep, const int first_i, const int first_j, const int sec_i);

/*!
 * @brief function to construct poisson banded matrix given input file
 * @pre bw_matrix must be a text file in root directory
 * @param[in] bw_matrix name of text file to create matrix from
 * @param[out] bwm vector of strings read in by file
 * @post construct a poisson matrix based on given text file name, returns
 *       the strings read in from file through bwm out parameter
 * @returns the constructed banded poisson matrix
 */
MyMatrix<double> calc_poisson_matrix(const string bw_matrix, MyVector<string> &bwm);

/*!
 * @brief creates poisson b vector of size rows, filled with 'val'
 * @pre rows must be a non negative value
 * @param[in] rows size of b vector
 * @param[in] val double value to fill b vector with
 * @throw std::out_of_range if rows is negative
 * @post creates a vector object of size rows, filled with value val
 * @returns the created vector object of size rows, with elements 'val'
 */
MyVector<double> calc_poisson_vector(const int rows, const double val);

/*!
 * @brief forcing function, determines values of b vector in equation Ax = b
 * @pre none
 * @param[in] x x index of matrix
 * @param[in] y y index of matrix
 * @post returns forcing func value at pos (x, y)
 * @returns forcing func value at pos (x, y)
 */
double forcing_func(const int x, const int y);
double forcing_func() { return 1; }

#include "PoissonMatrixMaker.hpp"

#endif