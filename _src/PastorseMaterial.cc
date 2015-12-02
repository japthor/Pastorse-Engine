#include "PastorseMaterial.h"

PastorseMaterial::PastorseMaterial(){
	color_.x = 0.0f;
	color_.y = 0.0f;
	color_.z = 0.0f;

	texture_ = 0;
}

void PastorseMaterial::create_material(){
	PastorseGPU* GPUInstance = nullptr;
	GPUInstance = PastorseGPU::getInstance();

	GPUInstance->init();
}

glm::vec3 PastorseMaterial::get_color(){
	return color_;
}

void PastorseMaterial::set_color(glm::vec3 color){
	color_ = color;
}

void PastorseMaterial::upload_texture(const char8* location){
	PastorseGPU* GPUInstance = nullptr;
	GPUInstance = PastorseGPU::getInstance();

	GPUInstance->upload_texture_prueba(location, &texture_);
}

void PastorseMaterial::prepare_draw(){
	PastorseGPU* GPUInstance = nullptr;
	GPUInstance = PastorseGPU::getInstance();

	GPUInstance->set_color(color_);
	GPUInstance->set_texture(&texture_);
}





