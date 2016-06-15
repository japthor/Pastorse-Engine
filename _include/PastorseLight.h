#ifndef INCLUDE_PASTORSELIGHT_H_
#define INCLUDE_PASTORSELIGHT_H_ 1

#include "PastorseGPU.h"
#include "PastorseNode.h"
#include "glm.hpp"

enum PointLightLinear{
	kPointLightLinear_07,
	kPointLightLinear_035,
	kPointLightLinear_022,
	kPointLightLinear_014,
	kPointLightLinear_009,
	kPointLightLinear_007,
	kPointLightLinear_0045,
	kPointLightLinear_0027,
	kPointLightLinear_0022,
	kPointLightLinear_0014,
	kPointLightLinear_0007,
	kPointLightLinear_00014

};

enum PointLightQuadratic{
	kPointLightQuadratic_18,
	kPointLightQuadratic_044,
	kPointLightQuadratic_020,
	kPointLightQuadratic_007,
	kPointLightQuadratic_0032,
	kPointLightQuadratic_0017,
	kPointLightQuadratic_00075,
	kPointLightQuadratic_00028,
	kPointLightQuadratic_00019,
	kPointLightQuadratic_00007,
	kPointLightQuadratic_00002,
	kPointLightQuadratic_0000007

};

enum SpotLightCutOff{
	kSpotLightCutOff_25,
	kSpotLightCutOff_35,
	kSpotLightCutOff_125,
	kSpotLightCutOff_175
};


class PastorseLight : public PastorseNode{
public:

	~PastorseLight(){};
	PastorseLight();

  /// Directional
  void setDirectionalLightColor(glm::vec3 color);
  glm::vec3 getDirectionalLightColor();

  void setDirectionalLightDirection(glm::vec3 dir);
  glm::vec3 getDirectionalLightDirection();

  /// PointLight
  void setPointLightConstant(float32 constant);
  float32 getPointLighConstant();

  void setPointLightLinear(PointLightLinear linear);
  float32 getPointLightLinear();

  void setPointLightQuadratic(PointLightQuadratic quadratic);
  float32 getPointLightQuadratic();

  void setPointLightPosition(glm::vec3 pos);
  glm::vec3 getPointLightPosition();

  void setPointLightColor(glm::vec3 color);
  glm::vec3 getPointLightColor();


  /// SpotLight
  void setSpotLightInnerAngle(SpotLightCutOff angle, int number);
  float32 getSpotLightInnerAngle(int number);

  void setSpotLightOuterAngle(SpotLightCutOff angle, int number);
  float32 getSpotLightOuterAngle(int number);

  void setSpotLightDirection(glm::vec3 dir, int number);
  glm::vec3 getSpotLightDirection(int number);

  void setSpotLightPosition(glm::vec3 pos, int number);
  glm::vec3 getSpotLightPosition(int number);

  void setSpotLightColor(glm::vec3 pos, int number);
  glm::vec3 getSpotLightColor(int number);

  void setSpotLightConstant(float32 constant, int number);
  float32 getSpotLighConstant(int number);

  void setSpotLightLinear(PointLightLinear linear, int number);
  float32 getSpotLightLinear(int number);

  void setSpotLightQuadratic(PointLightQuadratic quadratic, int number);
  float32 getSpotLightQuadratic(int number);

  virtual void visitNode(std::shared_ptr<PastorseNode> node){};
  virtual void updateNode(std::shared_ptr<PastorseNode> node){};

private:
	PastorseLight(const PastorseLight&);
	PastorseLight& operator= (const PastorseLight&);

	/// Directional
	glm::vec3 directional_color_;
	glm::vec3 directional_direction_;

	/// PointLight
	float32 pointlight_constant_;
	float32 pointlight_linear_;
	float32 pointlight_quadratic_;
	glm::vec3 pointlight_position_;
	glm::vec3 pointlight_color_;


	/// SpotLight
	float32 spotlight_inner_angle_[3];
	float32 spotlight_outer_angle_[3];
	float32 spotlight_constant_[3];
	float32 spotlight_linear_[3];
	float32 spotlight_quadratic_[3];

	glm::vec3 spotlight_direction_[3];
	glm::vec3 spotlight_position_[3];
	glm::vec3 spotlight_color_[3];


};

#endif