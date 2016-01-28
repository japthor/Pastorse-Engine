#include "PastorseGPU.h"
#include "PastorseWindow.h"
#include "PastorseInput.h"
#include "PastorseCamera.h"
#include "PastorseGeometry.h"
#include "PastorseMaterial.h"
#include "PastorseActor.h"


struct PastorseEngine{
	std::unique_ptr<PastorseInput> input;
	PastorseWindow window;

	std::shared_ptr<PastorseCamera> camera;
	std::shared_ptr<PastorseGeometry> geometry;
	std::shared_ptr<PastorseGeometry> geometry2;
	std::shared_ptr<PastorseGeometry> geometry3;
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
	engine.geometry = CREATE_MAKE_SHARED_PTR(PastorseGeometry);
	engine.geometry2 = CREATE_MAKE_SHARED_PTR(PastorseGeometry);
	engine.geometry3 = CREATE_MAKE_SHARED_PTR(PastorseGeometry);
	engine.material = CREATE_MAKE_SHARED_PTR(PastorseMaterial);
	engine.material2 = CREATE_MAKE_SHARED_PTR(PastorseMaterial);
	engine.camera = CREATE_MAKE_SHARED_PTR(PastorseCamera);
	engine.actor = CREATE_MAKE_SHARED_PTR(PastorseActor);
	engine.actor2 = CREATE_MAKE_SHARED_PTR(PastorseActor);
	engine.input = CREATE_UNIQUE_PTR(PastorseInput);

	engine.window.initWindow(800, 600, "Pastorse Ultra Engine");
	engine.material->createMaterial();
	engine.material2->createMaterial();

	engine.actor->setGeometry(engine.geometry3);
	engine.actor->setMaterial(engine.material);
	engine.actor->loadOBJ("../_assets/Stormtrooper/Stormtrooper.obj");

	engine.actor2->setGeometry(engine.geometry2);
	engine.actor2->setMaterial(engine.material2);
	engine.actor2->loadOBJ("../_assets/R2-D2/R2-D2.obj");

	engine.actor2->setPosition(0.0f, 0.0f, 5.0f);

	engine.actor->addChild(engine.actor2);


	while (!engine.window.isClosedWindow())
	{
        a += 0.01f;
		engine.input->keyInput(engine.window.getWindow());
		engine.window.pollEvents();
		engine.window.setColor(0.0f, 0.0f, 0.0f, 1.0f);

		// Input
		engine.camera->setLookUp(glm::vec3(engine.input->getX(), engine.input->getY(), engine.input->getZ()), glm::vec3(engine.input->getX(), engine.input->getY(), -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		engine.camera->setLookProjection(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

		// Update
		engine.actor->setRotation(0.0f, 1.0f, 0.0f, a);
		engine.actor2->setPosition(sin(a) * 2, 0.0f, engine.actor2->getPosition().z);

		// Render
		engine.camera->draw(engine.GPUInstance->get_program());
		engine.actor->draw();
		engine.actor2->draw();

		engine.window.swapBuffers();
	}

	engine.window.closeWindow();
	engine.GPUInstance->delete_buffers();
	engine.GPUInstance->delete_shader_program();
	exit(EXIT_SUCCESS);	
}