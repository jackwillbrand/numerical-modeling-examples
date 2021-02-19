#ifndef PAULI_Z_GATE_H
#define PAULI_Z_GATE_H

#include "QuantumGate.h"
#include "../containers/MyMatrix.h"
#include "../MyComplex.h"
using std::cout;
using std::endl;

/*! pauli z gate class, used to simulate pauli z gate function
 * @brief pauli z gate class, used to simulate pauli z gate function
 */
class PauliZGate;

/*! output operator, stream contents of pauli z gate to console
 * @brief output operator, stream contents of pauli z gate to console
 * @pre none
 * @param[in,out] out ostream object to print gate info to console
 * @param[in] hg pauli z gate to print to console
 * @post prints contents of pauli z gate, modifies out in process
 * @returns the modified ostream object 'out'
 */
ostream& operator<<(ostream& out, const PauliZGate &hg);

/*! pauli z gate class, used to simulate pauli z gate function
 * @brief pauli z gate class, used to simulate pauli z gate function
 */
class PauliZGate : public QuantumGate
{
    public:
        /*! pauli z gate default constructor, constructs a pauli z gate matrix
         * @brief pauli z gate default constructor, constructs pauli z gate matrix
         * @pre none
         * @post creates a pauli z gate object with respective gate matrix rep.
         */
        PauliZGate();

        /*! pauli z gate copy constructor, creates identical pauli z gate
         * @brief copy constructor, constructs identical pauli z gate to hg
         * @pre none
         * @param[in] hg pauli z gate to be copied to calling gate
         * @post creates pauli z gate object identical to hg
         */
        PauliZGate(const PauliZGate &hg);

        /*! pauli z gate operator=, sets lhs equal to pauli z gate hg
         * @brief operator=, sets lhs equal to pauli z gate 'hg' rhs
         * @pre none
         * @param[in] hg pauli z gate to be copied to lhs of =
         * @post sets calling object contents equal to hg contents
         * @returns the calling object after assignment
         */
        PauliZGate& operator=(const PauliZGate &hg);
};

#include "PauliZGate.hpp"

#endif