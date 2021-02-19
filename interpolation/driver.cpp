/*!
 * Author: Jackson Willbrand, 2/12/2020
 * File: driver.cpp
 * Class: CS 5201 Section A
 * Instructor: Clayton Price
 * Description: driver class for interpolator hw2
 */

#include "interpolator.h"
using std::cin;
using std::cout;
using std::endl;

int main()
{
    cout.precision(8);

    // read in number of independent variables for two functions
    int num_vals1, num_vals2;
    cin >> num_vals1 >> num_vals2;

    // read in two data sets from sample input (all vars of type float)
    interpolator<double> data_set1(num_vals1), data_set2(num_vals2);
    cin >> data_set1 >> data_set2;

    // print interpolated value of both functions for ind. value 1.707
    tuple<double, double> dep_v1 = data_set1(1.707);
    cout <<"1.707: "<< get<0>(dep_v1) <<" "<< get<1>(dep_v1) << "\r" << endl;

    tuple<double, double> dep_v2 = data_set2(1.707);
    cout <<"1.707: "<< get<0>(dep_v2) <<" "<< get<1>(dep_v2) << "\r" << endl;

    // print 0 if first interpolator is greater than second, 1 otherwise
    cout << !(data_set1 > data_set2) << "\r" << endl;

    // modify data point of first interpolator at ind. var. value of zero
    // to the pair of dependent variables
    data_set1[0.0] = std::make_tuple(0.0, 1.47, -0.0234);

    // print interpolated values of first interpolator object for ind.
    // value of 0.03
    tuple<double, double> dep_v1b = data_set1(0.03);
    cout <<"0.03: "<< get<0>(dep_v1b) <<" "<< get<1>(dep_v1b) << "\r" << endl;

    return 0;
}