#include <iostream>
#include "GITimeModel.h"
#include "PIDController.h"
using std::cin;
using std::cout;
using std::endl;

int main()
{
    GIVector<double> k_consts({10, 0.5, 0.5});
    double desired_glucose_level = 100;
    double glucose_level = 400;
    PIDController u_calc(k_consts, desired_glucose_level, glucose_level);

    GIVector<double> p({0.05, 0.5, 0.0001, 0.00001, 150, 0.05});
    GIVector<double> bgic({300, 40});
    GIVector<double> egic({0, 0});
    double step = 0.15;
    GITimeModel model(400, 0, 200, step, egic, p, bgic);
    cout << model << endl;

    for(double i = 0; i < 100.0; i += step)
    {
        u_calc(glucose_level, step);
        egic = u_calc.get_u_vals();
        model.modify_external_gi_consumption(egic[0], egic[1]);
        glucose_level = model();
        cout << model << endl;
    }

    return 0;
}