#include <iostream>
#include <functional>
#include "SIRDModel.h"
#include "SIRDVector.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
    if(argc != 3)
        throw std::invalid_argument("not enough cmd line arguments! (need 2)");
    cout.precision(8);

    SIRDVector<double> coefficients = SIRDVector<double>({0.01, 0.1, 0.05});
    SIRDModel model(atof(argv[1]), atof(argv[2]), 0.1, coefficients);

    cout << model << endl;
    for(size_t i = 0; i < 300; i++)
    {
        model();
        cout << model << endl;
    }
    return 0;
}