#include "PastorseEngine.h"

PastorseEngine::PastorseEngine(){

}

PastorseEngine::~PastorseEngine(){
	if (thread_render_){
		thread_render_->detach();
		thread_render_ = nullptr;
	}
}

void PastorseEngine::init(int window_width, int window_height, std::string name_engine){
	window_ = CREATE_MAKE_SHARED_PTR(PastorseWindow);
	window_->initWindow(window_width, window_height, name_engine);
	GPU_Instance_ = PastorseGPU::getInstance();

	thread_render_ = new std::thread(&PastorseEngine::draw, this);
}

std::shared_ptr<PastorseWindow> PastorseEngine::getWindow(){
	return window_;
}

std::shared_ptr<PastorseMaterial> PastorseEngine::createMaterial(){
	std::shared_ptr<PastorseMaterial> material;
	material = CREATE_MAKE_SHARED_PTR(PastorseMaterial);
	material_.push_back(material);

	return material;

}

std::shared_ptr<PastorseGeometry> PastorseEngine::createGeometry(){
	std::shared_ptr<PastorseGeometry> geometry;
	geometry = CREATE_MAKE_SHARED_PTR(PastorseGeometry);
	geometry_.push_back(geometry);

	return geometry;

}

std::shared_ptr<PastorseActor> PastorseEngine::createActor(){
	std::shared_ptr<PastorseActor> actor;
	actor = CREATE_MAKE_SHARED_PTR(PastorseActor);
	actor_.push_back(actor);

	return actor;

}

std::shared_ptr<PastorseCamera> PastorseEngine::createCamera(){
	std::shared_ptr<PastorseCamera> camera;
	camera = CREATE_MAKE_SHARED_PTR(PastorseCamera);
	camera_.push_back(camera);

	return camera;

}

std::unique_ptr<PastorseInput> PastorseEngine::createInput(){
	std::unique_ptr<PastorseInput> input;
	input = CREATE_UNIQUE_PTR(PastorseInput);

	return input;

}

void PastorseEngine::draw(){
	
	while (!window_->isClosedWindow()){

    window_->makeContextCurrent(1);
    window_->setColor(0.8f, 0.2f, 0.2f, 1.0f);
		
		for (unsigned int i = 0; i < actor_.size(); i++){
      
			actor_[i]->draw();
		}

		for (unsigned int f = 0; f < camera_.size(); f++){
			camera_[f]->draw(GPU_Instance_->get_program());
		}
		window_->swapBuffers(1);
	}
}
