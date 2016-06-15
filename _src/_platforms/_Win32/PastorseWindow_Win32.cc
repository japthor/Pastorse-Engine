#include "PastorseWindow.h"
#include "GLFW\glfw3.h"

GLFWwindow* window_ = nullptr;
GLFWwindow* thread_ = nullptr;

PastorseWindow::PastorseWindow() {
	name_ = "Pastorse Ultra Engine";
}

void PastorseWindow::initWindow(int width, int height, std::string name){
 
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
	/*thread_ = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
  
	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
	window_= glfwCreateWindow(width, height, name.c_str(), NULL, thread_);

  makeContextCurrent(0);
	//glfwMakeContextCurrent(window_->window);
	glfwGetFramebufferSize(thread_, &width_, &height_);
	glfwSwapInterval(1);

  glViewport(0, 0, width, height);*/

  /// Prueba!!!!!!

  window_ = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

  glfwMakeContextCurrent(window_);
  glfwGetFramebufferSize(window_, &width_, &height_);
  glfwSwapInterval(1);
}

void PastorseWindow::swapBuffers(int32 win_swap){
	/*if (win_swap == 0)
	{
		glfwSwapBuffers(window_);
	}
	else 
  {
    glfwSwapBuffers(thread_);
	}*/

  ///Prueba!!!!!!
  glfwSwapBuffers(window_);
}
void PastorseWindow::pollEvents(){
	glfwPollEvents();
}
void PastorseWindow::resizeWindow(int height, int width){
	glfwSetWindowSize(window_, width, height);
}
void PastorseWindow::closeWindow(){
	glfwDestroyWindow(window_);
	delete window_;
	window_ = nullptr;

  ///Prueba!!!!!!
  /*glfwDestroyWindow(thread_);
  delete thread_;
  thread_ = nullptr;*/
	glfwTerminate();
}

bool PastorseWindow::isClosedWindow(){
	/*if (!glfwWindowShouldClose(thread_)){
		return false;
	}else{return true;}*/
  ///Prueba!!!!!!
  if (!glfwWindowShouldClose(window_)){
    return false;
  }
  else{ return true; }
}

void PastorseWindow::setColor(float r, float g, float b, float a){
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}


// TEST MULTITHREAD
void PastorseWindow::makeContextCurrent(int32 context)
{
  /*if (context == 0)
  {
    //printf("PWindow makeContextCurrent: WINDOW CURRENT\n");
    glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
    glfwMakeContextCurrent(window_);

  }
  else
  {
    //printf("PWindow makeContextCurrent: THREAD CURRENT\n");
    glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
    glfwMakeContextCurrent(thread_);
    // We do it here because until we don't change the context,
    // we don't activate depth to thread context.
    glEnable(GL_DEPTH_TEST);
  }*/
}

void PastorseWindow::frameTime(){
  float currentFrame = glfwGetTime();
  delta_time_ = currentFrame - last_frame_;
  last_frame_ = currentFrame;
}

float PastorseWindow::getDeltaTime(){
  return delta_time_;
}

PastorseInput::PastorseInput(){
 
}

bool PastorseInput::getKey(Key key){

  /*if (glfwGetKey(thread_, key) == GLFW_PRESS){
    return true;
  }
  return false;*/

  ///Prueba!!!!!!
  if (glfwGetKey(window_, key) == GLFW_PRESS){
    return true;
  }
  return false;



}

bool PastorseInput::getSpecialKey(Special_Key key){

	/*if (glfwGetKey(thread_, key) == GLFW_PRESS){
		return true;
	}
	return false;*/

  ///Prueba!!!!!!

  if (glfwGetKey(window_, key) == GLFW_PRESS){
    return true;
  }
  return false;
}