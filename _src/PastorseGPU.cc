#define STB_IMAGE_IMPLEMENTATION

#include "PastorseGPU.h"
#include "stb_image.h"

GLchar* vertexSource =
"#version 330 core\n"
"layout(location = 0) in vec3 position;\n"
"layout(location = 1) in vec3 normal;\n"
"layout(location = 2) in vec2 text_coords;\n"
"out vec2 textCoords;\n"
"uniform mat4 cam_model;\n"
"uniform mat4 object_model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"out vec2 coord_text; \n"
"out vec3 norm; \n"
"out vec3 direction; \n"
"void main()\n"
"{\n"
"textCoords = text_coords;\n"
"vec4 total = cam_model *  object_model  * vec4(position, 1.0); \n"
"norm = (cam_model *  object_model * vec4(normal, 0.0)).xyz; \n"
"vec3 light_pos = vec3(0.0, 100.0, 0.0); \n"
"direction = normalize(light_pos - total.xyz); \n"
"gl_Position = projection * view  * cam_model * object_model * vec4(position, 1.0f);\n"
"}\n";

GLchar* fragmentSource =
"#version 330 core\n"
"in vec2 textCoords;\n"
"in vec3 norm; \n "
"in vec3 direction; \n"
"uniform sampler2D texture_;\n"
"uniform vec3 color_;"
"out vec4 color;\n"
"void main()\n"
"{\n"
"//vec2 new_texCoords = vec2(textCoords.x, 1.0 - textCoords.y);\n"
"float Intensity = dot(normalize(norm), normalize(direction)); \n"
"color = vec4(color_ * vec3(Intensity), 1.0) * texture2D(texture_,textCoords);\n"
"}\n";


PastorseGPU::PastorseGPU() {
	vertex_shader_ = 0;
	fragment_shader_ = 0;
	program_shader_ = 0;
	pos_attribute_ = 0;
	texture_ = 0;

  /// Init Glew
  glewExperimental = GL_TRUE;
  glewInit();

  /// View Port Dimensions
  //glViewport(0, 0, 800, 600);

  /// Set up OpenGL options
  glEnable(GL_DEPTH_TEST);

}


PastorseGPU* PastorseGPU::getInstance(){
	static PastorseGPU* instance = nullptr;
	if (instance == nullptr){
		instance = new PastorseGPU();
	}
	return instance;
}

void PastorseGPU::init(){
	
  GLint param_;

	/// Build vertex Shader
	vertex_shader_ = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader_, 1, &vertexSource, NULL);
	glCompileShader(vertex_shader_);

	glGetShaderiv(vertex_shader_, GL_COMPILE_STATUS, &param_);

	if (!param_){
		GLsizei length_;
		GLchar info_log_[1024];

		glGetShaderInfoLog(vertex_shader_, 1024, &length_, info_log_);
		printf("\nError: %s", info_log_);
	}

	/// Build Fragment Shader
	fragment_shader_ = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader_, 1, &fragmentSource, NULL);
	glCompileShader(fragment_shader_);

	glGetShaderiv(fragment_shader_, GL_COMPILE_STATUS, &param_);

	if (!param_){
		GLsizei length_;
		GLchar info_log_[1024];

		glGetShaderInfoLog(fragment_shader_, 1024, &length_, info_log_);
		printf("\nError: %s", info_log_);
	}

	/// Link Shaders into Program
	program_shader_ = glCreateProgram();
	glAttachShader(program_shader_, vertex_shader_);
	glAttachShader(program_shader_, fragment_shader_);
	glLinkProgram(program_shader_);

	glGetProgramiv(program_shader_, GL_LINK_STATUS, &param_);

	if (!param_){
		GLsizei length_;
		GLchar info_log_[1024];

		glGetProgramInfoLog(program_shader_,1024,&length_,info_log_);
		printf("\nError: %s", info_log_);
	}
}

