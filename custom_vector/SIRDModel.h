#ifndef SIRD_MODEL_H
#define SIRD_MODEL_H

#include <iostream>
#include "SIRDVector.h"
#include "SIRDEuler.h"
using std::ostream;

class SIRDModel;

/*! Insertion operator, prints contents of model to screen
* @brief Insertion operator, prints contents of model to screen
* @pre none
* @param[in,out] out ostream object to print with and modify
* @param[in] src SIRDModel object to print out to console
* @post prints contents of src to the console
* @returns the modified ostream object 'out'
*/
ostream& operator<<(ostream &out, const SIRDModel &src);

/*! SIRDModel class, performs simulation of disease spread
 * @brief SIRDModel class, performs the simulation of a disease
 *        spreading through the population, give an infection rate,
 *        a recovery/death rate, a population and an initial infection rate
 */
class SIRDModel
{
    private:
        double infected; //! total amount of infected at this time
        double susceptible; // ! total amount of susceptible at this time
        double recovered; //! total amount of recovered people at this time
        double dead; //! total deceased at this point in simulation

        double total_pop; //! the total population, s+i+r+d = total_pop
        double step; //! the jump between each run of simulation in days

        SIRDVector<double> coeff; //! vector of coefficients for disease info

    public:
        /*! Constructor, given total pop., initial infected, step size, coeff.
         * @brief Constructor given population numbers, step size, constants
         * @pre p0 and i0 must be nonnegative, vector must be size 3 [b, v, d]
         * @param[in] p0 total population for simulation
         * @param[in] i0 total infected at start of simulation
         * @param[in] h step size to use for euler's ODE method
         * @param[in] c vector containing constants to solve ODEs
         * @throw std::invalid_argument if p0 is negative
         * @throw std::invalid_argument if i0 is negative
         * @throw std::invalid_argument if c not of size 3
         * @post creates a SIRDModel object given initial parameters
         */
        SIRDModel(const double p0, const double i0, const double h, 
            const SIRDVector<double> c);
        
        /*! Function evaluation operator, step model at next moment in time
         * @brief Evaluation operator to step to next moment in simulation
         * @pre none
         * @post step the model to next moment and update member variables
         */
        void operator()();

        /*! Insertion operator, prints contents of model to screen
         * @brief Insertion operator, prints contents of model to screen
         * @pre none
         * @param[in,out] out ostream object to print with and modify
         * @param[in] src SIRDModel object to print out to console
         * @post prints contents of src to the console
         * @returns the modified ostream object 'out'
         */
        friend ostream& operator<<(ostream &out, const SIRDModel &src);
};

#include "SIRDModel.hpp"

#endif