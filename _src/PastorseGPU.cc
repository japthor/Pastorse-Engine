#define STB_IMAGE_IMPLEMENTATION

#include "PastorseGPU.h"
#include "stb_image.h"

GLchar* vertexSource =
"#version 330 core\n"
"layout(location = 0) in vec3 position;\n"
"layout(location = 1) in vec3 color;\n"
"layout(location = 2) in vec2 text_coords;\n"
"out vec2 textCoords;\n"
"uniform mat4 cam_model;\n"
"uniform mat4 object_model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"gl_Position = projection * view  * cam_model * object_model * vec4(position, 1.0f);\n"
"textCoords = text_coords;\n"
"}\n";

GLchar* fragmentSource =
"#version 330 core\n"
"in vec2 textCoords;\n"
"uniform sampler2D texture_;\n"
"uniform vec3 color_;"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(color_,1.0) * texture2D(texture_,textCoords);\n"
"}\n";


PastorseGPU::PastorseGPU() {
	vao_ = 0;
	vbo_ = 0;
	ebo_ = 0;
	vertex_shader_ = 0;
	fragment_shader_ = 0;
	program_shader_ = 0;
	pos_attribute_ = 0;
	texture_ = 0;
}


PastorseGPU* PastorseGPU::getInstance(){
	static PastorseGPU* instance = nullptr;
	if (instance == nullptr){
		instance = new PastorseGPU();
	}
	return instance;
}

void PastorseGPU::init(){

	/// Init Glew
	glewExperimental = GL_TRUE;
	glewInit();

	/// View Port Dimensions
	glViewport(0, 0, 800, 600);

	/// Set up OpenGL options
	glEnable(GL_DEPTH_TEST);

	/// Build vertex Shader
	vertex_shader_ = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader_, 1, &vertexSource, NULL);
	glCompileShader(vertex_shader_);

	/// Build Fragment Shader
	fragment_shader_ = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader_, 1, &fragmentSource, NULL);
	glCompileShader(fragment_shader_);

	/// Link Shaders into Program
	program_shader_ = glCreateProgram();
	glAttachShader(program_shader_, vertex_shader_);
	glAttachShader(program_shader_, fragment_shader_);
	glLinkProgram(program_shader_);
}

