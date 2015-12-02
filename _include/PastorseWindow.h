#ifndef INCLUDE_PASTORSEWINDOW_H_
#define INCLUDE_PASTORSEWINDOW_H_ 1

#include <string> 
#include "GLFW\glfw3.h"


class PastorseWindow
{
public:
	PastorseWindow();
	~PastorseWindow(){};

	void init_window(int width, int height, std::string name);
	void resize_window(int width, int height);
	void close_window();
	void swapBuffers_window();
	void pollEvents_window();
	bool is_closed_window();
	void change_color_window(float r, float g, float b, float a);

	GLFWwindow *getWindow();
private:

	struct Win {
		GLFWwindow* window;
	};

	Win* dt_;
	std::string name_;
	int width_;
	int height_;
};

#endif