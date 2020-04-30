//  file: gsl_spline_test_class.cpp
// 
//  Test program for the gsl spline routines using the Spline class
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      02/10/09 -- created from gsl_cubic_spline_test.cpp
//
//  Notes:
//   * uses the GSL interpolation functions (see online documentation) 
//
//*****************************************************************
// include files
#include <iostream>		// cout and cin
#include <iomanip>		// manipulators like setprecision
#include <cmath>
#include <string>		// C++ strings
#include <fstream>
using namespace std;
#include "GslSpline.h"		// Header file for the GSL Spline class
#include <gsl/gsl_integration.h>

// function prototypes
double my_integrand (double x, void *params);

inline double
sqr (double z)
{
  return z * z;
}				// inline function for z^2

int
main (void)
{
  const int NMAX = 3000;		// maximum number of array points 
  double x_values[NMAX], y_values[NMAX];

  // Test: interpolate y = sin(x^2) from xmin to xmax with npts points 
  double xmin = 0.;
  double xmax = 10.;
  for (int npts = 10 ; npts <= NMAX ; npts++) {
  double deltax = (xmax - xmin)/double(npts-1);
  for (int i = 0; i < npts; i++)
  {
    double x_temp = xmin + double(i) * deltax;   // grid of x points
    x_values[i] = x_temp;
    y_values[i] = 2. * x_temp * exp(-x_temp);
  }

  // Make the spline object
  
  Spline my_cubic_spline (x_values, y_values, npts, "cubic");

  //cout << "    x     y_exact   y_spline   y'_exact  y'_spline";
  //cout << "  y''_exact  y''_spline" << endl;
  double abserr = 0;
  for (double x = 1 ; x <= 4 ; x += .001) {

  // Evaluate the spline and derivatives
  //double y = my_cubic_spline.y (x);
  double y_deriv = my_cubic_spline.yp (x);
  //double y_deriv2 = my_cubic_spline.ypp (x);
  double err = fabs(y_deriv + 2. * exp(-x) * (x-1.)) ;
  if (err > abserr) abserr = err ;
  //cout << fixed << setprecision(6) 
  //     << x << "  " << 2. * x * exp(-x) << "  " <<  y << "  "
  //     <<  -2. * exp(-x) * (x-1.) << "  " << y_deriv << "  "
  //     <<  2. * exp(-x) * (x-2.) << "  " <<  y_deriv2
  //     << endl;
}
cout << npts << " " << deltax << " " << abserr << endl;
if (abserr < 1e-6) break ;
}

cout << "NOW FOR INTEGRAL" << endl;
gsl_integration_workspace *work_ptr
    = gsl_integration_workspace_alloc (1000);

  double lower_limit = 0;       /* lower limit a */
  double upper_limit = 10;       /* upper limit b */
  double abs_error = 1.0e-8;    /* to avoid round-off problems */
  double rel_error = 1.0e-8;    /* the result will usually be much better */
  double result;                /* the result from the integration */
  double error;                 /* the estimated error from the integration */

  double alpha = 1.0;           // parameter in integrand

  gsl_function My_function;
  void *params_ptr = &alpha;                                                                                                                                                                                                                 
  My_function.function = &my_integrand;
  My_function.params = params_ptr;

  gsl_integration_qags (&My_function, lower_limit, upper_limit,
                        abs_error, rel_error, 1000, work_ptr, &result,
                        &error);

for (int npts = 10 ; npts <= NMAX ; npts++) {
  double deltax = (xmax - xmin)/double(npts-1);
  for (int i = 0; i < npts; i++)
  {
    double x_temp = xmin + double(i) * deltax;   // grid of x points
    x_values[i] = x_temp;
    y_values[i] = 2. * x_temp * exp(-x_temp);
  }

  // Make the spline object

  Spline my_cubic_spline (x_values, y_values, npts, "cubic");

  //cout << "    x     y_exact   y_spline   y'_exact  y'_spline";
  //cout << "  y''_exact  y''_spline" << endl;


double integral = my_cubic_spline.integ (0,10);
double relerr = fabs ((integral-result)/result);
cout << npts << " " << deltax << " " << relerr << endl;
if (relerr <= .02) break;
}


  return (0);      // successful completion 
}

double
my_integrand (double x, void *params)
{
  double alpha = *(double *) params;

  return alpha * 2. * x * exp(-x);
}