void PastorseGPU::close_buffer(){
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void PastorseGPU::create_cube(float32 scale, uint32 *vao, uint32 *vbo, uint32 *ebo){

	GLfloat vertices[] = {
		// Front
		//    X           Y            Z                         UVX   UVY
		scale*-1.0f, scale*-1.0f, scale*1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		scale* 1.0f, scale*-1.0f, scale*1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		scale* 1.0f, scale* 1.0f, scale*1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		scale*-1.0f, scale* 1.0f, scale*1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		// Back
		//    X           Y            Z        R     G     B    UVX   UVY
		scale*-1.0f, scale*-1.0f, scale*-1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		scale* 1.0f, scale*-1.0f, scale*-1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		scale* 1.0f, scale* 1.0f, scale*-1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		scale*-1.0f, scale* 1.0f, scale*-1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,

		// Left
		//    X           Y            Z        R     G     B    UVX   UVY
		scale*-1.0f, scale*-1.0f, scale*-1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		scale*-1.0f, scale*-1.0f, scale* 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		scale*-1.0f, scale* 1.0f, scale* 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		scale*-1.0f, scale* 1.0f, scale*-1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

		// Right
		//    X           Y            Z        R     G     B    UVX   UVY
		scale* 1.0f, scale*-1.0f, scale*-1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		scale* 1.0f, scale*-1.0f, scale* 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		scale* 1.0f, scale* 1.0f, scale* 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		scale* 1.0f, scale* 1.0f, scale*-1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

		// Up
		//    X           Y            Z        R     G     B    UVX   UVY
		scale*-1.0f, scale* 1.0f, scale* 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		scale* 1.0f, scale* 1.0f, scale* 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		scale* 1.0f, scale* 1.0f, scale*-1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		scale*-1.0f, scale* 1.0f, scale*-1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,

		// Up
		//    X           Y            Z        R     G     B    UVX   UVY
		scale*-1.0f, scale*-1.0f, scale* 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		scale* 1.0f, scale*-1.0f, scale* 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		scale* 1.0f, scale*-1.0f, scale*-1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		scale*-1.0f, scale*-1.0f, scale*-1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	};

	GLuint indices[] = {
		0, 1, 2,
		0, 2, 3,

		4, 5, 6,
		4, 6, 7,

		8, 9, 10,
		8, 10, 11,

		12, 13, 14,
		12, 14, 15,

		16, 17, 18,
		16, 18, 19,

		20, 21, 22,
		20, 22, 23
	};

	glGenVertexArrays(1, vao);
	glBindVertexArray(*vao);

	/// Create a Vertex Buffer Object and copy the vertex data to it
	glGenBuffers(1, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	/// Create an element array
	glGenBuffers(1, ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	close_buffer();
}

void PastorseGPU::create_plane(float32 scale, uint32 *vao, uint32 *vbo, uint32 *ebo, float32 x, float32 y, float32 z){

	GLfloat vertices[] = {
		// Front
		//   X         Y         Z            UVX   UVY
		scale*-x, scale*-y, scale*z, x, y, z, 1.0f, 1.0f,
		scale* x, scale*-y, scale*z, x, y, z, 0.0f, 1.0f,
		scale* x, scale* y, scale*z, x, y, z, 0.0f, 0.0f,
		scale*-x, scale* y, scale*z, x, y, z, 1.0f, 0.0f,

	};

	GLuint indices[] = {
		0, 1, 2,
		0, 2, 3,
	};

	glGenVertexArrays(1, vao);
	glBindVertexArray(*vao);

	/// Create a Vertex Buffer Object and copy the vertex data to it
	glGenBuffers(1, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	/// Create an element array
	glGenBuffers(1, ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	close_buffer();
}

void PastorseGPU::attrib_pointer(){
	// Position 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Text Coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
}

void PastorseGPU::transform_draw(){
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	model = glm::rotate(model, (GLfloat)glfwGetTime() * -0.5f, glm::vec3(0.5f, 1.0f, 0.0f));
	view = glm::translate(view, glm::vec3(1.0f, 0.0f, -3.0f));
	projection = glm::perspective(45.0f, (GLfloat)800.0f / (GLfloat)600.0f, 0.1f, 100.0f);

	model_location_ = glGetUniformLocation(program_shader_, "model");
	view_location_ = glGetUniformLocation(program_shader_, "view");
	projection_location_ = glGetUniformLocation(program_shader_, "projection");

	glUniformMatrix4fv(model_location_, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(view_location_, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projection_location_, 1, GL_FALSE, glm::value_ptr(projection));

}

void PastorseGPU::upload_texture(){
	glGenTextures(1, &texture_);
	glBindTexture(GL_TEXTURE_2D, texture_);
	// set texture warpping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, comp;
	unsigned char* texture = stbi_load("../_build/bin/texture2.png", &width, &height, &comp, 0);

	if (comp == 3){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
	}
	else{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
	}
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void PastorseGPU::use_texture(){
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_);
	glUniform1i(glGetUniformLocation(program_shader_, "texture_"), 0);
}

void PastorseGPU::upload_texture_prueba(const char8* location, uint32* texture){
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	// set texture warpping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, comp;
	unsigned char* texture_data = stbi_load(location, &width, &height, &comp, 0);

	if (comp == 3){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
	}
	else{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
	}
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void PastorseGPU::set_texture(uint32* texture){
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glUniform1i(glGetUniformLocation(program_shader_, "texture_"), 0);
}

uint32 PastorseGPU::get_program(){
	return program_shader_;
}

void PastorseGPU::draw(uint32 *vao, uint32* ebo, uint32* vbo){
	/// Draw
	glUseProgram(program_shader_);

	glBindVertexArray(*vao);
	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
	attrib_pointer();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	close_buffer();

}

void PastorseGPU::set_color(glm::vec3 color){
	int32 color_pos = glGetUniformLocation(program_shader_, "color_");
	glUniform3f(color_pos, color.x, color.y, color.z);

}

void PastorseGPU::delete_buffers(){
	glDeleteBuffers(1, &ebo_);
	glDeleteBuffers(1, &vbo_);
	glDeleteVertexArrays(1, &vao_);
}

void PastorseGPU::delete_shader_program(){
	glDeleteProgram(program_shader_);
	glDeleteShader(vertex_shader_);
	glDeleteShader(fragment_shader_);
}

void PastorseGPU::set_transformation_to_draw(glm::mat4 model){
  int32 model_location = glGetUniformLocation(program_shader_, "object_model");
  glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model));
}


