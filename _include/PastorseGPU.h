#ifndef INCLUDE_PASTORSEGPU_H_
#define INCLUDE_PASTORSEGPU_H_ 1

#include "gtc\matrix_transform.hpp"
#include "gtc\type_ptr.hpp"
#include "glm.hpp"
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "PastorseTypes.h"


class PastorseGPU
{
public:
	~PastorseGPU(){};
	static PastorseGPU* getInstance();

	void init();
	void close_buffer();

	void create_cube(float32 scale, uint32 *vao, uint32 *vbo, uint32 *ebo);
	void create_plane(float32 scale, uint32 *vao, uint32 *vbo, uint32 *ebo, float32 x, float32 y, float32 z);

	void attrib_pointer();
	void transform_draw();

	void upload_texture();
	void use_texture();

	void upload_texture_prueba(const char8* location, uint32* texture);
	void set_texture(uint32* texture);

	uint32 get_program();

	void draw(uint32 *vao, uint32* ebo, uint32* vbo);
	void set_color(glm::vec3 color);

	void delete_buffers();
	void delete_shader_program();

  void set_transformation_to_draw(glm::mat4 model);


private:
	PastorseGPU();

	GLuint vao_;
	GLuint vbo_;
	GLuint ebo_;

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