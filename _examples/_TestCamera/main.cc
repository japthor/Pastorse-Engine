#include <stdio.h>
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "PastorseWindow.h"
#include "PastorseGPU.h"
#include "PastorseInput.h"
#include "PastorseCamera.h"
#include "PastorseGeometry.h"
#include "PastorseMaterial.h"
#include "PastorseActor.h"
#include <iostream>
#include <thread>
#include <memory>
#include <iostream>

#define CREATE_UNIQUE_PTR(var1) std::unique_ptr<var1>(new var1());

struct PastorseEngine{
	std::unique_ptr<PastorseInput> input;

	PastorseWindow window;

	std::shared_ptr<PastorseCamera> camera;
	std::shared_ptr<PastorseGeometry> geometry;
	std::shared_ptr<PastorseGeometry> geometry2;
	std::shared_ptr<PastorseMaterial> material;
  std::shared_ptr<PastorseMaterial> material2;

	std::shared_ptr<PastorseActor> actor;
	std::shared_ptr<PastorseActor> actor2;

	PastorseGPU* GPUInstance = nullptr;
}engine;


int main(int argc, const char* argv[])
{
  float a = 0.0f;
	engine.GPUInstance = PastorseGPU::getInstance();
	engine.geometry = std::make_shared<PastorseGeometry>();
	engine.geometry2 = std::make_shared<PastorseGeometry>();

	engine.material = std::make_shared<PastorseMaterial>();
  engine.material2 = std::make_shared<PastorseMaterial>();

	engine.camera = std::make_shared<PastorseCamera>();

	engine.actor = std::make_shared<PastorseActor>();
	engine.actor2 = std::make_shared<PastorseActor>();

	engine.input = CREATE_UNIQUE_PTR(PastorseInput);

	engine.window.init_window(800, 600, "Pastorse Ultra Engine");
	engine.material->create_material();
  engine.material2->create_material();
	engine.geometry->create_cube("cube1", 1.0f);
	engine.geometry2->create_cube("cube2", 0.5f);
	engine.material->upload_texture("../_assets/texture4.jpg");
  engine.material2->upload_texture("../_assets/texture2.jpg");

	engine.actor->set_geometry(engine.geometry);
	engine.actor->set_material(engine.material);

	engine.actor2->set_geometry(engine.geometry2);
	engine.actor2->set_material(engine.material2);

	engine.material->set_color(glm::vec3(0.5f, 0.0f, 0.0f));
  engine.material2->set_color(glm::vec3(0.0f, 0.0f, 0.5f));

	engine.actor2->add_child(engine.actor);

	while (!engine.window.is_closed_window())
	{
    a += 0.01f;
		engine.input->key_input(engine.window.getWindow());
		engine.window.pollEvents_window();
		engine.window.change_color_window(0.0f, 0.0f, 0.0f, 1.0f);

		engine.camera->draw(engine.GPUInstance->get_program());

    engine.actor->set_rotation(0.0f, 0.0f, 1.0f, sin(a));
    //engine.actor->set_scale(sin(a), sin(a), sin(a));

    engine.actor2->set_position(sin(a), 0.0f, 0.0f);

		engine.actor->draw();
		engine.actor2->draw();

		engine.camera->set_look_up(glm::vec3(engine.input->get_x(), engine.input->get_y(), engine.input->get_z()), glm::vec3(engine.input->get_x(), engine.input->get_y(), -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		engine.camera->set_look_projection(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

		engine.window.swapBuffers_window();
	}

	engine.window.close_window();
	engine.GPUInstance->delete_buffers();
	engine.GPUInstance->delete_shader_program();
	exit(EXIT_SUCCESS);	
}