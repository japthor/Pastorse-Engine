#include "PastorseCamera.h"
#include "PastorseGPU.h"
#include <stdio.h>
 
PastorseCamera::PastorseCamera() {
	projection_ = glm::mat4(1.0f);
	view_ = glm::mat4(1.0f);
}

void PastorseCamera::setLookUp(glm::vec3 position, glm::vec3 target, glm::vec3 up){
	view_ = glm::lookAt(position,target, up);
	position_ = position;
}

void PastorseCamera::setOrthoProjection(float32 znear, float32 zfar){
  projection_ = glm::ortho(-60.0f, 60.0f, -60.0f, 60.0f, znear, zfar);
}

void PastorseCamera::setLookProjection(float32 fov, float32 aspect_ratio, float32 znear, float32 zfar){
	projection_ = glm::perspective(fov * (3.14f /180.0f), aspect_ratio, znear, zfar);
}

glm::mat4 PastorseCamera::getProjection(){
  return projection_;
}

glm::mat4 PastorseCamera::getView(){
  return view_;
}

glm::vec3 PastorseCamera::getCameraPosition(){
  return position_;
}