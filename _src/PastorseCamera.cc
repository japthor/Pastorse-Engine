 #include "PastorseCamera.h"
#include <stdio.h>
PastorseCamera::PastorseCamera() {
	projection_ = glm::mat4(1.0f);
	view_ = glm::mat4(1.0f);
}

void PastorseCamera::setLookUp(glm::vec3 position, glm::vec3 target, glm::vec3 up){
	view_ = glm::lookAt(position, target, up);
}

void PastorseCamera::setLookProjection(float32 fov, float32 aspect_ratio, float32 znear, float32 zfar){
	projection_ = glm::perspective(fov, aspect_ratio, znear, zfar);
}

void PastorseCamera::draw(int32 program){
	//printf("PCamera Draw: program - %d\n", program);
	int32 model_location_ = glGetUniformLocation(program, "cam_model");
	int32 view_location_ = glGetUniformLocation(program, "view");
	int32 projection_location_ = glGetUniformLocation(program, "projection");

	glUniformMatrix4fv(model_location_, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
	glUniformMatrix4fv(view_location_, 1, GL_FALSE, glm::value_ptr(view_));
	glUniformMatrix4fv(projection_location_, 1, GL_FALSE, glm::value_ptr(projection_));
}

