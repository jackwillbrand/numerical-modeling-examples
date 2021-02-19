#ifndef T_GATE_H
#define T_GATE_H

#include "QuantumGate.h"
#include "../containers/MyMatrix.h"
#include "../MyComplex.h"
using std::cout;
using std::endl;

/*! T gate class, used to simulate T gate function
 * @brief T gate class, used to simulate T gate function
 */
class TGate;

/*! output operator, stream contents of T gate to console
 * @brief output operator, stream contents of T gate to console
 * @pre none
 * @param[in,out] out ostream object to print gate info to console
 * @param[in] hg T gate to print to console
 * @post prints contents of T gate, modifies out in process
 * @returns the modified ostream object 'out'
 */
ostream& operator<<(ostream& out, const TGate &hg);

/*! T gate class, used to simulate T gate function
 * @brief T gate class, used to simulate T gate function
 */
class TGate : public QuantumGate
{
    public:
        /*! T gate default constructor, constructs a T gate matrix
         * @brief T gate default constructor, constructs T gate matrix
         * @pre none
         * @post creates a T gate object with respective gate matrix rep.
         */
        TGate();

        /*! T gate copy constructor, creates identical T gate
         * @brief copy constructor, constructs identical T gate to hg
         * @pre none
         * @param[in] hg T gate to be copied to calling gate
         * @post creates T gate object identical to hg
         */
        TGate(const TGate &hg);

        /*! T gate operator=, sets lhs equal to T gate hg
         * @brief operator=, sets lhs equal to T gate 'hg' rhs
         * @pre none
         * @param[in] hg T gate to be copied to lhs of =
         * @post sets calling object contents equal to hg contents
         * @returns the calling object after assignment
         */
        TGate& operator=(const TGate &hg);
};

#include "TGate.hpp"

#endif