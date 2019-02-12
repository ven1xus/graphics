#include "Lab3.h"


/**
* LAB INSTRUCTIONS:
* Below are descriptions of problems in vector arithmetic and three dimensional
* geometry. Most require you to implement a struct that can be used to
* represent two or three dimensional curves or surfaces.
*
* Coding up these problems gives you a chance to verify your work is correct.
* Test by using values or quantities for which you know the answer.
*
* Please note that Defines includes overloaded stream operators for printing
* dvec2, dvec3, and dvec4 objects to the console. These functions
* are useful for printing vectors and matrices to the console.
*
* Uncomment all function calls before turning in the lab.
* When you have completed all the problems, complete the following turning in
* instructions:
*
*	1.	Copy the folder containing your solution to the desktop.
*	2.	Change the name of the folder to CSE287LabTwo followed by your unique
*		identifier. For instance �CSE287LabTwoBachmaer.�
*	3.	Open the solution. Make sure it still runs.
*	4.	Clean the solution by selecting Build->Clean Solution. (This will delete
*		the intermediate temporary files that are part of your project and
*		reduce the size of your submission.)
*	5.	Zip up the solution folder using the standard windows compression tool.
*		(No 7zips, rars, etc. Just zips.)
*	6.	Submit your zip archive of the solution through canvas.
*
*/

// Complete the constructor and the checkPoint methods for the Circle struct.
// The constructor should assign the input arguments to the data members using an
// initializer list.
// The checkPoint method should return a negative value for points that are inside the
// circle, zero for points that are on the circle, and positive values for points
// that are outside the circle.
// Test the checkPoint function using using the following values:
//   Circle c with center at (0, 0) and radius = 1
//   vec2 p = [0.5 0] (inside circle)
//   vec2 q = [1 0] (on circle)
//   vec2 r = [2 0] (outside circle)
// Then test your function for points of your choosing on a Circle that is NOT
// centered on the origin.
// Display all the results to the console.
struct Circle {

	dvec2 center;
	double radius;

	Circle(double r = 1.0, dvec2 ctr = dvec2(0.0, 0.0)): center(ctr), radius(r) {};

	double checkPoint(dvec2 pt)
	{
        double result = pow(pt.x - center.x, 2 ) + pow(pt.y - center.y, 2) - pow(radius, 2);
        return result; 
	} // end checkPoint

}; // end Circle struct


void problem1()
{
	std::cout << "Problem 1" << std::endl;
    Circle c, far(2, dvec2(3,3));
    std::cout << c.checkPoint(dvec2(0.5 , 0)) << endl;
    std::cout << c.checkPoint(dvec2(1, 0)) << endl;
    std::cout << c.checkPoint(dvec2(2, 0)) << endl;
    
    std::cout << far.checkPoint(dvec2(3,4)) << endl; 
    std::cout << far.checkPoint(dvec2(3,5)) << endl; 
    std::cout << far.checkPoint(dvec2(3,6)) << endl;
} // end Problem1

// Create a Sphere struct that is similar to the Circle struct. Again, it should 
// have a constructor with default arguments and an initializer list, and a 
// checkPoint method that returns negative values, zero, and positive values in a 
// manner that is similar to the Circle struct. 
// Test using the following values:
//   Sphere s with center at (0, 0, 0) and radius = 1
//   vec3 p = [0 0.5 0] (inside sphere)
//   vec3 q = [1 0 0] (on sphere)
//   vec3 r = [0 0 4] (outside sphere)
// Then test with points of your choosing that are inside, on, and outside a Sphere 
// that is NOT centered on the origin. Display the results to the console.
struct Sphere {


}; // end Sphere struct

void problem2()
{
	std::cout << "Problem 2" << std::endl;


} // end Problem2

// Write a struct for a Quadric surface of your choice. It should include a constructor
// and checkPoint method as in the previous problems. Test the method in a similar 
// manner and display the results.

// Create struct here

void problem3()
{
	std::cout << "Problem 3" << std::endl;


} // end Problem3

