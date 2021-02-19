#ifndef GI_RUNGE_KUTTA_H
#define GI_RUNGE_KUTTA_H

#include <functional>

template <typename T>
class GIRungeKutta;

/*! Swap function, swaps the contents of objects a and b
 * @brief Swap function to swap member variable contents of a and b
 * @pre template type T must support swap
 * @param[in,out] a GIRungeKutta obj, left hand side of swap function
 * @param[in,out] b GIRungeKutta obj, right hand side of swap function
 */
template <typename T>
void swap(GIRungeKutta<T> &a, GIRungeKutta<T> &b);

/*! GIRungeKutta class, performs stepwise ODE solver based on give ode
 * @brief GIRungeKutta class to perform num. ODE solution based on given ode
 */
template <typename T>
class GIRungeKutta
{
    private:
        std::function<T(T)> ode; // ODE function to solve, of form T func(T)
        T y; // current y value, GIRungeKutta solves for y_next
        T y_pred; // predictor value of y, Heun's method uses it to calculate y
        double h; // step value to use for Runge-Kutta's Method

    public:
        /*! Parameterized constructor, taking ODE, initial y, and step value
         * @brief Parameterized constructor given ODE, init. y, and step value
         * @pre function c must be of form T c(T)
         * @param[in] c ODE to perform Runge-Kutta on
         * @param[in] y0 initial y value for Runge-Kutta's Method
         * @param[in] h step size to use while perform Runge-Kutta's method
         * @post creates a GIRungeKutta object with given values for method
         */
        GIRungeKutta(std::function<T(T)> &c, const T y0, const double h): 
            ode(c), y(y0), h(h) {}
        
        /*! Copy constructor, copies contents of girk to calling obj
         * @brief Copy constructor to copy contents of girk to calling obj
         * @pre template type T must support assignment operator
         * @param[in] girk GIRungeKutta object to be copied by calling obj
         * @post creates a GIRungeKutta obj identical to girk param
         */
        GIRungeKutta(const GIRungeKutta<T> &girk);

        /*! Assignment operator, returns calling obj after swap contents w/ src
         * @brief = operator to return calling obj after swap contents w/ src
         * @pre template type T must support assignment operator
         * @param[in] src GIRungeKutta object for calling obj to swap contents
         * @post swaps the contents of the calling object and src object
         * @returns the modified calling object after swap performed
         */
        GIRungeKutta<T>& operator=(GIRungeKutta<T> src);

        /*! Evaluation operator, calculates the next y value, can use new step
         * @brief Eval operator to calculate next y val w/ Runge-Kutta's method
         * @pre new_h must be nonnegative (no going back in time)
         * @param[in] new_h custom step size value if you want a different step
         * @throw std::invalid_argument if new_h <= 0
         * @post performs Runge-Kutta's method to calculate next y value
         * @returns the calculated y(n+1) value using Runge-Kutta method
         */
        T operator()(const double new_h = 0);

        /*! Swap function, swaps the contents of objects a and b
         * @brief Swap function to swap member variable contents of a and b
         * @pre template type T must support swap
         * @param[in,out] a GIRungeKutta obj, left hand side of swap function
         * @param[in,out] b GIRungeKutta obj, right hand side of swap function
         */
        friend void swap<T>(GIRungeKutta<T> &a, GIRungeKutta<T> &b);
};

#include "GIRungeKutta.hpp"

#endif