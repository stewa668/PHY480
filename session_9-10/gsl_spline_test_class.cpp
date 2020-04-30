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

inline double
sqr (double z)
{
  return z * z;
}				// inline function for z^2

int
main (void)
{
//  const int NMAX = 300;		// maximum number of array points 
//  double x_values[NMAX], y_values[NMAX];

  // Test: interpolate y = sin(x^2) from xmin to xmax with npts points 
//  double xmin = 0.;
//  double xmax = 200.;
  int npts = 9;
//  double deltax = (xmax - xmin)/double(npts-1);
//  for (int i = 0; i < npts; i++)
//  {
//    double x_temp = xmin + double(i) * deltax;   // grid of x points
//    x_values[i] = x_temp;
//    y_values[i] = sin (x_temp * x_temp);
//  }

  double x_values[9] = { 0., 25., 50., 75., 100., 125., 150., 175., 200. };
//  double y_exp[9] =
//    { 10.6, 16.0, 45.0, 85.5, 52.8, 19.9, 10.8, 8.25, 4.70 };
  double y_values[9] = { 9.34, 17.9, 41.5, 83.5, 51.5, 21.5, 10.8, 6.29, 4.09 };

  // Make the spline object
  
  Spline my_lin_spline (x_values, y_values, npts, "linear");
  Spline my_poly_spline (x_values, y_values, npts, "polynomial");
  Spline my_cubic_spline (x_values, y_values, npts, "cubic");

  ofstream out;
  out.open("splines.dat") ; 

  out << "    x     y_exact   y_lspline  y_pspline  y_cspline" << endl;
  for (double x = 0; x < 201.; x += 5.)
    {

      // Evaluate the spline and derivatives
      double yl = my_lin_spline.y (x);
      double yp = my_poly_spline.y (x);
      double yc = my_cubic_spline.y (x);
   

      out << fixed << setprecision (6)
	<< x << " " << 63900 / ((x - 78.) * (x - 78.) +
				3025. / 4.) << " " << yl << " " << yp << " " << yc << endl;
    }
  
  out.close();
  return (0);			// successful completion 
}
