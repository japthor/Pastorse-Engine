#include "PastorseRenderToTexture.h"
#include "PastorseGPU.h"

PastorseRenderToTexture::PastorseRenderToTexture(){
  
}

void PastorseRenderToTexture::createRenderToTexture(ShaderType type){
  frame_buffer_ = CREATE_MAKE_SHARED_PTR(PastorseFrameBuffer);
  frame_buffer_->createFrameBuffer();

  geometry_ = CREATE_MAKE_SHARED_PTR(PastorseGeometry);
  geometry_->createPlane(1.0f);

  texture_ = CREATE_MAKE_SHARED_PTR(PastorseTexture);
  texture_->loadTexture();

  depth_texture_ = CREATE_MAKE_SHARED_PTR(PastorseTexture);
  depth_texture_->loadDepthTexture();

  material_ = CREATE_MAKE_SHARED_PTR(PastorseMaterial);
  material_->initMaterial(type);

  frame_buffer_->BindFrameBuffer();
  frame_buffer_->AttachFrameBuffer(texture_->getTexture(), depth_texture_->getTexture());
}

std::shared_ptr<PastorseFrameBuffer> PastorseRenderToTexture::getFrameBuffer(){
  return frame_buffer_;
}

void PastorseRenderToTexture::draw(glm::mat4 view, glm::mat4 projection, glm::vec3 camera_position){
  material_->draw(view, projection, camera_position,0);
  texture_->setTexture(material_->getProgram());
  geometry_->draw(glm::mat4(1.0f), material_->getProgram());
}

void PastorseRenderToTexture::drawDepth(glm::mat4 view, glm::mat4 projection, glm::vec3 camera_position){
  material_->draw(view, projection, camera_position, 0);
  depth_texture_->setTexture(material_->getProgram());
  geometry_->draw(glm::mat4(1.0f), material_->getProgram());
}

