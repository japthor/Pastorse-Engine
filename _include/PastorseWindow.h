#ifndef INCLUDE_PASTORSEWINDOW_H_
#define INCLUDE_PASTORSEWINDOW_H_ 1

#include <string> 
#include "PastorseTypes.h"
#include "GLFW\glfw3.h"


class PastorseWindow
{
public:
	PastorseWindow();
	~PastorseWindow(){};

	/// The function Init in engine Calls this function
	void initWindow(int width, int height, std::string name);

	/**
	* Resizes the window
	*
	* @param width new width.
	* @param height new height.
	*/
	void resizeWindow(int width, int height);

	/// Close the Window
	void closeWindow();

	/**
	* Testing MultiThreading 
	*
	* @param win_swap 0 window context, 1 thread context.
	*/
	void swapBuffers(int32 win_swap);
	/// Calls the GLFW PollEvents
	void pollEvents();
	/// Is the Window Closed
	bool isClosedWindow();
	/**
	* Sets the window color
	*
	* @param r r.
	* @param g g.
	* @param b b.
	* @param a a.
	*/
	void setColor(float r, float g, float b, float a);
	
	/**
	* Testing MultiThreading. Makes the current context (dont' use it)
	*
	* @param win_swap 0 window context, 1 thread context.
	*/
	void makeContextCurrent(int32 context);

	/// Gets the window
   GLFWwindow *getWindow();
private:

	struct Win {
		GLFWwindow* window;
	};

	Win* window_;
	Win* thread_;
	std::string name_;
	int width_;
	int height_;
};

#endif