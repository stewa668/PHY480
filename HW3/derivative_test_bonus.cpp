//  file: derivative_test_bonus.cpp
//
//  Program to study the error in differentiation rules
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      01/14/04  original version, translated from derivative_test.c
//      01/20/05  modified extrap_diff to use central_diff
//
//  Notes:
//   * Based on the discussion of differentiation in Chap. 8
//      of "Computational Physics" by Landau and Paez.
//   * As a convention (advocated in "Practical C"), we'll append
//      "_ptr" to all pointers.
//   * Use the adaptive gsl_diff_central function as well.
//      Output from this with e^(-x) at x=1 is:
//  gsl_diff_central(1) = -3.6787944117560983e-01 +/- 6.208817e-04
//   actual relative error: 1.13284386e-11
//
// My Notes
//  This is for bonus 4
//  My approach may be overkill, but for calculating one point this is
//  fine. First, I say I want to calculate the 3rd derivative with 
//  error at 10^-12 (a tall order but decent start), so I calucate the 
//  third derivative with a stepsize that allows that. Using the value 
//  for the third derivative, I then give optimun h for central 
//  difference, saying h^3 = 24*eps*f/f3 .
//
//  My roundoff error line is a bit too high. Not unusual. Other than
// than that my answer is very close to ideal. I'm happy with the method.
//
// Also I think there might be an error in session 3, as I think round-off
// error is missing a factor of f(x). Check out this link, their proof is 
// largely the same except for that one thing. 
// https://www.cs.cornell.edu/~bindel/class/cs3220-s12/notes/lec22.pdf
//
//*****************************************************************
// include files
#include <iostream>		// note that .h is omitted
#include <iomanip>		// note that .h is omitted
#include <fstream>		// note that .h is omitted
#include <cmath>
using namespace std;		// we need this when .h is omitted
#include <gsl/gsl_math.h>
#include <gsl/gsl_diff.h>

// function prototypes
double funct (double x, void *params_ptr);
double funct_deriv (double x, void *params_ptr);

double central_diff (double x, double h,
		     double (*f) (double x, void *params_ptr),
		     void *params_ptr);
double third_derivative (double x, double h,
			 double (*f) (double x, void *params_ptr),
			 void *params_ptr);

//************************** main program ***************************
int
main (void)
{
  void *params_ptr;		// void pointer passed to functions
  double hmin = 1E-10;
  double x = 1.;		// find the derivative at x
  double alpha = 1.;		// a parameter for the function
  double diff_cd, diff_cd3;	//, diff_fd;     // central, forward difference
//double diff_extrap, diff_extrap2;             // extrapolated derivative
  double diff_gsl_cd;		// gsl adaptive central derivative
  gsl_function My_F;		// gsl_function type
  double abserr;		// absolute error

  ofstream out ("derivative_test_bonus.dat");	// open the output file

  params_ptr = &alpha;		// double to pass to function

  double answer = funct_deriv (x, params_ptr);	// exact answer for test

  My_F.function = &funct;	// set up the gsl function
  My_F.params = params_ptr;
  gsl_diff_central (&My_F, x, &diff_gsl_cd, &abserr);	// gsl calculation

  cout << "gsl_diff_central(" << x << ") = " << scientific
    << setprecision (16) << diff_gsl_cd << " +/- "
    << setprecision (6) << abserr << endl;
  cout << " actual relative error: " << setprecision (8)
    << fabs ((diff_gsl_cd - answer) / answer) << endl;

  double h = 1;			// initialize mesh spacing
  while (h >= hmin)
    {
//diff_fd = forward_diff (x, h, &funct, params_ptr);
      diff_cd = central_diff (x, h, &funct, params_ptr);
//diff_extrap = extrap_diff (x, h, &funct, params_ptr);
// diff_extrap2 = extrap_diff2 (x, h, &funct, params_ptr); // THIS IS NOT EFFICIENT NOW. I'LL CHEAT TO GET A BIT FASTER WITH NEXT LINE
//diff_extrap2 = (16.*extrap_diff(x, h/2., &funct, params_ptr) - diff_extrap)/15. ;
// Just did not want to needlessly repeat the calc, the function is still below

// print relative errors to output file
      out << scientific << setprecision (8) << log10 (h) << "   "
//<< log10 (fabs ((diff_fd - answer) / answer)) << "   "
	<< log10 (fabs ((diff_cd - answer) / answer) ) << endl;
//<< log10 (fabs ((diff_extrap - answer) / answer)) << "   " 
//<< log10 (fabs ((diff_extrap2 - answer) / answer)) << endl;

      h /= 2.;			// reduce mesh by 2
    }

  h = (DBL_EPSILON) / (1E-12);
  diff_cd3 = third_derivative (x, h, &funct, params_ptr);
  cout << "3rd Der. = " << diff_cd3 << endl;
  h = pow (fabs((24. * DBL_EPSILON * funct(x, params_ptr) / diff_cd3)), (1. / 3.));
  diff_cd = central_diff (x, h, &funct, params_ptr);
  cout << "Optimal h: " << h << endl;
  cout << "Optimal log10(h): " << log10(h) << endl;
  cout << "Log10 of error: " << log10 (fabs ((diff_cd - answer) / answer)) <<
    endl;
  cout << "Actual hopt should be: " << pow (fabs(24. * DBL_EPSILON ), (1. / 3.)) << endl; // Only for this alpha




  out.close ();			// close the output stream
  return (0);			// successful completion
}

//************************** funct ***************************
double
funct (double x, void *params_ptr)
{
  double alpha;
  alpha = *(double *) params_ptr;

  return (exp (-alpha * x));
}

//************************** funct_deriv *********************
double
funct_deriv (double x, void *params_ptr)
{
  double alpha = *(double *) params_ptr;

  return (-alpha * exp (-alpha * x));
}


//************************** central_diff *********************
double
central_diff (double x, double h,
	      double (*f) (double x, void *params_ptr), void *params_ptr)
{
  return (f (x + h / 2., params_ptr) - f (x - h / 2., params_ptr)) / h;
}

// THIRD DERIVATIVE

double
third_derivative (double x, double h,
		  double (*f) (double x, void *params_ptr), void *params_ptr)
{
  return (f (x + 3. * h / 2., params_ptr) - 3 * f (x + h / 2., params_ptr) +
	  3 * f (x - h / 2., params_ptr) - f (x - 3. * h / 2.,
					      params_ptr)) / (h * h * h);
}
