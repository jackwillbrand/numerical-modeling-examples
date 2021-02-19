#ifndef HADAMARD_GATE_H
#define HADAMARD_GATE_H

#include "QuantumGate.h"
#include "../containers/MyMatrix.h"
#include "../MyComplex.h"
using std::cout;
using std::endl;

/*! hadamard gate class, used to simulate hadamard gate function
 * @brief hadamard gate class, used to simulate hadamard gate function
 */
class HadamardGate;

/*! output operator, stream contents of hadamard gate to console
 * @brief output operator, stream contents of hadamard gate to console
 * @pre none
 * @param[in,out] out ostream object to print gate info to console
 * @param[in] hg hadamard gate to print to console
 * @post prints contents of hadamard gate, modifies out in process
 * @returns the modified ostream object 'out'
 */
ostream& operator<<(ostream& out, const HadamardGate &hg);

/*! hadamard gate class, used to simulate hadamard gate function
 * @brief hadamard gate class, used to simulate hadamard gate function
 */
class HadamardGate : public QuantumGate
{
    public:
        /*! hadamard gate default constructor, constructs a hadamard gate matrix
         * @brief hadamard gate default constructor, constructs hadamard gate matrix
         * @pre none
         * @post creates a hadamard gate object with respective gate matrix rep.
         */
        HadamardGate();

        /*! hadamard gate copy constructor, creates identical hadamard gate
         * @brief copy constructor, constructs identical hadamard gate to hg
         * @pre none
         * @param[in] hg hadamard gate to be copied to calling gate
         * @post creates hadamard gate object identical to hg
         */
        HadamardGate(const HadamardGate &hg);

        /*! hadamard gate operator=, sets lhs equal to hadamard gate hg
         * @brief operator=, sets lhs equal to hadamard gate 'hg' rhs
         * @pre none
         * @param[in] hg hadamard gate to be copied to lhs of =
         * @post sets calling object contents equal to hg contents
         * @returns the calling object after assignment
         */
        HadamardGate& operator=(const HadamardGate &hg);
};

#include "HadamardGate.hpp"

#endif