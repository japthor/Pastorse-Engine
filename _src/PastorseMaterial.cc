#include "PastorseMaterial.h"

PastorseMaterial::PastorseMaterial(){
	color_.x = 0.0f;
	color_.y = 0.0f;
	color_.z = 0.0f;

}

void PastorseMaterial::initMaterial(ShaderType type){
	PastorseGPU* GPUInstance = nullptr;
	GPUInstance = PastorseGPU::getInstance();

    GPUInstance->init(type, &program_);
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


void PastorseMaterial::setTexture(std::shared_ptr<PastorseTexture> texture){
  texture_prueba_ = texture;
}

void PastorseMaterial::setLight(std::shared_ptr<PastorseLight> light){
  light_ = light;
}

void PastorseMaterial::draw(glm::mat4 view, glm::mat4 projection, glm::vec3 camera_position, int camera, glm::mat4 shadow_view, glm::mat4 shadow_projection, glm::mat4 shadow_view2, glm::mat4 shadow_projection2){
   PastorseGPU* GPUInstance = nullptr;
   GPUInstance = PastorseGPU::getInstance();

   GPUInstance->useProgram(&program_);
   GPUInstance->setColor(color_,&program_);

   if (camera == 0){
	   GPUInstance->setCameraProgram(&program_, view, projection);
	   GPUInstance->setCameraProgramShadow(&program_, shadow_view, shadow_projection, shadow_view2, shadow_projection2);
	   GPUInstance->setPositionCamera(camera_position, &program_);
   }
   else{
	   // Prueba Shadow 
       GPUInstance->setCameraProgram(&program_, view, projection);
	   GPUInstance->setPositionCamera(camera_position, &program_);
   }

  if (!texture_prueba_){
    //printf("\nNo texture");
  }
  else{
    uint32 texture = texture_prueba_->getTexture();
    GPUInstance->setTexture("texture_",&texture, program_);
  }

  if (!texture_shadow_){

  }
  else{
    uint32 texture_shadow = texture_shadow_->getTexture();
    GPUInstance->setTexture("texture_shadow",&texture_shadow, program_);
  }

  if (!texture_shadow_2){

  }
  else{
	  uint32 texture_shadow = texture_shadow_2->getTexture();
	  GPUInstance->setTexture("texture_shadow_2", &texture_shadow, program_);
  }

  if (!light_){
    //printf("\nNo Light");
  }
  else{

	/// Directional
	glm::vec3 directional_light_color = light_->getDirectionalLightColor();
	GPUInstance->setDirectionalLightColor(directional_light_color, program_);

    glm::vec3 directional_light_direction = light_->getDirectionalLightDirection();
	GPUInstance->setDirectionalLightDirection(directional_light_direction, program_);


	/// PointLight
	float32 pointlight_constant = light_->getPointLighConstant();
	GPUInstance->setPointLightConstant(pointlight_constant, program_);

	float32 pointlight_linear = light_->getPointLightLinear();
	GPUInstance->setPointLightLinear(pointlight_linear, program_);

	float32 pointlight_quadratic = light_->getPointLightQuadratic();
	GPUInstance->setPointLightQuadratic(pointlight_quadratic, program_);

	glm::vec3 pointlight_position = light_->getPointLightPosition();
	GPUInstance->setPointLightPosition(pointlight_position, program_);

	glm::vec3 pointlight_color = light_->getPointLightColor();
	GPUInstance->setPointLightColor(pointlight_color, program_);

	/// SpotLight

	float32 spotlight_inner_angle = light_->getSpotLightInnerAngle(0);
	GPUInstance->setSpotLightInnerAngle(spotlight_inner_angle, program_,0);

	float32 spotlight_inner_angle1 = light_->getSpotLightInnerAngle(1);
	GPUInstance->setSpotLightInnerAngle(spotlight_inner_angle1, program_,1);

	float32 spotlight_inner_angle2 = light_->getSpotLightInnerAngle(2);
	GPUInstance->setSpotLightInnerAngle(spotlight_inner_angle2, program_,2);
	
	//

	float32 spotlight_outer_angle_ = light_->getSpotLightOuterAngle(0);
	GPUInstance->setSpotLightOuterAngle(spotlight_outer_angle_, program_,0);

	float32 spotlight_outer_angle_1 = light_->getSpotLightOuterAngle(1);
	GPUInstance->setSpotLightOuterAngle(spotlight_outer_angle_1, program_,1);

	float32 spotlight_outer_angle_2 = light_->getSpotLightOuterAngle(2);
	GPUInstance->setSpotLightOuterAngle(spotlight_outer_angle_2, program_,2);

	//

	glm::vec3 spotlight_direction = light_->getSpotLightDirection(0);
	GPUInstance->setSpotLightDirection(spotlight_direction, program_,0);

	glm::vec3 spotlight_direction_1 = light_->getSpotLightDirection(1);
	GPUInstance->setSpotLightDirection(spotlight_direction_1, program_,1);

	glm::vec3 spotlight_direction_2 = light_->getSpotLightDirection(2);
	GPUInstance->setSpotLightDirection(spotlight_direction_2, program_,2);

	//

	glm::vec3 spotlight_position_1 = light_->getSpotLightPosition(0);
	GPUInstance->setSpotLightPosition(spotlight_position_1, program_,0);

	glm::vec3 spotlight_position_2 = light_->getSpotLightPosition(1);
	GPUInstance->setSpotLightPosition(spotlight_position_2, program_,1);

	glm::vec3 spotlight_position_3 = light_->getSpotLightPosition(2);
	GPUInstance->setSpotLightPosition(spotlight_position_3, program_,2);

	//

	glm::vec3 spotlight_color_1 = light_->getSpotLightColor(0);
	GPUInstance->setSpotLightColor(spotlight_color_1, program_,0);

	glm::vec3 spotlight_color_2 = light_->getSpotLightColor(1);
	GPUInstance->setSpotLightColor(spotlight_color_2, program_,1);

	glm::vec3 spotlight_color_3 = light_->getSpotLightColor(2);
	GPUInstance->setSpotLightColor(spotlight_color_3, program_,2);

	//

	float32 spotlight_constant = light_->getSpotLighConstant(0);
	GPUInstance->setSpotLightConstant(spotlight_constant, program_,0);

	float32 spotlight_constant_1 = light_->getSpotLighConstant(1);
	GPUInstance->setSpotLightConstant(spotlight_constant_1, program_,1);

	float32 spotlight_constant_2 = light_->getSpotLighConstant(2);
	GPUInstance->setSpotLightConstant(spotlight_constant_2, program_,2);

	//

	float32 spotlight_linear = light_->getSpotLightLinear(0);
	GPUInstance->setSpotLightLinear(spotlight_linear, program_,0);

	float32 spotlight_linear_1 = light_->getSpotLightLinear(1);
	GPUInstance->setSpotLightLinear(spotlight_linear_1, program_,1);

	float32 spotlight_linear_2 = light_->getSpotLightLinear(2);
	GPUInstance->setSpotLightLinear(spotlight_linear_2, program_,2);

	//

	float32 spotlight_quadratic = light_->getSpotLightQuadratic(0);
	GPUInstance->setSpotLightQuadratic(spotlight_quadratic, program_,0);

	float32 spotlight_quadratic_1 = light_->getSpotLightQuadratic(1);
	GPUInstance->setSpotLightQuadratic(spotlight_quadratic_1, program_,1);

	float32 spotlight_quadratic_2 = light_->getSpotLightQuadratic(2);
	GPUInstance->setSpotLightQuadratic(spotlight_quadratic_2, program_,2);
  }
}

uint32 PastorseMaterial::getProgram(){
  return program_;
}

void PastorseMaterial::setTextureShadow(std::shared_ptr<PastorseTexture> texture){
  texture_shadow_ = texture;
}

void PastorseMaterial::setTextureShadow2(std::shared_ptr<PastorseTexture> texture){
	texture_shadow_2 = texture;
}








