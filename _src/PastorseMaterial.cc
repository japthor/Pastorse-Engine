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

void PastorseMaterial::setColor(glm::vec3 color, int option){
	color_ = color;
	option_ = option;
}

void PastorseMaterial::setColorPruebaVal(glm::vec3 color, int option){
	color_ = color;
	option_ = option;
}

void PastorseMaterial::setColor(float r, float g, float b, int option){
	color_.r = r;
	color_.g = g;
	color_.b = b;

	color_PruebaValidacion_.r = r;
	color_PruebaValidacion_.g = g;
	color_PruebaValidacion_.b = b;
	option_ = option;
}

void PastorseMaterial::uploadTexture(const char8* location){
	PastorseGPU* GPUInstance = nullptr;
	GPUInstance = PastorseGPU::getInstance();

	GPUInstance->uploadTexture(location, &texture_);
}


void PastorseMaterial::draw(){
	PastorseGPU* GPUInstance = nullptr;
	GPUInstance = PastorseGPU::getInstance();

	GPUInstance->setColor(color_,option_);
	GPUInstance->setColorPV(color_PruebaValidacion_, option_);
	GPUInstance->setTexture(&texture_);
}








