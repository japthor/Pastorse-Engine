#ifndef INCLUDE_PASTORSEENGINE_H_
#define INCLUDE_PASTORSEENGINE_H_ 1

#include "PastorseGPU.h"
#include "PastorseWindow.h"
#include "PastorseCamera.h"
#include "PastorseGeometry.h"
#include "PastorseMaterial.h"
#include "PastorseActor.h"
#include "PastorseTexture.h"
#include "PastorseRenderToTexture.h"
#include "PastorseLight.h"


#include <thread>
#include "vector"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

class PastorseEngine{
public:

	~PastorseEngine();
  static PastorseEngine* getInstance();
	/**
	* Creates the window
	*
	* @param window_width Window width.
	* @param window_height Window height.
	* @param name_engine Name of your project.
	*/
	void init(int window_width, int window_height, std::string name_engine);


	///Gets the window
	std::shared_ptr<PastorseWindow> getWindow();

	/// Will move it next patch (Don't use it).
	PastorseGPU* GPU_Instance_ = nullptr;
	
	/// Creates a pointer to the material.
	std::shared_ptr<PastorseMaterial> createMaterial();
	/// Creates a pointer of the Geometry.
	std::shared_ptr<PastorseGeometry> createGeometry();
	/// Creates a pointer of the Actor.
	std::shared_ptr<PastorseActor> createActor();
	/// Creates a pointer of the Camera.
	std::shared_ptr<PastorseCamera> createCamera();
	/// Creates a pointer of the Input.
    std::shared_ptr<PastorseInput> createInput();
    /// Creates a pointer of the Texture.
    std::shared_ptr<PastorseTexture> createTexture();
	/// Creates a pointer of the Light.
	std::shared_ptr<PastorseLight> createLight();

  int32 id_camera;

  bool activate_pp;

  void draw();

private:

  PastorseEngine(const PastorseEngine&);
  PastorseEngine& operator= (const PastorseEngine&);
  PastorseEngine();
  
  std::shared_ptr<PastorseWindow> window_;
  std::shared_ptr<PastorseInput> input_;

  std::vector<std::shared_ptr<PastorseMaterial>> material_;
  std::vector<std::shared_ptr<PastorseTexture>> texture_;
  std::vector<std::shared_ptr<PastorseGeometry>> geometry_;
  std::vector<std::shared_ptr<PastorseActor>> actor_;
  std::vector<std::shared_ptr<PastorseCamera>> camera_;
  std::vector<std::shared_ptr<PastorseLight>> light_;

	//std::unique_ptr<std::thread> thread_render_;
  std::thread *thread_render_;

  /// FrameBuffer
  std::shared_ptr<PastorseRenderToTexture> render_to_texture_;
  std::shared_ptr<PastorseRenderToTexture> post_process;
  std::shared_ptr<PastorseRenderToTexture> post_process_2;

  /// Shadows
  std::shared_ptr<PastorseRenderToTexture> render_to_texture_position_;
  std::shared_ptr<PastorseRenderToTexture> render_to_texture_position_2;

};

#endif