#ifndef INCLUDE_PASTORSEMATERIAL_H_
#define INCLUDE_PASTORSEMATERIAL_H_ 1

#include "PastorseGPU.h"
#include "PastorseTexture.h"
#include "PastorseLight.h"
#include <memory>
#include "glm.hpp"

class PastorseMaterial
{
public:
	~PastorseMaterial(){};

	/// Creates the Shader
  void initMaterial(ShaderType type);

	/// Gets the Material Color
	glm::vec3 getColor();

	/**
	* Sets the material color
	*
	* @param color Color vector
	*/
	void setColor(glm::vec3 color);

	/// For the exam, don't use it.
	void setColorPruebaVal(glm::vec3 color, int option);

	/**
	* Sets the material color
	*
	* @param r R
	* @param g G
	* @param b B
	* @param option This was for the exam, just put 0.
	*/
	void setColor(float r, float g, float b);

  void setTexture(std::shared_ptr<PastorseTexture> texture);
    

  void setLight(std::shared_ptr<PastorseLight> light);

	/// Sets the Color and the Texure in the GPU (Don't use it)
  void draw(glm::mat4 view, glm::mat4 projection, glm::vec3 camera_position, int camera, glm::mat4 shadow_view = glm::mat4(1.0f), glm::mat4 shadow_projection = glm::mat4(1.0f), glm::mat4 shadow_view2 = glm::mat4(1.0f), glm::mat4 shadow_projection2 = glm::mat4(1.0f));
   
  uint32 getProgram();

  /// Shadow
  void setTextureShadow(std::shared_ptr<PastorseTexture> texture);
  void setTextureShadow2(std::shared_ptr<PastorseTexture> texture);


private:
  friend class PastorseEngine;
  friend class PastorseRenderToTexture;
  PastorseMaterial(const PastorseMaterial&);
  PastorseMaterial& operator= (const PastorseMaterial&);
  PastorseMaterial();

  glm::vec3 color_;
  glm::vec3 color_PruebaValidacion_;

  std::shared_ptr<PastorseTexture> texture_prueba_;
  std::shared_ptr<PastorseLight> light_;

  uint32 program_;

  /// Shadow
  std::shared_ptr<PastorseTexture> texture_shadow_;
  std::shared_ptr<PastorseTexture> texture_shadow_2;
};

#endif