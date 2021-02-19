#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include "GIVector.h"
#include "GITimeModel.h"
#include <algorithm>
#include <iostream>
#include <cmath>

/*! PID controller class
 * @brief class object to calculate the next u_g and u_i values by
 *        performing numerical integration/differentiation and the error
 *        values calculated
 */
class PIDController;

/*! Swap function, swaps contents of a and b
 * @brief Swap function to swap member contents of a and b
 * @pre none
 * @param[in] a left hand side of swap function to flip
 * @param[in] b right hand side of swap function to flip
 * @post swap the inner contents of a and b with each other
 */
void swap(PIDController &a, PIDController &b);

/*! PID controller class
 * @brief class object to calculate the next u_g and u_i values by
 *        performing numerical integration/differentiation and the error
 *        values calculated
 */
class PIDController
{
    private:
        GIVector<double> u_values; //! current u_g and u_i values
        GIVector<double> k; //! values of K constants for controller

        double desired_glucose_conc; //! desired glucose level to meet
        double curr_error; //! error of most current iteration
        double initial_error; //! initial error of simulation

    public:
        /*! Parameterized constructor, taking k const vect and desired g level
         * @brief create obj with given k consts and desired glucose level
         * @pre g, i must be nonnegative and k must be of size 3
         * @param[in] k vector of k constants to use for controller integral
         * @param[in] g the desired glucose level our simulation aims for
         * @param[in] i the initial glucose level to begin simulation
         * @throw std::invalid_argument if g<0, i<0, or k.size() != 3
         * @post creates new object with corresponding k and target glucose
         */
        PIDController(const GIVector<double> &ki, const double g, 
            const double i);

        /*! Copy constructor, creates identical object to src
         * @brief Copy constructor, creates identical object to src obj
         * @pre none
         * @param[in] src a PIDController object to copy to calling obj
         * @post creates new object identical to PIDController obj 'src'
         */
        PIDController(const PIDController &src);

        /*! Assignment operator, copies contents of src to calling obj
         * @brief Assignment op to copy contents of src to calling obj
         * @pre none
         * @param[in] src a copy of parameter for calling obj to copy
         * @post swaps the contents of calling obj and src object
         * @returns the calling object after all swaps are performed
         */
        PIDController& operator=(PIDController src);

        /*! Evaluation operator, steps the controller to calc. control signal
         * @brief step the controller, calculate new u values and adjust
         * @pre step and g must be nonnegative
         * @param[in] g current glucose level for error calculations
         * @param[in] step the step controller moves in time per unit
         * @throw std::invalid_argument if step or g is negative
         * @post step controller, calculate and adjust new u_values
         */
        void operator()(const double g, const double step);

        /*! Function to return the u_values inside PIDController
         * @brief returns the vector u_values in calling object
         * @pre none
         * @post returns the vector u_values in the calling object
         * @returns u_values inside the calling object
         */
        GIVector<double> get_u_vals() const { return u_values; } 

        /*! Subscript operator, returns contents of k vector at index i
         * @brief returns contents of k vector at index i
         * @pre i must be in range 0 <= i < k_consts.size()
         * @param[in] i the index of k_consts to access
         * @throw std::out_of_range if i not in [0, k_consts.size())
         * @post access the value of k_consts[i]
         * @returns the value of k_consts[i]
         */
        double operator[](const size_t i) const;

        /*! Subscript operator, returns reference to k vector at index i
         * @brief returns reference to contents of k vector at index i
         * @pre i must be in range 0 <= i < k_consts.size()
         * @param[in] i the index of k_consts to access
         * @throw std::out_of_range if i not in [0, k_consts.size())
         * @post access the value of k_consts[i]
         * @returns a reference to value of k_consts[i]
         */
        double& operator[](const size_t i);

        /*! reset function, allows adjustment of desired glucose level
         * @brief changes the desired glucose level to new_desired_glucose
         * @pre new_desired_glucose must be a nonnegative number
         * @param[in] new_desired_glucose new value to target for glucose
         * @throw std::invalid_argument if new_des_glucose is negative
         * @post sets the desired glucose level to new_desired_glucose
         */
        void reset(const double new_desired_glucose);

        /*! Swap function, swaps contents of a and b
         * @brief Swap function to swap member contents of a and b
         * @pre none
         * @param[in] a left hand side of swap function to flip
         * @param[in] b right hand side of swap function to flip
         * @post swap the inner contents of a and b with each other
         */
        friend void swap(PIDController &a, PIDController &b);
};

#endif