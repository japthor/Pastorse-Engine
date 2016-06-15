#include "PastorseLight.h"

PastorseLight::PastorseLight(){
	pointlight_constant_ = 1.0f;
	pointlight_linear_ = 0.09f;
	pointlight_quadratic_ = 0.032f;

	spotlight_inner_angle_[0] = 12.5f;
	spotlight_outer_angle_[0] = 25.0f;

	spotlight_constant_[0] = 1.0f;
	spotlight_linear_[0] = 0.001f;
	spotlight_quadratic_[0] = 0.0032f;

	spotlight_inner_angle_[1] = 12.5f;
	spotlight_outer_angle_[1] = 25.0f;

	spotlight_constant_[1] = 1.0f;
	spotlight_linear_[1] = 0.001f;
	spotlight_quadratic_[1] = 0.0032f;

	spotlight_inner_angle_[2] = 12.5f;
	spotlight_outer_angle_[2] = 25.0f;

	spotlight_constant_[2] = 1.0f;
	spotlight_linear_[2] = 0.001f;
	spotlight_quadratic_[2] = 0.0032f;

}

void PastorseLight::setDirectionalLightColor(glm::vec3 color){
	directional_color_ = color;
}

glm::vec3 PastorseLight::getDirectionalLightColor(){
	return directional_color_;
}

void PastorseLight::setDirectionalLightDirection(glm::vec3 dir){
	directional_direction_ = dir;
}

glm::vec3 PastorseLight::getDirectionalLightDirection(){
	return directional_direction_;
}

/// PointLight

void PastorseLight::setPointLightConstant(float32 constant){
	pointlight_constant_ = constant;
}

float32 PastorseLight::getPointLighConstant(){
	return pointlight_constant_;
}

void PastorseLight::setPointLightLinear(PointLightLinear linear){
	if (linear == kPointLightLinear_07){
		pointlight_linear_ = 0.7f;
	}else if (linear == kPointLightLinear_035){
		pointlight_linear_ = 0.35f;
	}else if (linear == kPointLightLinear_022){
		pointlight_linear_ = 0.22f;
	}else if (linear == kPointLightLinear_014){
		pointlight_linear_ = 0.14f;
	}else if (linear == kPointLightLinear_009){
		pointlight_linear_ = 0.09f;
	}else if (linear == kPointLightLinear_007){
		pointlight_linear_ = 0.07f;
	}else if (linear == kPointLightLinear_0045){
		pointlight_linear_ = 0.045f;
	}else if (linear == kPointLightLinear_0027){
		pointlight_linear_ = 0.027f;
	}else if (linear == kPointLightLinear_0022){
		pointlight_linear_ = 0.022f;
	}else if (linear == kPointLightLinear_0014){
		pointlight_linear_ = 0.014f;
	}else if (linear == kPointLightLinear_0007){
		pointlight_linear_ = 0.007f;
	}else if (linear == kPointLightLinear_00014){
		pointlight_linear_ = 0.0015f;
	}
}

float32 PastorseLight::getPointLightLinear(){
	return pointlight_linear_;
}

void PastorseLight::setPointLightQuadratic(PointLightQuadratic quadratic){
	if (quadratic == kPointLightQuadratic_18){
		pointlight_quadratic_ = 1.8f;
	}else if (quadratic == kPointLightQuadratic_044){
		pointlight_quadratic_ = 0.44f;
	}else if (quadratic == kPointLightQuadratic_020){
		pointlight_quadratic_ = 0.20f;
	}else if (quadratic == kPointLightQuadratic_007){
		pointlight_quadratic_ = 0.07f;
	}else if (quadratic == kPointLightQuadratic_0032){
		pointlight_quadratic_ = 0.032f;
	}else if (quadratic == kPointLightQuadratic_0017){
		pointlight_quadratic_ = 0.017f;
	}else if (quadratic == kPointLightQuadratic_00075){
		pointlight_quadratic_ = 0.0075f;
	}else if (quadratic == kPointLightQuadratic_00028){
		pointlight_quadratic_ = 0.0028f;
	}else if (quadratic == kPointLightQuadratic_00019){
		pointlight_quadratic_ = 0.0019f;
	}else if (quadratic == kPointLightQuadratic_00007){
		pointlight_quadratic_ = 0.0007f;
	}else if (quadratic == kPointLightQuadratic_00002){
		pointlight_quadratic_ = 0.0002f;
	}else if (quadratic == kPointLightQuadratic_0000007){
		pointlight_quadratic_ = 0.000007f;
	}
}

float32 PastorseLight::getPointLightQuadratic(){
	return pointlight_quadratic_;
}

void PastorseLight::setPointLightPosition(glm::vec3 pos){
	pointlight_position_ = pos;
}

glm::vec3 PastorseLight::getPointLightPosition(){
	return pointlight_position_;
}

void PastorseLight::setPointLightColor(glm::vec3 color){
	pointlight_color_ = color;
}

glm::vec3 PastorseLight::getPointLightColor(){
	return pointlight_color_;
}

/// SpotLight

