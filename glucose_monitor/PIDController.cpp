#include "PIDController.h"

PIDController::PIDController(const GIVector<double> &ki, const double g, 
    const double i)
{
    if(ki.size() != 3)
        throw std::invalid_argument("k vector not of size 3");
    if(g < 0)
        throw std::invalid_argument("desired glucose level negative");
    if(i < 0)
        throw std::invalid_argument("initial glucose level negative");
    
    k = ki;
    u_values = GIVector<double>(2);
    desired_glucose_conc = g;
    curr_error = std::abs(i - g);
    initial_error = curr_error;
}

PIDController::PIDController(const PIDController &src)
{
    u_values = src.u_values;
    k = src.k;
    desired_glucose_conc = src.desired_glucose_conc;
    curr_error = src.curr_error;
}

void swap(PIDController &a, PIDController &b)
{
    std::swap(a.u_values, b.u_values);
    std::swap(a.k, b.k);
    std::swap(a.desired_glucose_conc, b.desired_glucose_conc);
    std::swap(a.curr_error, b.curr_error);
}

PIDController& PIDController::operator=(PIDController src)
{
    swap(*this, src);
    return *this;
}

void PIDController::operator()(const double g, const double step)
{
    if(step < 0)
        throw std::invalid_argument("curr_time for PID() is negative");
    if(g < 0)
        throw std::invalid_argument("glucose level for PID() is negative");
    
    // assign previous error, calculate curr error, subtract to get de/dt
    double prev_error = curr_error;
    curr_error = g - desired_glucose_conc;
    double d_error = curr_error - prev_error;

    // trapezoid rule w/ previous/ current error to get integral of edt
    double min_error = std::abs(std::min(curr_error, prev_error));
    double i_error = (2*min_error + std::abs(d_error))/2 * step;

    double u = k[0]*curr_error + k[1]*i_error + k[2]*d_error;
    u_values[0] = u < 0 ? -u : 0;
    u_values[1] = u > 0 ? u : 0;
}

double PIDController::operator[](const size_t i) const
{
    if(i >= k.size())
        throw std::invalid_argument("i out of range for PID[]");
    return k[i];
}

double& PIDController::operator[](const size_t i)
{
    if(i >= k.size())
        throw std::invalid_argument("i out of range for PID[]");
    return k[i];
}

void PIDController::reset(const double new_desired_glucose)
{
    if(new_desired_glucose < 0)
        throw std::invalid_argument("new desired glucose level negative");
    desired_glucose_conc = new_desired_glucose;
}