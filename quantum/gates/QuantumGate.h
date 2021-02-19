#ifndef QUANTUM_GATE_H
#define QUANTUM_GATE_H

#include <iostream>
#include "../containers/MyMatrix.h"
#include "../containers/MyVector.h"
#include "../MyComplex.h"

/*! quantum gate abstract class, provides functionality for all child gates
 * @brief quantum gate abstract, provides functionality for all child gates,
 *        modification of quantum gate matrices are not allowed as that would
 *        create a different gate
 */
class QuantumGate
{
    protected:
        MyMatrix<MyComplex<double>> gate; //! matrix representing gate
        int req_qubit_size; //! qubit amount that given gate operates on
    
    public:
        /*! default constructor, creates a gate with size 2x2, req. qubit size of 0
         * @brief def. constructor, creates a gate with 2x2 size and qubit size of 0
         * @pre none
         * @post creates a quantum gate with size 2x2 and req. qubit size of 0
         */
        QuantumGate(): gate(MyMatrix<MyComplex<double>>(2, 2)), req_qubit_size(1) {}

        /*! virtual operator[], returns quantum gate's matrix
         * @brief virtual operator[], returns quantum gate's matrix
         * @pre none
         * @post accesses the vector inside matrix 'gate' at index 'i'
         * @returns the given quantum gate object's matrix
         */
        virtual MyMatrix<MyComplex<double>> get_gate() const { return gate; }

        /*! gets required qubit size comptabile with given gate
         * @brief gets required qubit size compatible with given gate
         * @pre none
         * @post gets the required qubit size compatible with given gate
         * @returns the required gubit size compatible with given gate
         */
        int get_req_qubit_size() const { return req_qubit_size; }
};

#endif