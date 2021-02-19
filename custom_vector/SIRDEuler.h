#ifndef SIRD_EULER_H
#define SIRD_EULER_H

#include <functional>

/*! SIRDEuler class, performs stepwise ODE solver based on give ode
 * @brief SIRDEuler class to perform numerical ODE solution based on given ode
 */
template <typename T>
class SIRDEuler
{
    private:
        std::function<T(T)> ode; // ODE function to solve, of form T func(T)
        T y; // current y value, SIRDEuler solves for y_next
        double h; // step value to use for Euler's Method

    public:
        /*! Parameterized constructor, taking ODE, initial y, and step value
         * @brief Parameterized constructor given ODE, init. y, and step value
         * @pre function c must be of form T c(T)
         * @param[in] c ODE to perform Euler's Method on
         * @param[in] y0 initial y value for Euler's Method
         * @param[in] h step size to use while perform euler's method
         * @post creates a SIRDEuler object with given values to perform method
         */
        SIRDEuler(std::function<T(T)> c, const T y0, const double h): ode(c), y(y0), h(h) {}

        /*! Evaluation operator, calculates the next y value, can use new step
         * @brief Evaluation operator to calculate next y val w/ euler's method
         * @pre none
         * @param[in] new_h custom step size value if you want a different step
         * @post performs euler's method to calculate next y value given step
         * @returns the calculated y(n+1) value using Euler's Method
         */
        T operator()(const double new_h = 0) const;
};

#include "SIRDEuler.hpp"

#endif