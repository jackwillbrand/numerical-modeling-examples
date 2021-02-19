#ifndef SIRD_VECTOR_H
#define SIRD_VECTOR_H

#include <iostream>
#include <algorithm>
#include <iterator>
#include "SIRDIterator.h"

using std::ostream;
using std::istream;

template <typename T>
class SIRDVector;

/*! Overloaded output, output contents of SIRDVector
 * @brief output operator to output contents of SIRDVector to console
 * @pre type T must be capable of outputting to console
 * @param[in,out] out ostream object to perform outputting with
 * @param[in] src SIRDVector to be outputted to the console
 * @post outputs the contents of src to the console
 * @returns the modified ostream object
 */
template <typename T>
ostream& operator<<(ostream &out, const SIRDVector<T> &src);

/*! Overloaded insertion, fill contents of SIRDVector with input
 * @brief insertion operator to fill contents of SIRDVector with input
 * @pre cin must be called 'm_size' times to fill each vector element
 * @param[in,out] out ostream object to perform outputting with
 * @param[in] src SIRDVector to be outputted to the console
 * @post outputs the contents of src to the console
 * @returns the modified ostream object
 */
template <typename T>
istream& operator>>(istream &in, SIRDVector<T> &src);

/*! swap function, swaps contents of a and b vector with each other
 * @brief swap function, swaps contents of a and b with each other
 * @pre a and b must be vectors of the same size
 * @param[in,out] a vector object to be switched with 'b'
 * @param[in,out] b vector object to be switched with 'a'
 * @throw std::invalid_argument if a.m_size != b.m_size
 * @post swaps the contents of SIRDVector 'a' and 'b'
 */
template <typename T>
void swap(SIRDVector<T> &a, SIRDVector<T> &b);

/*! addition operator, for all element add by a's corresponding element
 * @brief addition, for all elements add by a's corresponding element
 * @pre a must be of same size as b, T must support addition
 * @param[in] a vector of same size as b to add with
 * @param[in] b vector of same size as a to add with
 * @throw std::invalid_argument if a is not same size as b
 * @post for each element in both vectors, a.m_data[i] + b.m_data[i]
 * @returns the new SIRDVector after all addition is completed
 */
template <typename T>
SIRDVector<T> operator+(const SIRDVector<T> &a, const SIRDVector<T> &b);

/*! subtract operator, for all element minus by a's corresponding element
 * @brief subtraction, for all elements minus by a's corresponding element
 * @pre a must be of same size as b, T must support subtraction
 * @param[in] a vector of same size as b to subtract with
 * @param[in] b vector of same size as a to subtract with
 * @throw std::invalid_argument if a is not same size as b
 * @post for each element in both vectors, a.m_data[i] - b.m_data[i]
 * @returns the new SIRDVector after all subtraction is completed
 */
template <typename T>
SIRDVector<T> operator-(const SIRDVector<T> &a, const SIRDVector<T> &b);

/*! multiplication operator, multiply all elements of lhs by rhs
 * @brief scalar mult., multiply all elements of lhs by rhs
 * @pre T must be of type that supports multiplication
 * @param[in] lhs a SIRDVector object w/ elements to be multiplied
 * @param[in] rhs a scalar value of type T to multiply with
 * @post multiplies all elements of lhs by a scalar rhs
 * @returns new SIRDVector after multiplication performed
 */
template <typename T>
SIRDVector<T> operator*(const SIRDVector<T> &lhs, const T &rhs);

/*! multiplication operator, multiply all elements of lhs by rhs
 * @brief scalar mult., multiply all elements of lhs by rhs
 * @pre T must be of type that supports multiplication
 * @param[in] lhs a SIRDVector object w/ elements to be multiplied
 * @param[in] rhs a scalar value of type T to multiply with
 * @post multiplies all elements of lhs by a scalar rhs
 * @returns new SIRDVector after multiplication performed
 */
template <typename T>
SIRDVector<T> operator*(const T lhs, const SIRDVector<T> &rhs);

/*! dot product operator, compute dot product of lhs and rhs
 * @brief dot product, computes dot product of lhs and rhs
 * @pre lhs must be of same size as rhs, T must support multiplication
 * @param[in] lhs a SIRDVector to compute dot product with
 * @param[in] rhs a SIRDVector to compute dot product with
 * @post adds product of all corresponding elements and returns num
 * @returns the dot product of lhs and rhs
 */
template <typename T>
T operator*(const SIRDVector<T> &lhs, const SIRDVector<T> &rhs);

/*! SIRDVector class
 * @brief vector implementation to track the SIR(D) representing the spread
 *        of infectious diseases through a population
 */
template <typename T>
class SIRDVector
{

    private:
        T *m_data; //! dynamic array of size 'm_size' holding vector contents
        size_t m_size; //! size_t variable representing size of m_data

    public:
        /*! Default constructor, defaults to 0 vector with m_size 0
         * @brief Default constructor making zero vector with size of 0
         * @pre none
         * @post creates vector object with size 0
         */
        SIRDVector(): m_data(nullptr), m_size(0) {}

