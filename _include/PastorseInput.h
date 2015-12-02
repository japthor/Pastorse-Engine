#ifndef INCLUDE_PASTORSEINPUT_H_
#define INCLUDE_PASTORSEINPUT_H_ 1

#include "GLFW\glfw3.h"
#include "PastorseTypes.h"

class PastorseInput
{
public:

	PastorseInput();
	~PastorseInput(){};
		
	void key_input(GLFWwindow* window);

	float32 get_x();
	void set_x(float32 x);

	float32 get_y();
	void set_y(float32 y);

	float32 get_z();
	void set_z(float32 z);

	void set_key_input(GLFWwindow* window, void *a);

private:
	float32 x_;
	float32 y_;
	float32 z_;

};

#endif