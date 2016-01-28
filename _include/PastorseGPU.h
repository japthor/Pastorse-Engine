#ifndef INCLUDE_PASTORSEGPU_H_
#define INCLUDE_PASTORSEGPU_H_ 1

#include "gtc\matrix_transform.hpp"
#include "gtc\type_ptr.hpp"
#include "glm.hpp"
#include "GL\glew.h"
#include "PastorseTypes.h"

#include "tiny_obj_loader.h"
#include <vector>


class PastorseGPU
{
public:
	~PastorseGPU(){};
	static PastorseGPU* getInstance();

	/// Inits the GPU shaders
	void init();
	/// Close Buffers
	void closeBuffer();

	/// Creates a cube 
	void createCube(float32 scale, uint32 *vao, uint32 *vbo_vertices_, uint32 *vbo_normales_, uint32 *vbo_UV_, uint32 *ebo, uint32 *index_);

	/// Creates a Plane (Not working)
	void createPlane(float32 scale, uint32 *vao, uint32 *vbo_vertices_, uint32 *vbo_normales_, uint32 *vbo_UV_, uint32 *ebo, float32 x, float32 y, float32 z);

	/// Upload the Texture
	void atrributePointer(uint32 *vbo_vertices_, uint32 *vbo_normales_, uint32 *vbo_UV_);

	/// Upload the Texture
	void uploadTexture(const char8* location, uint32* texture);
	/// Sets the Shader texture
	void setTexture(uint32* texture);
	/// Gets the Program
	uint32 get_program();

	/// Calls to draw 
	void draw(uint32 *vao, uint32* ebo, uint32 *vbo_vertices_, uint32 *vbo_normales_, uint32 *vbo_UV_, uint32 *index);

	/// Deletes the Buffers
	void setColor(glm::vec3 color);

	/// Deletes the Buffers
	void delete_buffers(uint32 *vao, uint32 *vbo_vertices_, uint32 *vbo_normales_, uint32 *vbo_UV_, uint32 *ebo);
	/// Deletes the shader
	void delete_shader_program();

	/// Sets the model transofrmation matrix
    void setTransformation(glm::mat4 model);

	/// Creates the OBJ
	void loadOBJ(uint32 *vao, uint32 *vbo_vertices_, uint32 *vbo_normales_, uint32 *vbo_UV_, uint32 *ebo, uint32 *index, void* shapes);


private:
	PastorseGPU();

	GLuint vertex_shader_;
	GLuint fragment_shader_;
	GLuint program_shader_;
	GLint transformLoc_;
	
	GLint pos_attribute_;
	GLint color_attribute_;

	GLint model_location_;
	GLint view_location_;
	GLint projection_location_;

	GLuint texture_;



};

#endif