void PastorseGPU::closeBuffer(){
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void PastorseGPU::createCube(float32 scale, uint32 *vao, uint32 *vbo_vertices_, uint32 *vbo_normales_, uint32 *vbo_UV_, uint32 *ebo, uint32 *index){

	GLfloat vertices[] = {
		// Front
		//    X           Y            Z                         
		scale*-1.0f, scale*-1.0f, scale*1.0f,
		scale* 1.0f, scale*-1.0f, scale*1.0f,
		scale* 1.0f, scale* 1.0f, scale*1.0f,
		scale*-1.0f, scale* 1.0f, scale*1.0f,

		// Back
		//    X           Y            Z      
		scale*-1.0f, scale*-1.0f, scale*-1.0f,
		scale* 1.0f, scale*-1.0f, scale*-1.0f,
		scale* 1.0f, scale* 1.0f, scale*-1.0f,
		scale*-1.0f, scale* 1.0f, scale*-1.0f,

		// Left
		//    X           Y            Z      
		scale*-1.0f, scale*-1.0f, scale*-1.0f,
		scale*-1.0f, scale*-1.0f, scale* 1.0f,
		scale*-1.0f, scale* 1.0f, scale* 1.0f,
		scale*-1.0f, scale* 1.0f, scale*-1.0f,

		// Right
		//    X           Y            Z      
		scale* 1.0f, scale*-1.0f, scale*-1.0f,
		scale* 1.0f, scale*-1.0f, scale* 1.0f,
		scale* 1.0f, scale* 1.0f, scale* 1.0f,
		scale* 1.0f, scale* 1.0f, scale*-1.0f,

		// Up
		//    X           Y            Z      
		scale*-1.0f, scale* 1.0f, scale* 1.0f,
		scale* 1.0f, scale* 1.0f, scale* 1.0f,
		scale* 1.0f, scale* 1.0f, scale*-1.0f,
		scale*-1.0f, scale* 1.0f, scale*-1.0f,

		// Up
		//    X           Y            Z       
		scale*-1.0f, scale*-1.0f, scale* 1.0f,
		scale* 1.0f, scale*-1.0f, scale* 1.0f,
		scale* 1.0f, scale*-1.0f, scale*-1.0f,
		scale*-1.0f, scale*-1.0f, scale*-1.0f

	};

	GLfloat normals[] = {
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,

		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,

		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f
	};

	GLfloat UV[] = {
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f

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

	*index = 36;

	glGenVertexArrays(1, vao);
	glBindVertexArray(*vao);

	/// Create a Vertex Buffer Object and copy the vertex data to it
	glGenBuffers(1, vbo_vertices_);

	glBindBuffer(GL_ARRAY_BUFFER, *vbo_vertices_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, vbo_normales_);

	glBindBuffer(GL_ARRAY_BUFFER, *vbo_normales_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);

	glGenBuffers(1, vbo_UV_);

	glBindBuffer(GL_ARRAY_BUFFER, *vbo_UV_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(UV), UV, GL_STATIC_DRAW);

	/// Create an element array
	glGenBuffers(1, ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	closeBuffer();
}

void PastorseGPU::createPlane(float32 scale, uint32 *vao, uint32 *vbo_vertices_, uint32 *vbo_normales_, uint32 *vbo_UV_, uint32 *ebo, float32 x, float32 y, float32 z){

	/*GLfloat vertices[] = {
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

	close_buffer();*/
}

void PastorseGPU::atrributePointer(uint32 *vbo_vertices_, uint32 *vbo_normales_, uint32 *vbo_UV_){
	// Position 
	glBindBuffer(GL_ARRAY_BUFFER, *vbo_vertices_);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normal
	glBindBuffer(GL_ARRAY_BUFFER, *vbo_normales_);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(1);
	// Text Coords
	glBindBuffer(GL_ARRAY_BUFFER, *vbo_UV_);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(2);
}


void PastorseGPU::uploadTexture(const char8* location, uint32* texture){
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

void PastorseGPU::setTexture(uint32* texture){
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glUniform1i(glGetUniformLocation(program_shader_, "texture_"), 0);
}

uint32 PastorseGPU::get_program(){
	return program_shader_;
}

void PastorseGPU::draw(uint32 *vao, uint32* ebo, uint32 *vbo_vertices_, uint32 *vbo_normales_, uint32 *vbo_UV_, uint32 *index){
	/// Draw
	glUseProgram(program_shader_);

	glBindVertexArray(*vao);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
	atrributePointer(vbo_vertices_, vbo_normales_, vbo_UV_);
	glDrawElements(GL_TRIANGLES, *index, GL_UNSIGNED_INT, 0);

	closeBuffer();
}

void PastorseGPU::setColor(glm::vec3 color){
	int32 color_pos = glGetUniformLocation(program_shader_, "color_");
	glUniform3f(color_pos, color.x, color.y, color.z);

}

void PastorseGPU::delete_buffers(uint32 *vao, uint32 *vbo_vertices_, uint32 *vbo_normales_, uint32 *vbo_UV_, uint32 *ebo){
	glDeleteBuffers(1, ebo);
	glDeleteBuffers(1, vbo_vertices_);
	glDeleteBuffers(1, vbo_normales_);
	glDeleteBuffers(1, vbo_UV_);
	glDeleteVertexArrays(1, vao);
}

void PastorseGPU::delete_shader_program(){
	glDeleteProgram(program_shader_);
	glDeleteShader(vertex_shader_);
	glDeleteShader(fragment_shader_);
}

void PastorseGPU::setTransformation(glm::mat4 model){
  int32 model_location = glGetUniformLocation(program_shader_, "object_model");
  glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model));
}

void PastorseGPU::loadOBJ(uint32 *vao, uint32 *vbo_vertices_, uint32 *vbo_normales_, uint32 *vbo_UV_, uint32 *ebo, uint32 *index, void* shapes){

	
	tinyobj::shape_t* tshape = reinterpret_cast<tinyobj::shape_t *>(shapes);

	for (int i = 1; i < tshape[0].mesh.texcoords.size(); i += 2)
	{
		tshape[0].mesh.texcoords[i] = 1.0f - tshape[0].mesh.texcoords[i];
	}

	glGenVertexArrays(1, vao);
	glBindVertexArray(*vao);

	
	glGenBuffers(1, vbo_vertices_);
	glBindBuffer(GL_ARRAY_BUFFER, *vbo_vertices_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* tshape[0].mesh.positions.size(), &tshape[0].mesh.positions[0], GL_STATIC_DRAW);


	glGenBuffers(1, vbo_normales_);
	glBindBuffer(GL_ARRAY_BUFFER, *vbo_normales_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* tshape[0].mesh.normals.size(), &tshape[0].mesh.normals[0], GL_STATIC_DRAW);

	glGenBuffers(1, vbo_UV_);
	glBindBuffer(GL_ARRAY_BUFFER, *vbo_UV_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* tshape[0].mesh.texcoords.size(), &tshape[0].mesh.texcoords[0], GL_STATIC_DRAW);


	glGenBuffers(1, ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)* tshape[0].mesh.indices.size(), &tshape[0].mesh.indices[0], GL_STATIC_DRAW);

	*index = tshape[0].mesh.indices.size();

	closeBuffer();

}




