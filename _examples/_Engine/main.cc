#include "PastorseGPU.h"
#include "PastorseWindow.h"
#include "PastorseInput.h"
#include "PastorseCamera.h"
#include "PastorseGeometry.h"
#include "PastorseMaterial.h"
#include "PastorseActor.h"

#include "PastorseEngine.h"

int main(int argc, const char* argv[])
{

	std::unique_ptr<PastorseInput> input;

	std::shared_ptr<PastorseCamera> camera;

	std::shared_ptr<PastorseGeometry> geometry2;
	std::shared_ptr<PastorseGeometry> geometry3;
	std::shared_ptr<PastorseMaterial> material;
	std::shared_ptr<PastorseMaterial> material2;

	std::shared_ptr<PastorseActor> actor;
	std::shared_ptr<PastorseActor> actor2;

	std::unique_ptr<PastorseEngine> engine;

   float a = 0.0f;

	engine = CREATE_UNIQUE_PTR(PastorseEngine);

	engine->init(800, 600, "Pastorse Ultra Engine");
	//engine->getWindow()->setColor(0.0f, 1.0f, 0.0, 1.0f);

	input = engine->createInput();

	material = engine->createMaterial();
	material2 = engine->createMaterial();

	material->initMaterial();
	material->uploadTexture("../_assets/texture2.png");
	material2->initMaterial();

	geometry2 = engine->createGeometry();
	geometry3 = engine->createGeometry();
	geometry3->createCube("cosa", 1.0f);

	camera = engine->createCamera();

	actor = engine->createActor();
	actor2 = engine->createActor();

	actor->setGeometry(geometry3);
	actor->setMaterial(material);
	//actor->loadOBJ("../_assets/Stormtrooper/Stormtrooper.obj");

	actor2->setGeometry(geometry2);
	actor2->setMaterial(material2);
	actor2->loadOBJ("../_assets/R2-D2/R2-D2.obj");

	actor2->setPosition(0.0f, 0.0f, 5.0f);

	actor->addChild(actor2);
  //engine->thread();
	while (!engine->getWindow()->isClosedWindow())
	{
    a += 0.01f;
		input->keyInput(engine->getWindow()->getWindow());
		engine->getWindow()->pollEvents();
		

		// Input
		camera->setLookUp(glm::vec3(input->getX(), input->getY(),input->getZ()), glm::vec3(input->getX(), input->getY(), -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		camera->setLookProjection(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

		// Update
		actor2->setRotation(0.0f, 1.0f, 0.0f, a);
		material->setColor(0.0f, 1.0f, 0.0f);

    //actor->setScale(sin(a), 1.0f, 1.0f);

		actor->setPosition(sin(a), 0.0f, actor->getPosition().z);
    actor->setRotation(0.0f, 1.0f, 0.0f, a);
		// Render.
		//engine->getWindow()->setColor(1.0f, 0.0f, 0.0f, 1.0f);
		//engine->draw();
		engine->getWindow()->swapBuffers(0);
	}

	engine->getWindow()->closeWindow();
	engine->GPU_Instance_->delete_shader_program();
	exit(EXIT_SUCCESS);	
}
