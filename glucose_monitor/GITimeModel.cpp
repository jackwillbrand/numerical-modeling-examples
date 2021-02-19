#include <iostream>
#include "GITimeModel.h"

GITimeModel::GITimeModel(const double gl, const double ge, const double insl, 
    const double s, const GIVector<double> &gic, const GIVector<double> &pc, 
        const GIVector<double> &bgic)
{
    if(gl < 0 || insl < 0 || step < 0)
        throw std::invalid_argument("glucose/insulin level or step < 0");
    if(gic.size() != 2 || bgic.size() != 2)
        throw std::invalid_argument("gic or bgic not of size 2");
    if(pc.size() != 6)
        throw std::invalid_argument("pc vector of consts not size 6");
    
    glucose_level = gl;
    insulin_level = insl;
    glucose_eff = ge;
    step = s;
    ext_gi_consumption = gic;
    p_consts = pc;
    base_gi_con = bgic;
}

GITimeModel::GITimeModel(const GITimeModel &src)
{
    glucose_level = src.glucose_level;
    insulin_level = src.insulin_level;
    glucose_eff = src.glucose_eff;
    step = src.step;
    ext_gi_consumption = src.ext_gi_consumption;
    p_consts = src.p_consts;
    base_gi_con = src.base_gi_con;
}

void swap(GITimeModel &a, GITimeModel &b)
{
    std::swap(a.insulin_level, b.insulin_level);
    std::swap(a.glucose_level, b.glucose_level);
    std::swap(a.glucose_eff, b.glucose_eff);
    std::swap(a.step, b.step);
    std::swap(a.ext_gi_consumption, b.ext_gi_consumption);
    std::swap(a.p_consts, b.p_consts);
    std::swap(a.base_gi_con, b.base_gi_con);
}

GITimeModel& GITimeModel::operator=(GITimeModel src)
{
    std::swap(*this, src);
    return *this;
}

double GITimeModel::operator()()
{
    std::function<double(double)> dGdt = [&] (double g0)
        { return -(p_consts[0] + glucose_eff)*g0 + 
            p_consts[0]*base_gi_con[0] + ext_gi_consumption[0]; };
        
    std::function<double(double)> dXdt = [&] (double x0)
        { return -p_consts[1]*x0 + p_consts[2] *
            (insulin_level-base_gi_con[1]); };
            
    std::function<double(double)> dIdt = [&] (double i0)
        { return p_consts[3]*std::max(0.0, glucose_level-p_consts[4]) -
            p_consts[5]*(i0-base_gi_con[1]) + ext_gi_consumption[1]; };

    GIRungeKutta<double> glucose(dGdt, glucose_level, step);
    GIRungeKutta<double> glucose_efficiency(dXdt, glucose_eff, step);
    GIRungeKutta<double> insulin(dIdt, insulin_level, step);

    double new_g = glucose();
    double new_ge = glucose_efficiency();
    double new_i = insulin();

    glucose_level = new_g;
    glucose_eff = new_ge;
    insulin_level = new_i;

    return glucose_level;
}

void GITimeModel::modify_external_gi_consumption(const double g,const double i)
{
    if(g < 0)
        throw std::invalid_argument("ext. g val to modify is negative");
    if(i < 0)
        throw std::invalid_argument("ext. i val to modify is negative");
    
    ext_gi_consumption[0] = g;
    ext_gi_consumption[1] = i;
}

std::ostream& operator<<(std::ostream &out, const GITimeModel &g)
{
    out << "Glucose: " << g.glucose_level << ", ";
    out << "Insulin: " << g.insulin_level;
    return out;
}