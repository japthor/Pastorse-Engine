#include "PastorseInput.h"
#include<stdio.h>

PastorseInput::PastorseInput(){
	x_ = 0.0f;
	y_ = 0.0f;
	z_ = 10.0f;
}

void PastorseInput::keyInput(GLFWwindow* window){
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
		y_ += 0.1f;
	}
	
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		y_ -= 0.1f;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
		x_ -=  0.1f;
	}
	 
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		x_ += 0.1f;
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
		z_ -= 0.1f;
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
		z_ += 0.1f;
	}

}

float32 PastorseInput::getX(){
	return x_;
}

void PastorseInput::setX(float32 x){
	x_ = x;
}

float32 PastorseInput::getY(){
	return y_;
}

void PastorseInput::setY(float32 y){
	y_ = y;
}

float32 PastorseInput::getZ(){
	return z_;
}

void PastorseInput::setZ(float32 z){
	z_ = z;
}




