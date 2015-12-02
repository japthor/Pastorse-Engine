#include "PastorseGeometry.h"

PastorseGeometry::PastorseGeometry(){
	vao_ = 0;
	vbo_ = 0;
	ebo_ = 0;
  name_ = nullptr;
}

void PastorseGeometry::create_cube(char8* name, float32 scale){
	PastorseGPU* GPUInstance = nullptr;
	GPUInstance = PastorseGPU::getInstance();
	GPUInstance->create_cube(scale, &vao_, &vbo_, &ebo_);

  name_ = name;
}

void PastorseGeometry::draw(glm::mat4 model){
	PastorseGPU* GPUInstance = nullptr;
	GPUInstance = PastorseGPU::getInstance();
  GPUInstance->set_transformation_to_draw(model);
	GPUInstance->draw(&vao_, &ebo_, &vbo_);
}

void PastorseGeometry::create_plane(float32 scale, float32 x, float32 y, float32 z){
	PastorseGPU* GPUInstance = nullptr;
	GPUInstance = PastorseGPU::getInstance();
	GPUInstance->create_plane(scale, &vao_, &vbo_, &ebo_,x,y,z);
}



