#define STB_IMAGE_IMPLEMENTATION

#include "PastorseGPU.h"
#include "stb_image.h"
#include "PastorseShader.h"

PastorseGPU::PastorseGPU() {
	vertex_shader_ = 0;
	fragment_shader_ = 0;
	program_shader_ = 0;
	pos_attribute_ = 0;
	texture_ = 0;

  /// Init Glew
  glewExperimental = GL_TRUE;
  glewInit();

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

void PastorseGPU::init(ShaderType type, uint32 *program){
  GLint param_;
  Shader shader;

  if (type == ShaderType::kShaderType_Basic){
    shader = getBasicShader();
  }else if (type == ShaderType::kShaderType_Texture){
    shader = getTextureShader();
  }else if (type == ShaderType::kShaderType_RenderToTexture){
    shader = getRenderToTextureShader();
  }else if (type == ShaderType::kShaderType_Light_Basic){
	shader = getLightBasicShader();
  }else if (type == ShaderType::kShaderType_Light_Texture){
	shader = getLightTextureShader();
  }else if (type == ShaderType::kShaderType_DirectionalLight_Texture){
	shader = getLightDirectionalTextureShader();
  }else if (type == ShaderType::kShaderType_PointLight_Texture){
	shader = getPointLightTextureShader();
  }else if (type == ShaderType::kShaderType_TestDirectionalLight_Texture){
   shader = getLightDirectionalTestTextureShader();
  }else if (type == ShaderType::kShaderType_RenderPosition){
    shader = getRenderPositionShader();
  }else if (type == ShaderType::kShaderType_SpotLight_Texture){
	  shader = getLightSpotLightTextureShader();
  }else if (type == ShaderType::kShaderType_TestSpotLight_Texture){
	  shader = getLightSpotLightTestTextureShader();
  }else if (type == ShaderType::kShaderType_TestSpotDirectionalLight_Texture){
	  shader = getLightSpotDirectionalLightTestTextureShader();
  }
  else if (type == ShaderType::kShaderType_RenderToTextureRed){
	  shader = getRenderToTextureShaderRed();
  }
  else if (type == ShaderType::kShaderType_RenderToTextureGreen){
	  shader = getRenderToTextureShaderGreen();
  }
  else if (type == ShaderType::kShaderType_3SpotDirectionalLight_Texture){
	  shader = getLightThreeSpotOneDirectionalLightTextureShader();
  }


	/// Build vertex Shader
	vertex_shader_ = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader_, 1, &shader.vertexSource, NULL);
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
	glShaderSource(fragment_shader_, 1, &shader.fragmentSource, NULL);
	glCompileShader(fragment_shader_);

	glGetShaderiv(fragment_shader_, GL_COMPILE_STATUS, &param_);

	if (!param_){
		GLsizei length_;
		GLchar info_log_[1024];

		glGetShaderInfoLog(fragment_shader_, 1024, &length_, info_log_);
		printf("\nError: %s", info_log_);
	}

  *program = glCreateProgram();
  glAttachShader(*program, vertex_shader_);
  glAttachShader(*program, fragment_shader_);
  glLinkProgram(*program);

  glGetProgramiv(*program, GL_LINK_STATUS, &param_);

  if (!param_){
    GLsizei length_;
    GLchar info_log_[1024];

    glGetProgramInfoLog(*program, 1024, &length_, info_log_);
    printf("\nError: %s", info_log_);
  }

}

