#ifndef INCLUDE_PASTORSERENDERTOTEXTURE_H_
#define INCLUDE_PASTORSERENDERTOTEXTURE_H_ 1

#include "PastorseTexture.h"
#include "PastorseGeometry.h"
#include "PastorseFrameBuffer.h"
#include "PastorseTypes.h"
#include "PastorseMaterial.h"
#include <memory>

class PastorseRenderToTexture
{
public:
	~PastorseRenderToTexture(){};

  void createRenderToTexture(ShaderType type);
  void draw(glm::mat4 view, glm::mat4 projection, glm::vec3 camera_position);
  void drawDepth(glm::mat4 view, glm::mat4 projection, glm::vec3 camera_position);

  std::shared_ptr<PastorseFrameBuffer> getFrameBuffer();
  std::shared_ptr<PastorseGeometry> geometry_;

private:
  friend class PastorseEngine;
  friend class PastorseMaterial;
  friend class PastorseTexture;
  friend class PastorseGeometry;

  PastorseRenderToTexture(const PastorseRenderToTexture&);
  PastorseRenderToTexture& operator= (const PastorseRenderToTexture&);
  PastorseRenderToTexture();

  std::shared_ptr<PastorseTexture> texture_;
  std::shared_ptr<PastorseTexture> depth_texture_;
  std::shared_ptr<PastorseFrameBuffer> frame_buffer_;
  std::shared_ptr<PastorseMaterial> material_;
  int32 option_;
};

#endif