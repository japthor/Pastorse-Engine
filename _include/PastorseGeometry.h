#ifndef INCLUDE_PASTORSEGEOMETRY_H_
#define INCLUDE_PASTORSEGEOMETRY_H_ 1

#include "PastorseGPU.h"
#include "PastorseTypes.h"

class PastorseGeometry
{
public:
	PastorseGeometry();
	~PastorseGeometry(){};

	/**
	* Creates a Cube
	*
	* @param name The cube recieves a name
	* @param scale The cube recieves a size
	*/
	void createCube(char8* name, float32 scale);

	/**
	* Creates a Plane "Not Working Right Now"
	*
	* @param scale The cube recieves a size
	*/
	void createPlane(float32 scale, float32 x, float32 y, float32 z);

	/**
	* Calls to the geometry draw in the GPU (Don't use it)
	*
	* @param model Recieves the Model
	*/
	void draw(glm::mat4 model);

	/**
	* Calls to the geometry loadOBJ of the GPU (Don't use it)
	*
	* @param shapes Recieves the TinyOBJ geometry
	*/
	void geometryOBJ(void *shapes);

	void deleteBuffers();
	
private:
	uint32 vao_;
	uint32 ebo_;
	uint32 vbo_UV_;
	uint32 vbo_vertices_;
	uint32 vbo_normales_;
	uint32 index_;
	float32 size_;
    char8* name_;
};

#endif