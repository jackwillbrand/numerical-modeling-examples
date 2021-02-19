#ifndef QUANTUM_REGISTER_H
#define QUANTUM_REGISTER_H

#include <iostream>
#include <algorithm>
#include <string>
#include <random>
#include <cstdlib>
#include <time.h>
#include "containers/MyVector.h"
#include "gates/QuantumGate.h"
using std::ostream;
using std::string;

/*! quantum register class, templated on number of qubits
 * @brief quantum register class, templated on number of qubits
 */
template <int Q>
class QuantumRegister;

/*! output operator, outputs measured state and probabilities for given qubit
 * @brief output, lists measured states and probabilities for given qubit
 * @pre none
 * @param[in,out] out ostream object to be modified, prints info to console
 * @param[in,out] qr qubit object to be printed, is measured if it hasn't already
 * @post measures qubit if necessary, then prints measured state/probs to console
 * @returns the modified ostream object 'out'
 */
template <int Q>
ostream& operator<<(ostream &out, QuantumRegister<Q> &qr);

/*! swap function, swaps contents of quantum registers a and b
 * @brief swap function, swaps contents of quantum registers a and b
 * @pre none
 * @param[in,out] a lhs of swap function, to be swapped with b
 * @param[in,out] b rhs of swap function, to be swapped with a
 * @post swaps the contents of quantum registers a and b
 */
template <int Q>
void swap(const QuantumRegister<Q> &a, const QuantumRegister<Q> &b);

/*! quantum register class, templated on number of qubits
 * @brief quantum register class, templated on number of qubits
 */
template <int Q>
class QuantumRegister
{
    private:
        MyVector<MyComplex<double>> reg; //! vector representing qubit register
        string measured_state; //! measured state, only defined after measuring
        bool can_apply_gates; //! can this register have gates applied to it

    public:
        /*! parameterized constructor, given vector of state probabilities
         * @brief parameterized constructor, given vector of state probabilities
         * @pre must be a positive amount of qubits, otherwise useless. also must
         *      have the correct vector size given specified qubit amount 'Q', also
         *      sum of state probabilities must sum to 1
         * @param[in] r vector of state possibilies for given qubits
         * @throw std::invalid_argument if amount of qubits is not positive or r
         *      is incorrect size for register of qubit size 'Q'
         * @post creates a quantum register object based on state probabilities 'r' 
         */
        explicit QuantumRegister(const MyVector<MyComplex<double>> &r);

        /*! copy constructor, copies contents of src to calling object
         * @brief copy constructor, copies contents of src to calling object
         * @pre none
         * @param[in] src QuantumRegister object to copy to calling object
         * @post creates a QuantumRegister object identical to 'src'
         */
        QuantumRegister(const QuantumRegister<Q> &src);

        /*! assignment operator, swaps contents of calling object and qr
         * @brief assignment op, swaps contents of calling object and qr
         * @pre none
         * @param[in] qr copy to qr, contents to be swapped with calling obj
         * @post swaps contents of calling object and qr
         * @returns the modified calling object after swap
         */
        QuantumRegister<Q>& operator=(QuantumRegister<Q> qr);

        /*! access operator, allows access to state probability at index 'index'
         * @brief access operator, access state prob at index 'index'
         * @pre index must be positive and within range of vector 'reg'
         * @param[in] index index of qubit register to access
         * @throw std::out_of_range if index is out of range of qubit register
         * @post access the complex number located at register at index 'index'
         * @returns the accessed complex number at index 'index'
         */
        MyComplex<double> operator[](size_t index) const;

        /*! measure function, measures and gets a measured state, or returns existing
         * @brief measures qubit via random choice, or returns existing measurement
         * @pre none
         * @post measures the state of qubits based on weighted random choice, or
         *       returns the measured state if already measured
         * @returns the measured state of the qubits
         */
        string measure();

        /*! apply gate function, applies passed gate to qubits if prerequisites hold
         * @brief apply function, apply passed gate to qubits if prerequisites hold
         * @pre the state of qubit must not already be measured (can_apply_gates must
         *      be true). the specified quantum gate must be usable for the calling
         *      object's templated qubit size 'Q'. if a control bit is given, it must
         *      be a measured 1.
         * @param[in] qg quantum gate to apply to calling object quantum register
         * @throw std::invalid_argument if qubit is already measured or given quantum
         *        gate is not compatible with quantum register of size 'Q' or control
         *        bit is not a measured 1 if applicable
         * @post apply the gate to quantum register, adjusting probabilities accordingly
         */
        void apply_gate(const QuantumGate &qg);

        /*! output operator, outputs measured state and probabilities for given qubit
         * @brief output, lists measured states and probabilities for given qubit
         * @pre none
         * @param[in,out] out ostream object to be modified, prints info to console
         * @param[in,out] qr qubit object to be printed, is measured if it hasn't already
         * @post measures qubit if necessary, then prints measured state/probs to console
         * @returns the modified ostream object 'out'
         */
        friend ostream& operator<<<Q>(ostream& out, QuantumRegister<Q> &qr);

        /*! swap function, swaps contents of quantum registers a and b
         * @brief swap function, swaps contents of quantum registers a and b
         * @pre none
         * @param[in,out] a lhs of swap function, to be swapped with b
         * @param[in,out] b rhs of swap function, to be swapped with a
         * @post swaps the contents of quantum registers a and b
         */
        friend void swap<Q>(const QuantumRegister<Q> &a, const QuantumRegister<Q> &b);
};

/*! to_binary function, converts an int 'num' to binary string
 * @brief to_binary function, converts an int 'num' to binary string
 * @pre none
 * @param[in] num integer to be converted to binary string
 * @post creates a string of binary representation of integer 'num'
 * @returns the binary string after creation 
 */
string to_binary(int num);

#include "QuantumRegister.hpp"

#endif