#include <cassert>

SIRDModel::SIRDModel(const double p0, const double i0, const double h, 
    const SIRDVector<double> c)
{
    if(p0 < 0)
        throw std::invalid_argument("initial population must be nonnegative");
    
    if(i0 < 0)
        throw std::invalid_argument("infected pop. must be nonnegative");
    
    if(c.size() != 3)
        throw std::invalid_argument("coeff. vector contains too less/much");

    total_pop = p0;
    infected = i0;
    susceptible = total_pop - infected;
    dead = 0;
    recovered = 0;
    step = h;
    coeff = c;
}

void SIRDModel::operator()()
{
    std::function<double(double)> s_func = 
        [&](double s0) { return (-1 * coeff[0] * infected * s0)*step + s0; };
    std::function<double(double)> i_func =
        [&](double i0) { return ((coeff[0] * i0 * susceptible) - 
            (coeff[1] * i0) - (coeff[2] * i0))*step + i0; };
    std::function<double(double)> r_func = 
        [&](double r0) { return (coeff[1] * infected)*step + r0; };
    std::function<double(double)> d_func =
        [&](double d0) { return (coeff[2] * infected)*step + d0; };

    SIRDEuler<double> s(s_func, susceptible, step);
    SIRDEuler<double> i(i_func, infected, step);
    SIRDEuler<double> r(r_func, recovered, step);
    SIRDEuler<double> d(d_func, dead, step);

    double new_s = s();
    double new_i = i();
    double new_r = r();
    double new_d = d();

    susceptible = new_s;
    infected = new_i;
    recovered = new_r;
    dead = new_d;
}

ostream& operator<<(ostream &out, const SIRDModel &src)
{
    std::cout << "Susceptible: " << src.susceptible << ", ";
    std::cout << "Infected: " << src.infected << ", ";
    std::cout << "Recovered: " << src.recovered << ", ";
    std::cout << "Deceased: " << src.dead;
    return out;
}