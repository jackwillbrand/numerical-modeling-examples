#ifndef PAULI_X_GATE_H
#define PAULI_X_GATE_H

#include "QuantumGate.h"
#include "../containers/MyMatrix.h"
#include "../MyComplex.h"
using std::cout;
using std::endl;

/*! pauli x gate class, used to simulate pauli x gate function
 * @brief pauli x gate class, used to simulate pauli x gate function
 */
class PauliXGate;

/*! output operator, stream contents of pauli x gate to console
 * @brief output operator, stream contents of pauli x gate to console
 * @pre none
 * @param[in,out] out ostream object to print gate info to console
 * @param[in] hg pauli x gate to print to console
 * @post prints contents of pauli x gate, modifies out in process
 * @returns the modified ostream object 'out'
 */
ostream& operator<<(ostream& out, const PauliXGate &hg);

/*! pauli x gate class, used to simulate pauli x gate function
 * @brief pauli x gate class, used to simulate pauli x gate function
 */
class PauliXGate : public QuantumGate
{
    public:
        /*! pauli x gate default constructor, constructs a pauli x gate matrix
         * @brief pauli x gate default constructor, constructs pauli x gate matrix
         * @pre none
         * @post creates a pauli x gate object with respective gate matrix rep.
         */
        PauliXGate();

        /*! pauli x gate copy constructor, creates identical pauli x gate
         * @brief copy constructor, constructs identical pauli x gate to hg
         * @pre none
         * @param[in] hg pauli x gate to be copied to calling gate
         * @post creates pauli x gate object identical to hg
         */
        PauliXGate(const PauliXGate &hg);

        /*! pauli x gate operator=, sets lhs equal to pauli x gate hg
         * @brief operator=, sets lhs equal to pauli x gate 'hg' rhs
         * @pre none
         * @param[in] hg pauli x gate to be copied to lhs of =
         * @post sets calling object contents equal to hg contents
         * @returns the calling object after assignment
         */
        PauliXGate& operator=(const PauliXGate &hg);
};

#include "PauliXGate.hpp"

#endif