        /*! Parameterized constructor, given initializer_list 'l'
         * @brief Parameterized constructor given initializer_list 'l'
         * @pre none
         * @param[in] l initializer list of T elements to copy to vector
         * @post creates a SIRDVector obj with dynamic array of 'l' elements
         */
        explicit SIRDVector(const std::initializer_list<T> l);

        /*! Parameterized constructor, given size of SIRDVector 'space'
         * @brief Parameterized constructor, given size of vector 'space'
         * @pre space must be positive
         * @param[in] space size_t representing size of SIRDVector storage
         * @throw std::invalid_argument if space < 0
         * @post creates a SIRDVector object with storage size 'space'
         */
        explicit SIRDVector(const size_t space);

        /*! Parameterized constructor, given arr of values of size n
         * @brief Parameterized constructor, given arr of values of size n
         * @pre none
         * @param[in] arr array of values to copy to SIRDVector
         * @param[in] n value to initialize as size of SIRDVector
         * @post creates a SIRDVector object with values of arr and equal size
         */
        SIRDVector(const T *arr, const size_t n);

        /*! Destructor, clears memory allocated to internal array
         * @brief Destructor, clears memory allocated to internal array
         * @pre none
         * @post clears and deletes pointer to internal dynamic array
         */
        ~SIRDVector();

        /*! Copy constructor
         * @brief Copy constructor, creates identical SIRDVector object to src
         * @pre none
         * @param[in] src the object to be copied to calling object
         * @post creates SIRDVector with copy of src's m_data and m_size values
         */
        SIRDVector(const SIRDVector<T> &src);

        /*! Assignment operator, returns SIRDVector equal to given src
         * @brief Assignment operator, returns SIRDVector object equal to src
         * @pre none
         * @param[in] src copy of src vector to swap contents with to new obj
         * @post swaps contents of calling object and src
         * @returns the modified calling object, contains contents of src
         */
        SIRDVector<T>& operator=(SIRDVector<T> src);

        /*! Resize function, changes SIRDVector size to new_size
         * @brief Resize function, changes SIRDVector size to new_size
         * @pre new_size must be positive
         * @param[in] new_size size_t representing new dyn. array size
         * @throw std::invalid_argument if size_t < 0
         * @post modifies SIRDVector so dyn. array is resized and m_size set
         */
        void resize(const size_t new_size);

        /*! Size function, returns the size of the SIRDVector storage
         * @brief Size function, returns size of SIRDVector storage
         * @pre none
         * @post returns the size of SIRDVector
         * @returns the size of SIRDVector
         */
        size_t size() const;

        /*! Subscript operator, returns val of m_data at index i
         * @brief Subscript operator, returns val of m_data at index i
         * @pre i must be in range 0 <= i < m_size
         * @param[in] i size_t representing index to pull from m_data
         * @throw std::out_of_range if i < 0 or i >= m_size
         * @post returns the value of m_data[i]
         * @returns the value of m_data[i]
         */
        T operator[](const size_t i) const;

        /*! apply function, returns new SIRD with func applied to all elements
         * @brief apply function, returns new SIRD with func on each element
         * @pre function must be of form func(T) with return type T
         * @param[in] func function of form func(T) with return type T
         * @post applies func() to all elements in m_data, return modified obj
         * @returns the modified vector with func() applied to all elements
         */
        SIRDVector<T>& apply(T(*func)(T));

        /*! unary minus operator, makes all elements in SIRDVector negative
         * @brief unary minus, for all elements in vector, change to inverse
         * @pre none
         * @post for each element in vector, change each to inverse
         * @returns a modified vector with each element inverted
         */
        SIRDVector<T>& operator-();

        /*! begin() function, returns iter at beginning of m_data
         * @brief begin() function, returns iter at beginning of m_data
         * @pre none
         * @post returns an iterator to beginning of m_data
         * @returns an iterator to beginning of m_data
         */
        SIRDIterator<T> begin() const { return SIRDIterator<T>(m_data); }
        
        /*! end() function, returns iter at end of m_data
         * @brief end() function, returns iter at end of m_data
         * @pre none
         * @post returns an iterator to end of m_data
         * @returns an iterator to end of m_data
         */
        SIRDIterator<T> end() const { return SIRDIterator<T>(m_data + unsigned(m_size)); }

        /*! Overloaded insertion, fill contents of SIRDVector with input
         * @brief insertion operator to fill contents of SIRDVector with input
         * @pre cin must be called 'm_size' times to fill each vector element
         * @param[in,out] out ostream object to perform outputting with
         * @param[in] src SIRDVector to be outputted to the console
         * @post outputs the contents of src to the console
         * @returns the modified ostream object
         */
         friend istream& operator>><T>(istream &in, SIRDVector<T> &src);

        /*! swap function, swaps contents of a and b vector with each other
         * @brief swap function, swaps contents of a and b with each other
         * @pre a and b must be vectors of the same size
         * @param[in,out] a vector object to be switched with 'b'
         * @param[in,out] b vector object to be switched with 'a'
         * @throw std::invalid_argument if a.m_size != b.m_size
         * @post swaps the contents of SIRDVector 'a' and 'b'
         */
        friend void swap<T>(SIRDVector<T> &a, SIRDVector<T> &b);
};

#include "SIRDVector.hpp"

#endif