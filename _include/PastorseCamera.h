#ifndef INCLUDE_PASTORSECAMERA_H_
#define INCLUDE_PASTORSECAMERA_H_ 1

#include "glm.hpp"
#include "gtc\matrix_transform.hpp"
#include "gtc\type_ptr.hpp"
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "PastorseTypes.h"


class PastorseCamera
{
public:
	PastorseCamera();
	~PastorseCamera(){};

	void set_look_up(glm::vec3 position, glm::vec3 target, glm::vec3 up);
	void set_look_projection(float32 fov, float32 aspect_ratio, float32 znear, float32 zfar);
	void draw(int32 program);


private:
	PastorseCamera(const PastorseCamera&);
	PastorseCamera& operator= (const PastorseCamera&);

	glm::mat4 projection_;
	glm::mat4 view_;


};

#endif