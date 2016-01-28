#include "PastorseGeometry.h"

PastorseGeometry::PastorseGeometry(){
	vao_ = 0;
	vbo_normales_ = 0;
	vbo_UV_ = 0;
	vbo_vertices_ = 0;
	ebo_ = 0;
	name_ = nullptr;
}

void PastorseGeometry::createCube(char8* name, float32 scale){
	PastorseGPU* GPUInstance = nullptr;
	GPUInstance = PastorseGPU::getInstance();
	GPUInstance->createCube(scale, &vao_, &vbo_vertices_, &vbo_normales_, &vbo_UV_, &ebo_, &index_);

    name_ = name;
}

void PastorseGeometry::createPlane(float32 scale, float32 x, float32 y, float32 z){
	PastorseGPU* GPUInstance = nullptr;
	GPUInstance = PastorseGPU::getInstance();
	GPUInstance->createPlane(scale, &vao_, &vbo_vertices_, &vbo_normales_, &vbo_UV_, &ebo_, x, y, z);
}

void PastorseGeometry::draw(glm::mat4 model){
	PastorseGPU* GPUInstance = nullptr;
	GPUInstance = PastorseGPU::getInstance();
	GPUInstance->setTransformation(model);
	GPUInstance->draw(&vao_, &ebo_, &vbo_vertices_, &vbo_normales_, &vbo_UV_, &index_);
}

void PastorseGeometry::geometryOBJ(void* shapes){
	PastorseGPU* GPUInstance = nullptr;
	GPUInstance = PastorseGPU::getInstance();
	GPUInstance->loadOBJ(&vao_, &vbo_vertices_, &vbo_normales_, &vbo_UV_, &ebo_,&index_, shapes);
}

void PastorseGeometry::deleteBuffers(){
	PastorseGPU* GPUInstance = nullptr;
	GPUInstance = PastorseGPU::getInstance();

	GPUInstance->delete_buffers(&vao_, &vbo_vertices_, &vbo_normales_, &vbo_UV_, &ebo_);
}




