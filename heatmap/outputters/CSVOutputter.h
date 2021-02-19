#ifndef CSV_OUTPUTTER_H
#define CSV_OUTPUTTER_H

#include <fstream>
#include "../containers/MyVector.h"
using std::string;

class CSVOutputter;

/*!
 * @brief extraction operator, output ordered solution in csvo
 * @pre csvo must contained an ordered solution vector
 * @param[in,out] out ostream object to print with
 * @param[in] csvo csvoutputter object containing ordered solution vect
 * @throw std::invalid_argument if csvo doesn't contain ordered solution
 * @post output the ordered solution vector inside of csvo
 * @returns the modified ostream var. after printing
 */
ostream& operator<<(ostream &out, const CSVOutputter &csvo);

/*!
 * @brief swap function, swaps contents of csvoutputter obj. a and b
 * @pre none
 * @param[in] a lhs of swap function, swap contents with b
 * @param[in] b rhs of swap function, swap contents with a
 * @post swaps contents of a and b
 */
void swap(CSVOutputter &a, CSVOutputter &b);

class CSVOutputter
{
    private:
        MyVector<double> solution; //! double sol. vector obtained from Chol/SOR method
        MyVector<string> bwm_sep; //! string vector representing black/white txt file
        int n; //! size of solution vector, aka number of unknowns solved
        MyVector<string> ordered_sol; //! ordered solution vector, read to write to csv
        bool is_ordered; // if solution has been ordered, this is true, otherwise false
    
    public:
        /*!
         * @brief default constructor, init empty vectors of size zero
         * @pre none
         * @post creates empty csvoutputter with vectors of size zero
         */
        CSVOutputter(): solution(MyVector<double>()), bwm_sep(MyVector<string>()), n(0),
            ordered_sol(MyVector<string>()), is_ordered(false) {}

        /*!
         * @brief param. constructor, given b/w txt matrix, solution vect, num (size of vect)
         * @pre s must be a vector of size num
         * @param[in] bw string vector, containing contents of b/w text file
         * @param[in] solution vector obtained via Chol/SOR method
         * @param[in] num size of s, amount of unknowns previously solved
         * @throw std::invalid_argument if s.size() != num
         * @post creates a csvoutputter object given relevent parameters
         */
        CSVOutputter(const MyVector<string> &bw, const MyVector<double> &s, const int num);

        /*!
         * @brief copy constructor, creates csvoutputter object identical to csvo
         * @pre none
         * @param[in] csvo existing csvoutputter object to copy
         * @post creates csvoutputter object identical to csvo
         */
        CSVOutputter(const CSVOutputter &csvo);

        /*!
         * @brief assignment operator, sets calling object equal to csvo
         * @pre none
         * @param[in] csvo existing csvoutputter object to copy to calling object
         * @post sets calling object equal to csvo
         * @returns a reference to modified calling object
         */
        CSVOutputter& operator=(CSVOutputter csvo);

        /*!
         * @brief eval. operator, calculates the ordered solution vector given the b/w text
         *        file matrix and the solution obtained from Chol/SOR methods
         * @pre none
         * @post finds the ordered solution vector, given b/w text file and solution vect
         * @returns a reference to the ordered solution vector
         */
        MyVector<string>& operator()();

        /*!
         * @brief reset function, recreates calling object with new b/w text vector, 
         *        solution vector, and vector size
         * @pre s must be of size num
         * @param[in] bw string vector, containing contents of b/w text file
         * @param[in] solution vector obtained via Chol/SOR method
         * @param[in] num size of s, amount of unknowns previously solved
         * @throw std::invalid_argument if num != s.size()
         * @post create calling object with new bw, s, num
         */
        void reset(const MyVector<string> &bw, const MyVector<double> &s, const int num);

        /*!
         * @brief output function, outputs contents of ordered sol. to csv file
         * @pre csvoutputter sol. vect. must have been previously ordered
         * @param[in] out_file name of the path to create csv file under
         * @throw std::invalid_argument if sol. vect. has not been ordered
         * @post creates a csv file containing ordered sol. vect.
         */
        void output_to_file(const string out_file) const;

        /*!
         * @brief swap function, swaps contents of csvoutputter obj. a and b
         * @pre none
         * @param[in] a lhs of swap function, swap contents with b
         * @param[in] b rhs of swap function, swap contents with a
         * @post swaps contents of a and b
         */
        friend void swap(CSVOutputter &a, CSVOutputter &b);

        /*!
         * @brief extraction operator, output ordered solution in csvo
         * @pre csvo must contained an ordered solution vector
         * @param[in,out] out ostream object to print with
         * @param[in] csvo csvoutputter object containing ordered solution vect
         * @throw std::invalid_argument if csvo doesn't contain ordered solution
         * @post output the ordered solution vector inside of csvo
         * @returns the modified ostream var. after printing
         */
        friend ostream& operator<<(ostream &out, const CSVOutputter &csvo);
};

#include "CSVOutputter.hpp"

#endif