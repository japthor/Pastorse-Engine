#include "PastorseWindow.h"


PastorseWindow::PastorseWindow() {
	name_ = "Pastorse Ultra Engine";
}

void PastorseWindow::init_window(int width, int height, std::string name){
	
	dt_ = new Win;
 
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

	if (!glfwInit()){
		exit(EXIT_FAILURE);
	}

	dt_->window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

	glfwMakeContextCurrent(dt_->window);
	glfwGetFramebufferSize(dt_->window, &width_, &height_);
	glfwSwapInterval(1);
}

void PastorseWindow::swapBuffers_window(){
	glfwSwapBuffers(dt_->window);
}
void PastorseWindow::pollEvents_window(){
	glfwPollEvents();
}
void PastorseWindow::resize_window(int height, int width){
	glfwSetWindowSize(dt_->window, width, height);
}
void PastorseWindow::close_window(){
	glfwDestroyWindow(dt_->window);
	glfwTerminate();
}

bool PastorseWindow::is_closed_window(){
	if (!glfwWindowShouldClose(dt_->window)){
		return false;
	}else{return true;}
}

void PastorseWindow::change_color_window(float r, float g, float b, float a){
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLFWwindow *PastorseWindow::getWindow(){
	return dt_->window;
}




