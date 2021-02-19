#ifndef MY_COMPLEX_H
#define MY_COMPLEX_H

#include <iostream>
#include <algorithm>
#include <cmath>
using std::ostream;

/*! complex number class implementation
 * @brief complex number class implementation
 */
template <typename T>
class MyComplex;

/*! extraction operator, outputs contents of src to console
 * @brief extraction operator, outputs contents of src to console
 * @pre none
 * @param[in,out] out ostream object to output with
 * @param[in] src complex object to be outputted to console
 * @post outputs the contents of src to the console
 * @returns the modified ostream object
 */
template <typename T>
ostream& operator<<(ostream &out, const MyComplex<T> &src);

/*! swap function, swaps contents of c1 and c2
 * @brief swap function, swaps contents of c1 and c2
 * @pre none
 * @param[in,out] c1 complex object, lhs of the swap function
 * @param[in,out] c2 complex object, rhs of the swap function
 * @post swaps the contents of c1 and c2
 */
template <typename T>
void swap(MyComplex<T> &c1, MyComplex<T> &c2);

/*! complex addition, adds complex a and b and returns new complex
 * @brief complex addition, adds complex a and b and returns new complex
 * @pre type T must be capable of addition
 * @param[in] a complex object, lhs of addition operator
 * @param[in] b complex object, rhs of addition operator
 * @post add the contents of a and b to a new complex
 * @returns the new complex after all addition completed
 */
template <typename T>
MyComplex<T> operator+(const MyComplex<T> &a, const MyComplex<T> &b);

/*! complex subtraction, minus complex a and b and returns new complex
 * @brief complex subtraction, minus complex a and b and returns new complex
 * @pre type T must be capable of subtraction
 * @param[in] a complex object, lhs of subtraction operator
 * @param[in] b complex object, rhs of subtraction operator
 * @post subtract the contents of a and b to a new complex
 * @returns the new complex after all subtraction completed
 */
template <typename T>
MyComplex<T> operator-(const MyComplex<T> &a, const MyComplex<T> &b);

/*! complex multiplication, multiply complex a and b and return new complex
 * @brief complex multiplication, multiply complex a and b and return new complex
 * @pre type T must be capable of subtraction, addition, multiplication
 * @param[in] a complex object, lhs of multiplication operator
 * @param[in] b complex object, rhs of multiplication operator
 * @post multiply the contents of a and b to a new complex
 * @returns the new complex after all multiplication completed
 */
template <typename T>
MyComplex<T> operator*(const MyComplex<T> &a, const MyComplex<T> &b);

/*! complex number class implementation
 * @brief complex number class implementation
 */
template <typename T>
class MyComplex
{
    private:
        T a; //! real component of complex number
        T b; //! imaginary component of complex number

    public:
        MyComplex(): a(0), b(0) {}

        /*! parameterized constructor, given real/imag component
         * @brief parameterized constructor, given real/imag component
         * @pre none
         * @param[in] r real component of complex number
         * @param[in] i imaginary component of complex number
         * @post creates a complex object of form ('r' + 'i'i)
         */
        MyComplex(const T r, const T i);

        /*! copy constructor, given an existing complex 'c'
         * @brief copy constructor, given an existing complex number 'c'
         * @pre none
         * @param[in] c complex object to be copied to calling object
         * @post creates a complex object copied from 'c'
         */
        MyComplex(const MyComplex<T> &c);

        /*! assignment operator, returns calling obj after swapped with 'c'
         * @brief assign operator, return calling obj after swap with 'c'
         * @pre none
         * @param[in] c complex objec to be copied to calling object
         * @returns the new equivalent complex object
         */
        MyComplex<T>& operator=(MyComplex<T> c);

        /*! real function, returns real component of complex object
         * @brief real function, return real component of complex object
         * @pre none
         * @post returns the real component of calling complex object
         * @returns the real component of calling complex object
         */
        T real() const { return a; }

        /*! imag function, returns imag component of complex object
         * @brief imag function, return imag component of complex object
         * @pre none
         * @post returns the imag component of calling complex object
         * @returns the imag component of calling complex object
         */
        T imag() const { return b; }

        /*! unary minus, returns additive inverse of real component
         * @brief unary minus, return additive inverse of real component
         * @pre type T must be capable of inversion
         * @post calculates the additive inverse of real component
         * @returns additive inverse of real component of complex
         */
        MyComplex<T>& operator-() const;

        /*! unary !, returns the complex conjugate
         * @brief unary !, returns the complex conjugate
         * @pre type T must be capable of inversion
         * @post calculates the complex conjugate
         * @returns the calculated complex conjugate
         */
        MyComplex<T>& operator!() const;
        
        /*! unary ~, returns the magnitude of complex number
         * @brief unary ~, returns magnitude of complex number
         * @pre type T must be capable of multiplication
         * @post calculates the magnitude of complex number (rep. as vector)
         * @returns the calculated magnitude of complex number
         */
        T operator~() const;

        /*! swap function, swaps contents of a and b
         * @brief swap function, swaps contents of a and b
         * @pre none
         * @param[in,out] a complex object, lhs of the swap function
         * @param[in,out] b complex object, rhs of the swap function
         * @post swaps the contents of a and b
         */
        friend void swap<T>(MyComplex<T> &c1, MyComplex<T> &c2);

        /*! extraction operator, outputs contents of src to console
         * @brief extraction operator, outputs contents of src to console
         * @pre none
         * @param[in,out] out ostream object to output with
         * @param[in] src complex object to be outputted to console
         * @post outputs the contents of src to the console
         * @returns the modified ostream object
         */
        friend ostream& operator<<<T>(ostream &out, const MyComplex<T> &src);
};

#include "MyComplex.hpp"

#endif