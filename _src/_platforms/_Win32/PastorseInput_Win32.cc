#include "PastorseInput.h"
#include<stdio.h>

PastorseInput::PastorseInput(){
	x_ = 0.0f;
	y_ = 0.0f;
	z_ = 10.0f;
	r_ = 0.0f;
	t_ = 0.0f;
	space_ = false;
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

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
		r_ += 0.1f;
		t_ -= 0.1f;
	}

	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS){
		t_ += 0.1f;
		r_ -= 0.1f;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
		space_ = true;
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

float32 PastorseInput::getR(){
	return r_;
}

float32 PastorseInput::getT(){
	return t_;
}

bool PastorseInput::getSpace(){
	return space_;
}

void PastorseInput::setSpace(bool space){
	space_ = space;
}




