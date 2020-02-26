//  file: diffeq_test.cpp
// 
//  Program to study the error in differential equation algorithms
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      02/07/04  original version, translated from diffeq_test.c
//      01/30/05  comments improved and function names changed
//      01/22/06  improved code organization
//
//  Notes:
//   * Based on the discussion of differential equations in Chap. 9
//      of "Computational Physics" by Landau and Paez
//   * As a convention (advocated in "Practical C++"), we'll append
//      "_ptr" to all pointers.
//
//********************************************************************

// include files
#include <iostream>		// note that .h is omitted
#include <iomanip>		// note that .h is omitted
#include <fstream>		// note that .h is omitted
using namespace std;		// we need this when .h is omitted
#include <cmath>
#include "diffeq_routines.h"	// diffeq routine prototypes

// function prototypes
double rhs (double t, double y[], int i, void *params_ptr);
double exact_answer (double t, void *params_ptr);

// structures
typedef struct			// define a type to hold parameters 
{
  double alpha;
  double beta;
}
f_parameters;			// now we can define a structure of this type
				//   using the keyword "f_parameters" 

const double pi = 4.*atan(1.);
//************************** main program ****************************
int
main (void)
{
  void *params_ptr;		// void pointer passed to functions 
  f_parameters funct_parameters;	// parameters for the function 

  const int N = 1;		// size of arrays of y functions
  double y_euler[N], y_rk2[N], y_rk4[N];	// arrays of y functions 

  ofstream out ("diffeq_test_h.dat");	// open the output file 

  funct_parameters.alpha = 2.;	// function parameter to be passed 
  funct_parameters.beta = 4.*atan(1.);	// function parameter to be passed
  params_ptr = &funct_parameters;	// structure to pass to function 

  double tmin = 0.;		// starting t value 
  double tmax = 1.;		// last t value 

  for (double h = 1.; h >= 1e-8; h = h / 2.)
    {
      y_euler[0] = 0.0;		// initial condition for y(t) 
      y_rk2[0] = 0.0;           // initial condition for y(t)
      y_rk4[0] = 0.0;		// initial condition for y(t) 


      for (double t = tmin; t <= tmax; t += h)
	{

	  // find y(t+h) and output vs. t+h 
	  euler (N, t, y_euler, h, rhs, params_ptr);	// Euler's algorithm 
          runge2 (N, t, y_rk2, h, rhs, params_ptr);     // 2nd order R-K
	  runge4 (N, t, y_rk4, h, rhs, params_ptr);	// 4th order R-K 

	  if (t == 1. - h)
	    {
	      out << scientific << setprecision (16)
		<< h << "  "
		<< y_euler[0] << "  "
                << y_rk2[0] << "  "
		<< y_rk4[0] << "  " << exact_answer (1., params_ptr) << endl;
	    }
	}
    }
  cout << "data stored in diffeq_test_h.dat\n";
  out.close ();			// close the output file 

  return (0);			// successful completion 
}


//************************** rhs ************************************
//
//  * This is the function defining the right hand side of the diffeq
//
//*********************************************************************
double
rhs (double t, double y[], int i, void *params_ptr)
{
  double a = ((f_parameters *) params_ptr)->alpha;
  double b = ((f_parameters *) params_ptr)->beta; 

  if (i == 0)
    {
      //return (-a * t * y[0]);
      return (a*cos(a*b*t) + y[0] - y[0]);
    }

  return (1);			// something's wrong if we get here 
}

//********************** exact_answer **************************
//
//  * This is the exact answer for y(t)
//
//******************************************************************
double
exact_answer (double t, void *params_ptr)
{
  // recover a and b from the void pointer params_ptr
  double a = ((f_parameters *) params_ptr)->alpha;
  double b = ((f_parameters *) params_ptr)->beta;

  //return (b * exp (-a * t * t / 2.));
  return (sin(a*b*t)/b);
}
