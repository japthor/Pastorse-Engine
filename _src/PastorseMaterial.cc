#include "PastorseMaterial.h"

PastorseMaterial::PastorseMaterial(){
	color_.x = 0.0f;
	color_.y = 0.0f;
	color_.z = 0.0f;

	texture_ = 0;
}

void PastorseMaterial::initMaterial(){
	PastorseGPU* GPUInstance = nullptr;
	GPUInstance = PastorseGPU::getInstance();

	GPUInstance->init();
}

glm::vec3 PastorseMaterial::getColor(){
	return color_;
}

void PastorseMaterial::setColor(glm::vec3 color){
	color_ = color;
}

void PastorseMaterial::setColor(float r, float g, float b){
	color_.r = r;
	color_.g = g;
	color_.b = b;
}

void PastorseMaterial::uploadTexture(const char8* location){
	PastorseGPU* GPUInstance = nullptr;
	GPUInstance = PastorseGPU::getInstance();

	GPUInstance->uploadTexture(location, &texture_);
}

void PastorseMaterial::draw(){
	PastorseGPU* GPUInstance = nullptr;
	GPUInstance = PastorseGPU::getInstance();

	GPUInstance->setColor(color_);
	GPUInstance->setTexture(&texture_);
}