// Write a Plane struct. The constructor should have three vec3s as parameters
// that are assumed to be in counter-clockwise order. The data members of the 
// struct should include a normal vector and a point on the Plane. The normal
// vector should point out of the side of the Plane on which the vertices are
// in counter-clockwise order and should be unit length. 
//
// As long as the normal vector is a unit vector, the signed distance of a 
// point from a plane is given by the equation on page 57 of the notes. Write
// a signedDistance function that has a vec3 as a parameter. 
// Test it using the following values:
//   Plane p with points (0, 4, 0), (0, 0, 0), (4, 0, 0)
//   vec3 x = [0 0 1] (in front of plane)
//   vec3 y = [0 0 -1] (behind plane)
//   vec3 z = [0 3 0] (on plane)
// Then test it for using points and a new Plane of your choosing. Display  
// all of your results on the console.
//
// Can your checkPoint methods in the previous questions be modified to 
// return a signed distance? If you believe the answer is "yes," go ahead
// and modify the functions accordingly in each of the previous questions.
struct Plane {


}; // end Plane struct

void problem4()
{
	std::cout << "Problem 4" << std::endl;


} // end Problem4

// Write a struct that supports a parametric representation of a line 
// in three dimensional space. The constructor should take two points on
// the line as parameters. 
//
// It should have a method called checkPoint that returns true if the 
// input argument is on the line and false otherwise. If the point is on 
// the line it should also return the parameter of the point "by reference." 
// Test this method for the following values:
//   ParametricLine with points (0, 0, 0) and (1, 0, 0)
//   Point u = (2, 0, 0) (on line,  returned parameter = 2)
//   Point v = (0, 3, 0) (off line)
// Then test the method with your own values for the line and points.
// Verify that the returned parameter is correct for points on the line. 
// Display the results. 
//
// Write a method called getPoint. Given a value for the parameter, t, it
// should return a vec3 that contains the location that corresponds to the
// supplied parameter. 
//
// Test this method with the same ParametricLine from the checkPoint test and 
// parameter values of 3, -3, and 0.5 (the results should be [3 0 0], 
// [-3 0 0], and [0.5 0 0], respectively).

// Then test the method using your own values for the line and points. Include
// parameters for positive and negative points, as well as a point in between
// the two used to define the line.
// Display the results.
struct ParametricLine {


	bool checkPoint(const dvec3 & p, double & t)
	{
		t = 0.0;
		return true;
	}


}; // end ParametricLine struct

void problem5()
{
	std::cout << "Problem 5" << std::endl;


} // end Problem5

// Write a function that supports linear interpolation between
// two scalar (doubles) values. It should take two doubles as 
// arguments. These represent the initial and ending values. It
// should also take a value for the interpolation parameter as 
// an argument. If the parameter is zero or negative, the function
// should return the initial value. If the parameter is one or
// greater, the function should return the final value. Otherwise,
// it should return an interpolated value between the begining 
// and ending values. Use the function to interpolate between 5 and 15.
// Test it with parameter values of -1, 0, 0.6, 1, and 20. Display
// the results to the console.
double linearInterpolateScalars(const double & initial, const double & final, const double & t)
{

	return 0.0;

} // end linearInterpolateScalars

void problem6()
{
	std::cout << "Problem 6" << std::endl;


} // end Problem6

// Write a function that linearly interpolates between two three
// dimension vector values. Functionality should be similar to 
// the previous question. Test it with points at (0,0,0) and (4, 4, 0).
// Use the same parameter values as the previous question. Display the 
// results.
dvec3 linearInterpolateVectors()
{
	return dvec3();
}

void problem7()
{
	std::cout << "Problem 7" << std::endl;


} // end Problem7


// Refer to the updated version of slide 37 in the chapter two notes
// for this problem. 
//
// Suppose the vector v = [2 -6 3] and the vector w = [-4 3 10].
// Find the vector that represents the projection of v onto w. Find the
// vector that represents the component of v that is perpendicular to w. Print
// out each of these vectors. Verify correctness by adding together the
// two calculated vectors and checking for equality with v. Also verify the 
// reuslts by taking the dot product of the two vectors. Display the results.
void problem8()
{
	std::cout << "Problem 8" << std::endl;

	dvec3 v(2, -6, 3);
	dvec3 w(-4, 3, 10);

} // end Problem8




int main(int argc, char** argv)
{
	// To keep the console open on shutdown, start the project with Ctrl+F5 instead of just F5.

	problem1();
	problem2();
	problem3();	
	problem4();	
	problem5();
	problem6();
	problem7();
	problem8();

	return 0;

} // end main
