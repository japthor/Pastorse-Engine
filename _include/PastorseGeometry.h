#ifndef INCLUDE_PASTORSEGEOMETRY_H_
#define INCLUDE_PASTORSEGEOMETRY_H_ 1

#include "PastorseGPU.h"
#include "PastorseTypes.h"
#include "PastorseMaterial.h"
#include <string> 
#include <memory>



class PastorseGeometry
{
public:
	PastorseGeometry();
	~PastorseGeometry(){};

	void create_cube(char8* name, float32 scale);
	void create_plane(float32 scale, float32 x, float32 y, float32 z);
	void draw(glm::mat4 model);

	void set_material(std::weak_ptr<PastorseMaterial> material);
	
private:
	uint32 vao_;
	uint32 vbo_;
	uint32 ebo_;
	float32 size_;
  char8* name_;
};

#endif