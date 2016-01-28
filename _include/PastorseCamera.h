#ifndef INCLUDE_PASTORSECAMERA_H_
#define INCLUDE_PASTORSECAMERA_H_ 1

#include "glm.hpp"
#include "gtc\matrix_transform.hpp"
#include "gtc\type_ptr.hpp"
#include "GL\glew.h"
#include "PastorseTypes.h"


class PastorseCamera
{
public:
	PastorseCamera();
	~PastorseCamera(){};

	/**
	* Creates the view of the camera
	*
	* @param position Position of the camera's viewpoint.
	* @param target  Where you are looking at.
	* @param up World's "upwards" direction.
	*/
	void setLookUp(glm::vec3 position, glm::vec3 target, glm::vec3 up);

	/**
	* Sets the camera projection
	*
	* @param fov Field of View
	* @param aspect_ratio Aspect Ratio
	* @param znear Near distance of the camera
	* @param zfar Far distance of the camera
	*/
	void setLookProjection(float32 fov, float32 aspect_ratio, float32 znear, float32 zfar);

	/**
	* Calls to draw the camera in the GPU (Don't call it).
	*
	* @param program Recieves a program
	*/
	void draw(int32 program);


private:
	PastorseCamera(const PastorseCamera&);
	PastorseCamera& operator= (const PastorseCamera&);

	glm::mat4 projection_;
	glm::mat4 view_;


};

#endif