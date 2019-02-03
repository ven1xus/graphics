#include "Lab1.h"
#include "MyRectangle.h"
#include "Square.h"
#include "Triangle.h"
#include "Parallelogram.h"
#define GL_SILENCE_DEPRECATION 
/**
* Frame buffer that maintains the individual pixel colors in memory
* before they are displayed on the screen.
* This object is a global variable.
*/
FrameBuffer frameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);

/**
* Acts as the display function for the window.
*/

// X is left-right
// Y is Up-down

MyRectangle r2(300, 250, 75, 35, getRandomColor());
MyRectangle r1(200, 100, 30, 150, getRandomColor());
Square s2(50, 250, 100, getRandomColor());
Triangle t1(250,100,100,100, getRandomColor());
Parallelogram p;
static void RenderSceneCB()
{
	// Clear the color buffer
	frameBuffer.clearColorAndDepthBuffers(); // Not necessary for ray tracin

    p.draw(frameBuffer);
	// Rendering code that updates the color buffer
    r2.draw(frameBuffer);
    r1.draw(frameBuffer);
    t1.draw(frameBuffer);
    s2.draw(frameBuffer);
	 // Display the color buffer
	frameBuffer.showColorBuffer();

} // end RenderSceneCB


  // Reset viewport limits for full window rendering each time the window is resized.
  // This function is called when the program starts up and each time the window is 
  // resized.
static void ResizeCB(int width, int height)
{
	// Size the color buffer to match the window size.
	frameBuffer.setFrameBufferSize(width, height);

	// Signal the operating system to re-render the window
	glutPostRedisplay();

} // end ResizeCB


  // Register as the "idle" function to have the screen continously
  // repainted. Due to software rendering, the frame rate will not
  // be fast enough to support motion simulation
static void animate()
{
	glutPostRedisplay();

} // end animate


int main(int argc, char** argv)
{
	// freeGlut and Window initialization ***********************

	// Pass any applicable command line arguments to GLUT. These arguments
	// are platform dependent.
	glutInit(&argc, argv);

	// Set the initial display mode.
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA);

	// Set the initial window size
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	// Create a window using a string and make it the current window.
    //GLuint world_Window = glutCreateWindow("2D Shapes");
    glutCreateWindow("2D Shapes");
    glutPushWindow();
	// Indicate to GLUT that the flow of control should return to the program after
	// the window is closed and the GLUTmain loop is exited.
    #warning glutSetOption(X,Y) doesnt exist..
	//glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	// Callback for window redisplay
	glutDisplayFunc(RenderSceneCB);
	glutReshapeFunc(ResizeCB);
//    glutIdleFunc(animate);

	// ColorBuffer initialization ***********************

	// Create a clear color for the window
	color blue(0.784, 0.784, 1.0, 1.0);

	// Set red, green, blue, and alpha to which the color buffer is cleared.
	frameBuffer.setClearColor(blue);

	// Enter the GLUT main loop. Control will not return until the window is closed.
	glutMainLoop();

	// To keep the console open on shutdown, start the project with Ctrl+F5 instead of just F5.
	return 0;

} // end main
