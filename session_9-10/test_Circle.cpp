//  file: test_Circle.cpp
//
//  This program calculates the area of a circle, given the radius.
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      05-Feb-2009  original version, for 780.20 Computational Physics
//      11-Feb-2010  added output statements
//
//  Notes:  
//   * Use make_test_Circle to compile and link with the Circle class
//   * Compare to area.cpp from Session 1  
//
//  To do:
//   * Test additional methods for the Circle class
//
//*********************************************************************// 

// include files
#include <iostream>		
using namespace std;  // otherwise preprend std:: to cin, cout, endl

#include "Circle.h"   // include the Circle class definition
#include "Sphere.h"

//*********************************************************************//

int
main ()
{
  double my_radius;
  cout << "Enter the radius of a circle: ";	// ask for radius
  cin >> my_radius;
  
  Circle my_first_circle(my_radius);  // create a Circle object
  
  double my_area = my_first_circle.area();
  double my_circumference = my_first_circle.circumference();
  cout << "radius = " << my_radius << ", area = " << my_area << ", circ = " << my_circumference << endl;

  Sphere my_first_sphere(my_radius);  // create a Sphere object

  double my_sarea = my_first_sphere.surface_area();
  double my_volume = my_first_sphere.volume();
  cout << "radius = " << my_first_sphere.get_radius() << ", sarea = " << my_sarea << ", volume = " << my_volume << endl;
            
  // Now create another circle in a block (i.e., between {}'s)
  {
    Circle my_second_circle(2.*my_radius);
    cout << "Made a 2nd circle of radius: "
         << my_second_circle.get_radius() << endl;
    cout << endl << "Last statement inside {}'s . . . " << endl;	 
  }          
  cout << "Now outside {}'s. " << endl << endl;
              
  return (0);			// successful completion
}

//*********************************************************************//
  
