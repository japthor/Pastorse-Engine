#ifndef INCLUDE_PASTORSEMATERIAL_H_
#define INCLUDE_PASTORSEMATERIAL_H_ 1

#include <string> 
#include "PastorseGPU.h"
#include "glm.hpp"
#include "tiny_obj_loader.h"



class PastorseMaterial
{
public:
	PastorseMaterial();
	~PastorseMaterial(){};

	void create_material();
	glm::vec3 get_color();

	void set_color(glm::vec3 color);

	void upload_texture(const char8* location);

	void prepare_draw();

private:
	glm::vec3 color_;
	uint32 texture_;
};

#endif