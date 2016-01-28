#ifndef INCLUDE_PASTORSEMATERIAL_H_
#define INCLUDE_PASTORSEMATERIAL_H_ 1

#include "PastorseGPU.h"
#include "glm.hpp"

class PastorseMaterial
{
public:
	PastorseMaterial();
	~PastorseMaterial(){};

	/// Creates the Shader
	void initMaterial();

	/// Gets the Material Color
	glm::vec3 getColor();

	/**
	* Sets the material color
	*
	* @param color Color vector
	*/
	void setColor(glm::vec3 color);

	/**
	* Sets the material color
	*
	* @param r R
	* @param g G
	* @param b B
	*/
	void setColor(float r, float g, float b);

	/**
	* Gives to the Material a Texture.
	*
	* @param location location of the texture.
	*/
	void uploadTexture(const char8* location);

	/// Sets the Color and the Texure in the GPU (Don't use it)
	void draw();

private:
	glm::vec3 color_;
	uint32 texture_;
};

#endif