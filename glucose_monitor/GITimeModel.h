#ifndef GI_TIME_MODEL_H
#define GI_TIME_MODEL_H

#include "GIVector.h"
#include "GIRungeKutta.h"
#include <algorithm>
#include <functional>
using std::ostream;

/*! GITimeModel class
 * @brief GITimeModel class, performs the bulk of the overview of managing
 *        the glucose and insulin level simulation, gets fed external glucose
 *        and insulin consumption from PIDController and prints new glucose
 *        and insulin concentrations in the bloodstream to the console
 */
class GITimeModel;

/*! Insertion operator, prints contents of model to screen
* @brief Insertion operator, prints contents of model to screen
* @pre none
* @param[in,out] out ostream object to print with and modify
* @param[in] g GITimeModel object to print out to console
* @post prints contents of src to the console
* @returns the modified ostream object 'out'
*/
ostream& operator<<(ostream &out, const GITimeModel &g);

/*! swap function, swaps contents of a and b model with each other
 * @brief swap function, swaps contents of a and b with each other
 * @pre none
 * @param[in,out] a GITimeModel object to be switched with 'b'
 * @param[in,out] b GITimeModel object to be switched with 'a'
 * @post swaps the contents of GIVector 'a' and 'b'
 */
void swap(GITimeModel &a, GITimeModel &b);

/*! GITimeModel class
 * @brief GITimeModel class, performs the bulk of the overview of managing
 *        the glucose and insulin level simulation, gets fed external glucose
 *        and insulin consumption from PIDController and prints new glucose
 *        and insulin concentrations in the bloodstream to the console
 */
class GITimeModel
{
    private:
        double glucose_level; //! current level of glucose conc. in blood
        double insulin_level; //! current level of insulin conc. in blood
        double glucose_eff; //! current eff. of glucose as func of insulin

        double step; //! step size for time model
        GIVector<double> base_gi_con; //! base glucose/insulin conc.
        GIVector<double> ext_gi_consumption; //! g/i consumption consts
        GIVector<double> p_consts; //! consts used in g/i diff. equations

    public:
        /*! Parameter constructor, creates a GITime Model object with info
         * @brief creates GITimeModel object with given information as params
         * @pre gl, insl, step must all be nonnegative floating point values
         *      gic, bgic must be GIVector holding 2 nonnegative float values
         *      pc must be GIVector containing 6 nonnegative float values
         * @param[in] gl the initial glucose level of the system
         * @param[in] ge the effectiveness of glucose as func of insulin
         * @param[in] insl the initial insulin level of the system
         * @param[in] s the step size of the time model
         * @param[in] gic the external glucose/insulin consumption values
         * @param[in] pc the 6 p-constants used to model diff. equations
         * @param[in] bgic the base glucose/insulin concentrations
         * @throw std::invalid_argument if gl, insl, step < 0
         * @throw std::invalid_argument if gic, bgic not of size 2
         * @throw std::invalid_argument if pc not vector of size 6
         * @post create a GITimeModel with given values as member vars.
         */
        GITimeModel(const double gl, const double ge, const double insl, 
            const double s, const GIVector<double> &gic, 
            const GIVector<double> &pc, const GIVector<double> &bgic);

        /*! Copy constructor, creates a GITimeModel object equal to src
         * @brief Copy constructor to create new GITimeModel equal to src
         * @pre none
         * @post creates a new GITimeModel equivalent in member vars. to src
         */
        GITimeModel(const GITimeModel &src);

        /*! Assignment operator, returns time model equal to copy of src
         * @brief Assignment operator, returns equivalent model via swap
         * @pre none
         * @post swaps the contents of the calling object and src (copy)
         * @returns the calling object after swap completed
         */
        GITimeModel& operator=(GITimeModel src);

        /*! Function evaluation, steps model, calculating next g/i levels
         * @brief Function evaluation, computes next g/i level at next time
         * @pre none
         * @post calculates next g/i level and adjusts their member vars.
         * @returns the new glucose level
         */
        double operator()();

        /*! External g/i consumption modifier, changing their values
         * @brief modify function to change ext_gi_consumption vect values
         * @pre g and i double values must be nonnegative
         * @param[in] g a double representing rate of external glucose cons.
         * @param[in] i a double representing rate of external insulin cons.
         * @throw std::invalid_argument if either g or i are less than 0
         * @post modifies ext_gi_consumption vector with new values
         */
        void modify_external_gi_consumption(const double g, const double i);

        /*! Insertion operator, prints contents of model to screen
         * @brief Insertion operator, prints contents of model to screen
         * @pre none
         * @param[in,out] out ostream object to print with and modify
         * @param[in] g GITimeModel object to print out to console
         * @post prints contents of src to the console
         * @returns the modified ostream object 'out'
         */
        friend ostream& operator<<(ostream &out, const GITimeModel &g);

        /*! swap function, swaps contents of a and b model with each other
         * @brief swap function, swaps contents of a and b with each other
         * @pre none
         * @param[in,out] a GITimeModel object to be switched with 'b'
         * @param[in,out] b GITimeModel object to be switched with 'a'
         * @post swaps the contents of GIVector 'a' and 'b'
         */
        friend void swap(GITimeModel &a, GITimeModel &b);
};

#endif