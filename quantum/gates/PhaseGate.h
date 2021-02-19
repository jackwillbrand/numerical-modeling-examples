#ifndef PHASE_GATE_H
#define PHASE_GATE_H

#include "QuantumGate.h"
#include "../containers/MyMatrix.h"
#include "../MyComplex.h"
using std::cout;
using std::endl;

/*! phase gate class, used to simulate phase gate function
 * @brief phase gate class, used to simulate phase gate function
 */
class PhaseGate;

/*! output operator, stream contents of phase gate to console
 * @brief output operator, stream contents of phase gate to console
 * @pre none
 * @param[in,out] out ostream object to print gate info to console
 * @param[in] hg phase gate to print to console
 * @post prints contents of phase gate, modifies out in process
 * @returns the modified ostream object 'out'
 */
ostream& operator<<(ostream& out, const PhaseGate &hg);

/*! phase gate class, used to simulate phase gate function
 * @brief phase gate class, used to simulate phase gate function
 */
class PhaseGate : public QuantumGate
{
    public:
        /*! phase gate default constructor, constructs a phase gate matrix
         * @brief phase gate default constructor, constructs phase gate matrix
         * @pre none
         * @post creates a phase gate object with respective gate matrix rep.
         */
        PhaseGate();

        /*! phase gate copy constructor, creates identical phase gate
         * @brief copy constructor, constructs identical phase gate to hg
         * @pre none
         * @param[in] hg phase gate to be copied to calling gate
         * @post creates phase gate object identical to hg
         */
        PhaseGate(const PhaseGate &hg);

        /*! phase gate operator=, sets lhs equal to phase gate hg
         * @brief operator=, sets lhs equal to phase gate 'hg' rhs
         * @pre none
         * @param[in] hg phase gate to be copied to lhs of =
         * @post sets calling object contents equal to hg contents
         * @returns the calling object after assignment
         */
        PhaseGate& operator=(const PhaseGate &hg);
};

#include "PhaseGate.hpp"

#endif