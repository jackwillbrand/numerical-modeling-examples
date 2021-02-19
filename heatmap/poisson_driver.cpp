#include <iostream>
#include <chrono>
#include "containers/MyMatrix.h"
#include "matrix-solvers/PoissonMatrixMaker.h"
#include "matrix-solvers/CholeskyDecomp.h"
#include "matrix-solvers/SuccessiveOR.h"
#include "outputters/CSVOutputter.h"

using std::cout;
using std::cin;
using std::endl;
using std::chrono::duration_cast;

int main(int argc, char** argv)
{
    if(argc != 3)
        throw std::invalid_argument("wrong amount of cmd line arguments");
    
    MyVector<string> bwm_sep(1);
    MyMatrix<double> A = calc_poisson_matrix(string(argv[1]), bwm_sep);
    MyVector<double> b = calc_poisson_vector(A.rows(), forcing_func());

    char method;
    cout << "Choose method, type C for Cholesky, S for SOR method: ";
    cin >> method;

    while(method != 'C' && method != 'S')
    {
        cout << "invalid argument, type a C or an S: ";
        cin >> method;
    }

    MyVector<double> x(b.size());
    if(method == 'C')
    {
        cout << "Starting Cholesky Decomp..." << endl;
        auto start = std::chrono::high_resolution_clock::now();
        CholeskyDecomp cholesky(A);
        x = cholesky(b);
        auto stop = std::chrono::high_resolution_clock::now();
        auto dur = duration_cast<std::chrono::milliseconds>(stop - start);
        cout << "Cholesky Decomp Finish Time: " << dur.count() << endl << endl;
    }
    else if(method == 'S')
    {
        cout << "Starting Successive OR..." << endl;
        auto start = std::chrono::high_resolution_clock::now();
        SuccessiveOR successive_or(A);
        x = successive_or(b, get_w_value(), 0.01);
        auto stop = std::chrono::high_resolution_clock::now();
        auto dur = duration_cast<std::chrono::milliseconds>(stop - start);
        cout << "Successive OR Finish Time (ms): " << dur.count() << endl << endl;        
    }

    cout << "Writing Solution to CSV..." << endl;
    CSVOutputter csv_outputter(bwm_sep, x, x.size());
    csv_outputter();
    csv_outputter.output_to_file(string(argv[2]));

    cout << "Program completed, solution in csv. Thanks!" << endl;

    return 0;
}