void PastorseLight::setSpotLightInnerAngle(SpotLightCutOff angle, int32 number){
	if (angle == kSpotLightCutOff_25){
		spotlight_inner_angle_[number] = 25.0f;
	}else if (angle == kSpotLightCutOff_125){
		spotlight_inner_angle_[number] = 12.5f;
	}
}

float32 PastorseLight::getSpotLightInnerAngle(int32 number){
	return spotlight_inner_angle_[number];
}

void PastorseLight::setSpotLightOuterAngle(SpotLightCutOff angle, int32 number){
	if (angle == kSpotLightCutOff_175){
		spotlight_outer_angle_[number] = 17.5f;
	}else if (angle == kSpotLightCutOff_35){
		spotlight_outer_angle_[number] = 35.0f;
	}
}

float32 PastorseLight::getSpotLightOuterAngle(int32 number){
	return spotlight_outer_angle_[number];
}

void PastorseLight::setSpotLightDirection(glm::vec3 dir, int32 number){
	spotlight_direction_[number] = dir;
}

glm::vec3 PastorseLight::getSpotLightDirection(int32 number){
	return spotlight_direction_[number];
}

void PastorseLight::setSpotLightPosition(glm::vec3 pos, int32 number){
	spotlight_position_[number] = pos;
}

glm::vec3 PastorseLight::getSpotLightPosition(int32 number){
	return spotlight_position_[number];
}

void PastorseLight::setSpotLightColor(glm::vec3 color, int32 number){
	spotlight_color_[number] = color;
}

glm::vec3 PastorseLight::getSpotLightColor(int32 number){
	return spotlight_color_[number];
}

void PastorseLight::setSpotLightConstant(float32 constant, int32 number){
	spotlight_constant_[number] = constant;
}

float32 PastorseLight::getSpotLighConstant(int32 number){
	return spotlight_constant_[number];
}

void PastorseLight::setSpotLightLinear(PointLightLinear linear, int32 number){
	if (linear == kPointLightLinear_07){
		spotlight_linear_[number] = 0.7f;
	}
	else if (linear == kPointLightLinear_035){
		spotlight_linear_[number] = 0.35f;
	}
	else if (linear == kPointLightLinear_022){
		spotlight_linear_[number] = 0.22f;
	}
	else if (linear == kPointLightLinear_014){
		spotlight_linear_[number] = 0.14f;
	}
	else if (linear == kPointLightLinear_009){
		spotlight_linear_[number] = 0.09f;
	}
	else if (linear == kPointLightLinear_007){
		spotlight_linear_[number] = 0.07f;
	}
	else if (linear == kPointLightLinear_0045){
		spotlight_linear_[number] = 0.045f;
	}
	else if (linear == kPointLightLinear_0027){
		spotlight_linear_[number] = 0.027f;
	}
	else if (linear == kPointLightLinear_0022){
		spotlight_linear_[number] = 0.022f;
	}
	else if (linear == kPointLightLinear_0014){
		spotlight_linear_[number] = 0.014f;
	}
	else if (linear == kPointLightLinear_0007){
		spotlight_linear_[number] = 0.007f;
	}
	else if (linear == kPointLightLinear_00014){
		spotlight_linear_[number] = 0.0015f;
	}
}

float32 PastorseLight::getSpotLightLinear(int32 number){
	return spotlight_linear_[number];
}

void PastorseLight::setSpotLightQuadratic(PointLightQuadratic quadratic, int32 number){
	if (quadratic == kPointLightQuadratic_18){
		spotlight_quadratic_[number] = 1.8f;
	}
	else if (quadratic == kPointLightQuadratic_044){
		spotlight_quadratic_[number] = 0.44f;
	}
	else if (quadratic == kPointLightQuadratic_020){
		spotlight_quadratic_[number] = 0.20f;
	}
	else if (quadratic == kPointLightQuadratic_007){
		spotlight_quadratic_[number] = 0.07f;
	}
	else if (quadratic == kPointLightQuadratic_0032){
		spotlight_quadratic_[number] = 0.032f;
	}
	else if (quadratic == kPointLightQuadratic_0017){
		spotlight_quadratic_[number] = 0.017f;
	}
	else if (quadratic == kPointLightQuadratic_00075){
		spotlight_quadratic_[number] = 0.0075f;
	}
	else if (quadratic == kPointLightQuadratic_00028){
		spotlight_quadratic_[number] = 0.0028f;
	}
	else if (quadratic == kPointLightQuadratic_00019){
		spotlight_quadratic_[number] = 0.0019f;
	}
	else if (quadratic == kPointLightQuadratic_00007){
		spotlight_quadratic_[number] = 0.0007f;
	}
	else if (quadratic == kPointLightQuadratic_00002){
		spotlight_quadratic_[number] = 0.0002f;
	}
	else if (quadratic == kPointLightQuadratic_0000007){
		spotlight_quadratic_[number] = 0.000007f;
	}
}

float32 PastorseLight::getSpotLightQuadratic(int32 number){
	return spotlight_quadratic_[number];
}