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
  ~PastorseGPU(){ delete_shader_program(); };
  static PastorseGPU* getInstance();
  /// Gets the Program
  uint32 get_program();
private:

  friend class PastorseGeometry;
  friend class PastorseMaterial;
  friend class PastorseTexture;
  friend class PastorseFrameBuffer;
  friend class PastorseCamera;
  friend class PastorseLight;

	/// Inits the GPU shaders
    void init(ShaderType type, uint32 *program);

	/// Close Buffers
	void closeBuffer();

	/// Creates a cube 
	void createCube(float32 scale, uint32 *vao, uint32 *vbo_vertices_, uint32 *vbo_normales_, uint32 *vbo_UV_, uint32 *ebo, uint32 *index_);

	/// Creates a Plane (Not working)
	void createPlane(float32 scale, uint32 *vao, uint32 *vbo_vertices_, uint32 *vbo_normales_, uint32 *vbo_UV_, uint32 *ebo, uint32* index_);

	/// Upload the Texture
	void atrributePointer(uint32 *vbo_vertices_, uint32 *vbo_normales_, uint32 *vbo_UV_);

	/// Upload the Texture
	void uploadTexture(const char8* location, uint32* texture);

	/// Sets the Shader texture
  void setTexture(const char8* name, uint32* texture, uint32 program);

	/// Calls to draw 
	void draw(uint32 *vao, uint32* ebo, uint32 *vbo_vertices_, uint32 *vbo_normales_, uint32 *vbo_UV_, uint32 *index);

	/// Deletes the Buffers
  void setColor(glm::vec3 color, uint32* program);

	/// Deletes the Buffers
	void delete_buffers(uint32 *vao, uint32 *vbo_vertices_, uint32 *vbo_normales_, uint32 *vbo_UV_, uint32 *ebo);
	/// Deletes the shader
	void delete_shader_program();

	/// Sets the model transofrmation matrix
  void setTransformation(glm::mat4 model, uint32* program);

	/// Creates the OBJ
	void loadOBJ(uint32 *vao, uint32 *vbo_vertices_, uint32 *vbo_normales_, uint32 *vbo_UV_, uint32 *ebo, uint32 *index, void* shapes);

  // Program
  void createProgram(uint32 *program);
  void useProgram(uint32 *program);
  void setColorProgram(uint32 *program);
  void setLightProgram(uint32 *program);
  void setCameraProgram(uint32* program, glm::mat4 view, glm::mat4 projection);

  /// Frame Buffer
  void createFrameBuffer(uint32 *frame_buffer, uint32 *render_buffer);
  void bindFrameBuffer(uint32 *frame_buffer);
  void attachFrameBuffer(uint32 texture, uint32 depth_texture, uint32 *render_buffer);
  void unBindFrameBuffer();

  // Light
  void setDirectionalLightColor(glm::vec3 light_color, uint32 program);
  void setDirectionalLightDirection(glm::vec3 light_dir, uint32 program);

  /// PointLight
  void setPointLightConstant(float32 constant, uint32 program);
  void setPointLightLinear(float32 linear, uint32 program);
  void setPointLightQuadratic(float32 quadratic, uint32 program);
  void setPointLightPosition(glm::vec3 light_pos, uint32 program);
  void setPositionCamera(glm::vec3 position, uint32* program);
  void setPointLightColor(glm::vec3 light_color, uint32 program);

  /// SpotLight
  void setSpotLightInnerAngle(float32 angle, uint32 program, int32 number);
  void setSpotLightOuterAngle(float32 angle, uint32 program, int32 number);
  void setSpotLightConstant(float32 constant, uint32 program, int32 number);
  void setSpotLightLinear(float32 linear, uint32 program, int32 number);
  void setSpotLightQuadratic(float32 quadratic, uint32 program, int32 number);
  void setSpotLightPosition(glm::vec3 light_pos, uint32 program, int32 number);

  void setSpotLightColor(glm::vec3 light_color, uint32 program, int32 number);
  void setSpotLightDirection(glm::vec3 light_direction, uint32 program, int32 number);

  /// Shadow
  void setCameraProgramShadow(uint32* program, glm::mat4 view, glm::mat4 projection, glm::mat4 view2, glm::mat4 projection2);

  /// Depth
  void uploadDepthTexture(uint32* texture);


	PastorseGPU(const PastorseGPU&);
	PastorseGPU& operator= (const PastorseGPU&);
	PastorseGPU();

	GLuint vertex_shader_;
	GLuint fragment_shader_;
	GLuint program_shader_;

	GLuint vertex_shader_1;
	GLuint fragment_shader_1;
	GLuint program_shader_1;

	GLint transformLoc_;
	
	GLint pos_attribute_;
	GLint color_attribute_;

	GLint model_location_;
	GLint view_location_;
	GLint projection_location_;

  GLuint texture_;

  /// Program
  int32 color_pos_;
  int32 option_use_;

};

#endif