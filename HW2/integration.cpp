//  file: integration.cpp
// 
//  Integration of a function using a varying number of 
//  steps to solve with different methods.
//
//  Programmer: Zach Stewart  stewa668@msu.edu
//
//  Revision history:
//      02/27/2020  original C++ version
//
//  Notes:
//  - ...
//
// Part c
// 
// Graphically the approximation error starts being affected by roundoff a bit past
// 10^5, lets say 150,000 to be safe.
// 
// The approximation error is err = (10^-0.3)*N^(-2.5) approx 1/(2*N^(2.5))
// 
// Set this equal to roundoff, which is machine_eps * sqrt(N), then slove for N.
// 
// We get N = (2*me)*(-1/3), or 170,998.
// 
// This is just slightly past where the roundoff error starts affecting the approximation
// error, so it works very well as an N value. (It also shows the two are in agreement.) 
// To save computaional time, you could get the approximation errer from lets say 100 points,
// then use that to compute the optimum N. 
// 
//*********************************************************************//

// include files
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <omp.h>     // Just in case I want too. If I remove the GSL stuff it can be done in 2 lines
#include <gsl/gsl_integration.h>
using namespace std;

#include "integ_routines.h"

// function prototypes
double my_integrand (double x);
double my_integrand_4GSL (double x, void* params); // Because I'd rather not rewrite a ton
//*********************************************************************//

// A handy trick to write Pi to many digits
const double pi = 4.*atan(1.);

const double lower = 0; // Lower bound
const double upper = 2*pi ; // Upper Bound
const double Exact = 1.89469337820433017543851 ; // Wolfram'd because oh boy


struct my_f_params { double a; };

int
main (void)
{
  
  double result;                /* the result from the integration */

  gsl_function My_function;
  struct my_f_params params = { 1.0 };

  My_function.function = &my_integrand_4GSL;
  My_function.params = &params;

  ofstream out ("error_lin.dat"); // open the output file
  ofstream out2 ("error_log.dat"); // open the output file

  out << "#   N" << setw(20) << "Simpson's" << setw(20) << "Milne" << setw(20) << "GSL" << endl;
  out << "#" << setw(35) << setfill('-') << "" << setfill(' ') << endl;

  out2 << "#                  N" << setw(20) << "Simpson's" << setw(20) << "Milne" << setw(20) << "GSL" << endl;
  out2 << "#" << setw(35) << setfill('-') << "" << setfill(' ') << endl;

  gsl_integration_glfixed_table * t = gsl_integration_glfixed_table_alloc(1);

  for (int N = 1001 ; N <= 2000001 ; N += 4000) {
  
    out << setw(5) << N ;
    out2 << setw(20) << setprecision(14) << log10(N) ;

    result = simpsons_rule (N, lower, upper, &my_integrand);
    out << setw(20) << setprecision(14) << fabs((result-Exact)/Exact);
    out2 << setw(20) << setprecision(14) << log10(fabs((result-Exact)/Exact)); 

    result = milne_rule (N, lower, upper, &my_integrand);
    out << setw(20) << setprecision(14) << fabs((result-Exact)/Exact);
    out2 << setw(20) << setprecision(14) << log10(fabs((result-Exact)/Exact));
   
    if (N < 20000){
    t = gsl_integration_glfixed_table_alloc(N); // Used Gauss Legrande for fixed points
    }
    result = gsl_integration_glfixed(&My_function, lower, upper, t);            // It's awesome but slow for testing purpose
    out << setw(20) << setprecision(14) << fabs((result-Exact)/Exact);          // Hence the limit to avoid calculating weights
    out2 << setw(20) << setprecision(14) << log10(fabs((result-Exact)/Exact));  // But it reaches it's convergence fairly quickly

    out << " " << endl;  
    out2 << " " << endl;

  } 
  
  cout << "Data stored in error_lin.dat and error_log.dat\n";
  out.close();
  out2.close();

  return (0);
}

//*********************************************************************//

double
my_integrand (double x)
{
  // Mathematica form: -sqrt(x) * sin(x)

  return (-1. * sqrt(x) * sin(x) );
}

double
my_integrand_4GSL (double x, void * p) // Done like this because I didn't account fot the null pointer and I don't like warnings
  {
    struct my_f_params * params = (struct my_f_params *)p;
    double a = params->a ;

    return  (-a * sqrt(x) * sin(x) );
  }
