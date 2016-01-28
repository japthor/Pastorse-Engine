#ifndef INCLUDE_PASTORSEINPUT_H_
#define INCLUDE_PASTORSEINPUT_H_ 1

#include "GLFW\glfw3.h"
#include "PastorseTypes.h"

class PastorseInput
{
public:

	PastorseInput();
	~PastorseInput(){};
	
	/// Inits the Input
	void keyInput(GLFWwindow* window);

	/// Get's X
	float32 getX();
	/// Set's X
	void setX(float32 x);
	/// Get's Y
	float32 getY();
	/// Set's Y
	void setY(float32 y);
	/// Get's Z
	float32 getZ();
	/// Set's Z
	void setZ(float32 z);

private:
	float32 x_;
	float32 y_;
	float32 z_;

};

#endif