void PastorseGPU::createProgram(uint32 *program){
  /// Link Shaders into Program
  GLint param_;

  *program = glCreateProgram();
  glAttachShader(*program, vertex_shader_);
  glAttachShader(*program, fragment_shader_);
  glLinkProgram(*program);

  glGetProgramiv(*program, GL_LINK_STATUS, &param_);

  if (!param_){
    GLsizei length_;
    GLchar info_log_[1024];

    glGetProgramInfoLog(*program, 1024, &length_, info_log_);
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
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,

		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,

		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f
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
    /// Generates a Vertex Array
	glGenVertexArrays(1, vao);
    // Bind the Vao first, then bind and sets vertex buffers and attribute pointers.
	glBindVertexArray(*vao);

	glGenBuffers(1, vbo_vertices_);

    /// Introduces the new buffer to the GL_ARRAY_BUFFER.
	glBindBuffer(GL_ARRAY_BUFFER, *vbo_vertices_);
    /// Configure the currently bound buffer and the data into the buffers memory:
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
  glEnableVertexAttribArray(0);

	glGenBuffers(1, vbo_normales_);

	glBindBuffer(GL_ARRAY_BUFFER, *vbo_normales_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
  glEnableVertexAttribArray(1);

	glGenBuffers(1, vbo_UV_);

	glBindBuffer(GL_ARRAY_BUFFER, *vbo_UV_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(UV), UV, GL_STATIC_DRAW);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
  glEnableVertexAttribArray(2);

	
	glGenBuffers(1, ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


  /// Deallocate Buffer
	closeBuffer();
}

void PastorseGPU::createPlane(float32 scale, uint32 *vao, uint32 *vbo_vertices_, uint32 *vbo_normales_, uint32 *vbo_UV_, uint32 *ebo, uint32 *index){

	GLfloat vertices[] = {
		// Front
		//   X         Y   Z UVX   UVY
    scale*-1.0f, scale*-1.0f, scale*0.0f,
    scale* 1.0f, scale*-1.0f, scale*0.0f,
    scale* 1.0f, scale* 1.0f, scale*0.0f,
    scale*-1.0f, scale* 1.0f, scale*0.0f,

	};

  GLfloat normals[] = {

    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
  };

  GLfloat UV[] = {
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
  };

	GLuint indices[] = {
    0, 1, 2,
    0, 2, 3,
	};

  *index = 6;

	glGenVertexArrays(1, vao);
	glBindVertexArray(*vao);

	/// Create a Vertex Buffer Object and copy the vertex data to it
  glGenBuffers(1, vbo_vertices_);

  glBindBuffer(GL_ARRAY_BUFFER, *vbo_vertices_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
  glEnableVertexAttribArray(0);

  glGenBuffers(1, vbo_normales_);

  glBindBuffer(GL_ARRAY_BUFFER, *vbo_normales_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
  glEnableVertexAttribArray(1);

  glGenBuffers(1, vbo_UV_);

  glBindBuffer(GL_ARRAY_BUFFER, *vbo_UV_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(UV), UV, GL_STATIC_DRAW);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
  glEnableVertexAttribArray(2);
	/// Create an element array
	glGenBuffers(1, ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  closeBuffer();
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
  

  if (location == nullptr){
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 800, 600, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

  }else{
    int width, height, comp;
    unsigned char* texture_data = stbi_load(location, &width, &height, &comp, 0);

    if (comp == 3){
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
    }
    else{
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
    }
  }

  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void PastorseGPU::setTexture(const char8* name, uint32* texture, uint32 program){
  glActiveTexture(GL_TEXTURE0 + *texture);
  //glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *texture);
  int32 cosa = glGetUniformLocation(program, name);
  glUniform1i(cosa, *texture);
}

uint32 PastorseGPU::get_program(){
	return program_shader_;
}

void PastorseGPU::draw(uint32 *vao, uint32* ebo, uint32 *vbo_vertices_, uint32 *vbo_normales_, uint32 *vbo_UV_, uint32 *index){
	/// Draw

	glBindVertexArray(*vao);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
	//atrributePointer(vbo_vertices_, vbo_normales_, vbo_UV_);
	glDrawElements(GL_TRIANGLES, *index, GL_UNSIGNED_INT, 0);

	closeBuffer();
}

void PastorseGPU::useProgram(uint32 *program){
  glUseProgram(*program);
}

void PastorseGPU::setColor(glm::vec3 color, uint32* program){
  int32 color_pos = glGetUniformLocation(*program, "color_");
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

void PastorseGPU::setTransformation(glm::mat4 model, uint32* program){
  int32 model_location = glGetUniformLocation(*program, "object_model");
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* tshape[0].mesh.positions.size(), &(tshape[0].mesh.positions[0]), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, vbo_normales_);
	glBindBuffer(GL_ARRAY_BUFFER, *vbo_normales_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* tshape[0].mesh.normals.size(), &(tshape[0].mesh.normals[0]), GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, vbo_UV_);
	glBindBuffer(GL_ARRAY_BUFFER, *vbo_UV_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* tshape[0].mesh.texcoords.size(), &(tshape[0].mesh.texcoords[0]), GL_STATIC_DRAW);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(2);

	glGenBuffers(1, ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)* tshape[0].mesh.indices.size(), &(tshape[0].mesh.indices[0]), GL_STATIC_DRAW);

	*index = tshape[0].mesh.indices.size();

	closeBuffer();

}

/// FrameBuffer
void PastorseGPU::createFrameBuffer(uint32 *frame_buffer, uint32 *render_buffer){

  glGenFramebuffers(1, frame_buffer);
  glGenRenderbuffers(1, render_buffer);
}

void PastorseGPU::bindFrameBuffer(uint32 *frame_buffer){
	glBindFramebuffer(GL_FRAMEBUFFER, *frame_buffer);
}

void PastorseGPU::attachFrameBuffer(uint32 texture, uint32 depth_texture, uint32 *render_buffer){
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_texture, 0);

  /*glBindRenderbuffer(GL_RENDERBUFFER, *render_buffer);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);

  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, *render_buffer);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER != GL_FRAMEBUFFER_COMPLETE)){
    printf("Framebuffer error");
  }*/

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PastorseGPU::unBindFrameBuffer(){
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PastorseGPU::setCameraProgram(uint32* program, glm::mat4 view, glm::mat4 projection){
  int32 model_location_ = glGetUniformLocation(*program, "cam_model");
  int32 view_location_ = glGetUniformLocation(*program, "view");
  int32 projection_location_ = glGetUniformLocation(*program, "projection");

  glUniformMatrix4fv(model_location_, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
  glUniformMatrix4fv(view_location_, 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(projection_location_, 1, GL_FALSE, glm::value_ptr(projection));
}

/// Directional

void PastorseGPU::setDirectionalLightColor(glm::vec3 light_color, uint32 program){
	int32 light_colorr = glGetUniformLocation(program, "directional_light_color");
	glUniform3f(light_colorr, light_color.r, light_color.g, light_color.b);
}

void PastorseGPU::setDirectionalLightDirection(glm::vec3 light_direction, uint32 program){
	int32 light_directionn = glGetUniformLocation(program, "directional_light_direction");
	glUniform3f(light_directionn, light_direction.x, light_direction.y, light_direction.z);
}


/// PointLight

void PastorseGPU::setPointLightConstant(float32 constant, uint32 program){
	float32 light_constant = glGetUniformLocation(program, "point_light_constant");
	glUniform1f(light_constant, constant);
}

void PastorseGPU::setPointLightLinear(float32 linear, uint32 program){
	int32 light_linear = glGetUniformLocation(program, "point_light_linear");
	glUniform1f(light_linear, linear);
}

void PastorseGPU::setPointLightQuadratic(float32 quadratic, uint32 program){
	int32 light_quadratic = glGetUniformLocation(program, "point_light_quadratic");
	glUniform1f(light_quadratic, quadratic);
}

void PastorseGPU::setPointLightPosition(glm::vec3 light_pos, uint32 program){
	int32 light_position = glGetUniformLocation(program, "point_light_position");
	glUniform3f(light_position, light_pos.x, light_pos.y, light_pos.z);
}

void PastorseGPU::setPositionCamera(glm::vec3 position, uint32* program){
	int32 camera_position = glGetUniformLocation(*program, "camera_position");
	glUniform3f(camera_position, position.x, position.y, position.z);
}

void PastorseGPU::setPointLightColor(glm::vec3 light_color, uint32 program){
	int32 light_colorr = glGetUniformLocation(program, "point_light_color");
	glUniform3f(light_colorr, light_color.r, light_color.g, light_color.b);
}

/// SpotLight

void PastorseGPU::setSpotLightInnerAngle(float32 angle, uint32 program, int32 number){

	if (number == 0){
		int32 light_anglee = glGetUniformLocation(program, "spot_light_inner_angle");
		glUniform1f(light_anglee, glm::cos(glm::radians(angle)));
	}
	else if (number == 1){
		int32 light_anglee = glGetUniformLocation(program, "spot_light_inner_angle_2");
		glUniform1f(light_anglee, glm::cos(glm::radians(angle)));
	}else if(number == 2){
		int32 light_anglee = glGetUniformLocation(program, "spot_light_inner_angle_3");
		glUniform1f(light_anglee, glm::cos(glm::radians(angle)));
	}
}

void PastorseGPU::setSpotLightOuterAngle(float32 angle, uint32 program, int32 number){

	if(number == 0){
		int32 light_anglee = glGetUniformLocation(program, "spot_light_outer_angle");
		glUniform1f(light_anglee, glm::cos(glm::radians(angle)));
	}
	else if (number == 1){
		int32 light_anglee = glGetUniformLocation(program, "spot_light_outer_angle_2");
		glUniform1f(light_anglee, glm::cos(glm::radians(angle)));
	}
	else if (number == 2){
		int32 light_anglee = glGetUniformLocation(program, "spot_light_outer_angle_3");
		glUniform1f(light_anglee, glm::cos(glm::radians(angle)));
	}
}

void PastorseGPU::setSpotLightConstant(float32 constant, uint32 program, int32 number){

	if (number == 0){
		float32 light_constant = glGetUniformLocation(program, "spot_light_constant");
		glUniform1f(light_constant, constant);
	}
	else if (number == 1){
		float32 light_constant = glGetUniformLocation(program, "spot_light_constant_2");
		glUniform1f(light_constant, constant);
	}
	else if (number == 2){
		float32 light_constant = glGetUniformLocation(program, "spot_light_constant_3");
		glUniform1f(light_constant, constant);
	}

}

void PastorseGPU::setSpotLightLinear(float32 linear, uint32 program, int32 number){

	if (number == 0){
		int32 light_linear = glGetUniformLocation(program, "spot_light_linear_");
		glUniform1f(light_linear, linear);
	}
	else if (number == 1){
		int32 light_linear = glGetUniformLocation(program, "spot_light_linear_2");
		glUniform1f(light_linear, linear);
	}
	else if (number == 2){
		int32 light_linear = glGetUniformLocation(program, "spot_light_linear_3");
		glUniform1f(light_linear, linear);
	}
}

void PastorseGPU::setSpotLightQuadratic(float32 quadratic, uint32 program, int32 number){
	if (number == 0){
		int32 light_quadratic = glGetUniformLocation(program, "spot_light_quadratic");
		glUniform1f(light_quadratic, quadratic);
	}
	else if (number == 1){
		int32 light_quadratic = glGetUniformLocation(program, "spot_light_quadratic_2");
		glUniform1f(light_quadratic, quadratic);
	}
	else if (number == 2){
		int32 light_quadratic = glGetUniformLocation(program, "spot_light_quadratic_3");
		glUniform1f(light_quadratic, quadratic);
	}
}

void PastorseGPU::setSpotLightPosition(glm::vec3 light_pos, uint32 program, int32 number){

	if (number == 0){
		int32 light_position = glGetUniformLocation(program, "spot_light_position");
		glUniform3f(light_position, light_pos.x, light_pos.y, light_pos.z);
	}
	else if (number == 1){
		int32 light_position = glGetUniformLocation(program, "spot_light_position_2");
		glUniform3f(light_position, light_pos.x, light_pos.y, light_pos.z);
	}
	else if (number == 2){
		int32 light_position = glGetUniformLocation(program, "spot_light_position_3");
		glUniform3f(light_position, light_pos.x, light_pos.y, light_pos.z);
	}
	
}

void PastorseGPU::setSpotLightColor(glm::vec3 light_color, uint32 program, int32 number){
	if (number == 0){
		int32 light_colorr = glGetUniformLocation(program, "spot_light_color");
		glUniform3f(light_colorr, light_color.r, light_color.g, light_color.b);
	}
	else if (number == 1){
		int32 light_colorr = glGetUniformLocation(program, "spot_light_color_2");
		glUniform3f(light_colorr, light_color.r, light_color.g, light_color.b);
	}
	else if (number == 2){
		int32 light_colorr = glGetUniformLocation(program, "spot_light_color_3");
		glUniform3f(light_colorr, light_color.r, light_color.g, light_color.b);
	}
}

void PastorseGPU::setSpotLightDirection(glm::vec3 light_direction, uint32 program, int32 number){
	if (number == 0){
		int32 light_directionn = glGetUniformLocation(program, "spot_light_direction");
		glUniform3f(light_directionn, light_direction.x, light_direction.y, light_direction.z);
	}
	else if (number == 1){
		int32 light_directionn = glGetUniformLocation(program, "spot_light_direction_2");
		glUniform3f(light_directionn, light_direction.x, light_direction.y, light_direction.z);
	}
	else if (number == 2){
		int32 light_directionn = glGetUniformLocation(program, "spot_light_direction_3");
		glUniform3f(light_directionn, light_direction.x, light_direction.y, light_direction.z);
	}

}



/// Shadow
void PastorseGPU::setCameraProgramShadow(uint32* program, glm::mat4 view, glm::mat4 projection, glm::mat4 view2, glm::mat4 projection2){
  int32 shadow_view_location_ = glGetUniformLocation(*program, "shadow_view");
  int32 shadow_model_location_ = glGetUniformLocation(*program, "shadow_model");
  int32 shadow_projection_location_ = glGetUniformLocation(*program, "shadow_projection");

  glUniformMatrix4fv(shadow_view_location_, 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(shadow_projection_location_, 1, GL_FALSE, glm::value_ptr(projection));
  glUniformMatrix4fv(shadow_model_location_, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));

  int32 shadow_view_location_2 = glGetUniformLocation(*program, "shadow_view2");
  int32 shadow_model_location_2 = glGetUniformLocation(*program, "shadow_model2");
  int32 shadow_projection_location_2 = glGetUniformLocation(*program, "shadow_projection2");

  glUniformMatrix4fv(shadow_view_location_2, 1, GL_FALSE, glm::value_ptr(view2));
  glUniformMatrix4fv(shadow_projection_location_2, 1, GL_FALSE, glm::value_ptr(projection2));
  glUniformMatrix4fv(shadow_model_location_2, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
}

void PastorseGPU::uploadDepthTexture(uint32* texture){
  glGenTextures(1, texture);
  glBindTexture(GL_TEXTURE_2D, *texture);

  // set texture warpping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 800, 600, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

  glBindTexture(GL_TEXTURE_2D, 0);
}









