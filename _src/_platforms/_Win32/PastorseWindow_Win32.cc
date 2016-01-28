#include "PastorseWindow.h"


PastorseWindow::PastorseWindow() {
	name_ = "Pastorse Ultra Engine";
}

void PastorseWindow::initWindow(int width, int height, std::string name){
	
	window_ = new Win;
  thread_ = new Win;
 
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

	if (!glfwInit()){
		exit(EXIT_FAILURE);
	}

	// MULTI THREAD TEST
	//glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
  //
	thread_->window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
  
	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
	window_->window = glfwCreateWindow(width, height, name.c_str(), NULL, thread_->window);

  makeContextCurrent(0);
	//glfwMakeContextCurrent(window_->window);
	glfwGetFramebufferSize(thread_->window, &width_, &height_);
	glfwSwapInterval(1);

  glViewport(0, 0, width, height);
}

void PastorseWindow::swapBuffers(int32 win_swap){
	if (win_swap == 0)
	{
		glfwSwapBuffers(window_->window);
	}
	else 
  {
    glfwSwapBuffers(thread_->window);
	}
	
}
void PastorseWindow::pollEvents(){
	glfwPollEvents();
}
void PastorseWindow::resizeWindow(int height, int width){
	glfwSetWindowSize(window_->window, width, height);
}
void PastorseWindow::closeWindow(){
	glfwDestroyWindow(window_->window);
	delete window_;
	window_ = nullptr;

  glfwDestroyWindow(thread_->window);
  delete thread_;
  thread_ = nullptr;
	glfwTerminate();
}

bool PastorseWindow::isClosedWindow(){
	if (!glfwWindowShouldClose(thread_->window)){
		return false;
	}else{return true;}
}

void PastorseWindow::setColor(float r, float g, float b, float a){
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLFWwindow *PastorseWindow::getWindow(){
	return thread_->window;
}

// TEST MULTITHREAD
void PastorseWindow::makeContextCurrent(int32 context)
{
  if (context == 0)
  {
    //printf("PWindow makeContextCurrent: WINDOW CURRENT\n");
    glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
    glfwMakeContextCurrent(window_->window);

  }
  else
  {
    //printf("PWindow makeContextCurrent: THREAD CURRENT\n");
    glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
    glfwMakeContextCurrent(thread_->window);
    // We do it here because until we don't change the context,
    // we don't activate depth to thread context.
    glEnable(GL_DEPTH_TEST);
  }
}