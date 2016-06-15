#include "PastorseEngine.h"

PastorseEngine::PastorseEngine(){
	activate_pp = false;
}

PastorseEngine::~PastorseEngine(){
	if (thread_render_){
		thread_render_->detach();
		thread_render_ = nullptr;
	}
}

PastorseEngine* PastorseEngine::getInstance(){
  static PastorseEngine* instance = nullptr;

  if (instance == nullptr){
    instance = new PastorseEngine;
  }

  return instance;
}

void PastorseEngine::init(int window_width, int window_height, std::string name_engine){
  window_ = CREATE_MAKE_SHARED_PTR(PastorseWindow);
  window_->initWindow(window_width, window_height, name_engine);

  input_ = CREATE_MAKE_SHARED_PTR(PastorseInput);

  GPU_Instance_ = PastorseGPU::getInstance();

  render_to_texture_ = CREATE_MAKE_SHARED_PTR(PastorseRenderToTexture);
  render_to_texture_->createRenderToTexture(kShaderType_RenderToTexture);

  render_to_texture_position_ = CREATE_MAKE_SHARED_PTR(PastorseRenderToTexture);
  render_to_texture_position_->createRenderToTexture(kShaderType_RenderToTexture);

  render_to_texture_position_2 = CREATE_MAKE_SHARED_PTR(PastorseRenderToTexture);
  render_to_texture_position_2->createRenderToTexture(kShaderType_RenderToTexture);

  post_process = CREATE_MAKE_SHARED_PTR(PastorseRenderToTexture);
  post_process->createRenderToTexture(kShaderType_RenderToTexture);

  post_process_2 = CREATE_MAKE_SHARED_PTR(PastorseRenderToTexture);
  post_process_2->createRenderToTexture(kShaderType_RenderToTextureRed);
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

std::shared_ptr<PastorseTexture> PastorseEngine::createTexture(){
  std::shared_ptr<PastorseTexture> texture;
  texture = CREATE_MAKE_SHARED_PTR(PastorseTexture);
  texture_.push_back(texture);

  return texture;
}

std::shared_ptr<PastorseLight> PastorseEngine::createLight(){
	std::shared_ptr<PastorseLight> light;
	light = CREATE_MAKE_SHARED_PTR(PastorseLight);
	light_.push_back(light);

	return light;
}

std::shared_ptr<PastorseInput> PastorseEngine::createInput(){
  return input_;
}

void PastorseEngine::draw(){

	///Directional Shadow
  render_to_texture_position_->getFrameBuffer()->BindFrameBuffer();
  window_->setColor(1.0f, 1.0f, 1.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glCullFace(GL_FRONT);

  for (unsigned int i = 0; i < actor_.size(); i++){
    actor_[i]->specialDraw(camera_[1]->getView(), camera_[1]->getProjection(), camera_[1]->getCameraPosition(),1);
  }
  glCullFace(GL_BACK);
  render_to_texture_position_->getFrameBuffer()->unBindFrameBuffer();

	/// Spotlight Shadow
	render_to_texture_position_2->getFrameBuffer()->BindFrameBuffer();
	window_->setColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_FRONT);

	for (unsigned int i = 0; i < actor_.size(); i++){
		actor_[i]->specialDraw(camera_[2]->getView(), camera_[2]->getProjection(), camera_[2]->getCameraPosition(), 2);
	}
	glCullFace(GL_BACK);
	render_to_texture_position_2->getFrameBuffer()->unBindFrameBuffer();

    //window_->setColor(0.1f, 0.3f, 0.4f, 1.0f);
    //render_to_texture_position_->draw(camera_[0]->getView(), camera_[0]->getProjection(), camera_[0]->getCameraPosition());
  
   render_to_texture_->getFrameBuffer()->BindFrameBuffer();
   window_->setColor(0.1f, 0.3f, 0.4f, 1.0f);
   glEnable(GL_DEPTH_TEST);

  for (unsigned int i = 0; i < actor_.size(); i++){
    actor_[i]->material_->setTextureShadow(render_to_texture_position_->depth_texture_);
	  actor_[i]->material_->setTextureShadow2(render_to_texture_position_2->depth_texture_);
	  actor_[i]->draw(camera_[0]->getView(), camera_[0]->getProjection(), camera_[0]->getCameraPosition(), camera_[1]->getView(), camera_[1]->getProjection(), camera_[2]->getView(), camera_[2]->getProjection());
  }

  
  render_to_texture_->getFrameBuffer()->unBindFrameBuffer();
  
   
  /// PostProcess
  post_process->getFrameBuffer()->BindFrameBuffer();
  window_->setColor(1.0, 1.0, 1.0,1.0);

  if (id_camera == 0){
    render_to_texture_->draw(camera_[0]->getView(), camera_[0]->getProjection(), camera_[0]->getCameraPosition());
    render_to_texture_->material_->draw(glm::mat4(1.0f), glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0);
  }else if (id_camera == 1){
    render_to_texture_position_->drawDepth(camera_[0]->getView(), camera_[0]->getProjection(), camera_[0]->getCameraPosition());
    render_to_texture_position_->material_->draw(glm::mat4(1.0f), glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0);
  }else if (id_camera == 2){
	  render_to_texture_position_2->drawDepth(camera_[0]->getView(), camera_[0]->getProjection(), camera_[0]->getCameraPosition());
    render_to_texture_position_2->material_->draw(glm::mat4(1.0f), glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0);
  }

  post_process->getFrameBuffer()->unBindFrameBuffer();

  if (activate_pp){
	  post_process_2->getFrameBuffer()->BindFrameBuffer();
	  
  }
  window_->setColor(1.0, 1.0, 1.0, 1.0);

  post_process->draw(camera_[0]->getView(), camera_[0]->getProjection(), camera_[0]->getCameraPosition());
  post_process->material_->draw(glm::mat4(1.0f), glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0);

  if (activate_pp){
	  post_process_2->getFrameBuffer()->unBindFrameBuffer();

	  window_->setColor(0.1f, 0.3f, 0.4f, 1.0f);

	  post_process_2->draw(camera_[0]->getView(), camera_[0]->getProjection(), camera_[0]->getCameraPosition());
	  post_process_2->material_->draw(glm::mat4(1.0f), glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0);
  }

  //render_to_texture_->texture_->setTexture(render_to_texture_->material_->getProgram());
   
  window_->swapBuffers(0);
}

