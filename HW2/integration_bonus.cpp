//  file: integration_bonus.cpp
// 
//  This is for part e
//
//  Programmer: Zach Stewart  stewa668@msu.edu
//
//  Revision history:
//      02/27/2020  original C++ version
//
//  Notes:
//  - ...
//
// I'm using Milne and the same integral from the main script.
// 
// The approx error/exact we get is err = (10^-0.4)*N^(-2.5)
// 
// This is close to the correct answer, (-0.3 -> -0.4) and 
// gives the exact right power relationship. (Which is more important.)
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
//*********************************************************************//

// A handy trick to write Pi to many digits
const double pi = 4.*atan(1.);

const double lower = 0; // Lower bound
const double upper = 2*pi ; // Upper Bound


int
main (void)
{
  
  double result;                /* the result from the integration */
  double result2;

  ofstream out ("error_lin_bonus.dat"); // open the output file
  ofstream out2 ("error_log_bonus.dat"); // open the output file

  out << "#   N" << setw(20) << "Milne" << endl;
  out << "#" << setw(35) << setfill('-') << "" << setfill(' ') << endl;

  out2 << "#                  N" << setw(20) << "Milne" << endl;
  out2 << "#" << setw(35) << setfill('-') << "" << setfill(' ') << endl;

  for (int N = 405 ; N <= 20001 ; N += 4) {
  
    out << setw(5) << N ;
    out2 << setw(20) << setprecision(14) << log10(N) ;

    result = milne_rule (N, lower, upper, &my_integrand);
    result2 = milne_rule ((2*N-1), lower, upper, &my_integrand);
    out << setw(20) << setprecision(14) << fabs((result-result2)/result2);
    out2 << setw(20) << setprecision(14) << log10(fabs((result-result2)/result2));
   
    out << " " << endl;  
    out2 << " " << endl;

  } 
  
  cout << "Data stored in error_lin_bonus.dat and error_log_bonus.dat\n";
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
