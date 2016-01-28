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
	std::unique_ptr<PastorseEngine> engine;

	std::shared_ptr<PastorseGeometry> geometry_1[3];
	std::shared_ptr<PastorseMaterial> material_1[3];
	std::shared_ptr<PastorseActor> actor_1[3];

	std::shared_ptr<PastorseGeometry> geometry_2[4];
	std::shared_ptr<PastorseMaterial> material_2[3];
	std::shared_ptr<PastorseActor> actor_2[3];

	std::shared_ptr<PastorseGeometry> geometry_3[4];
	std::shared_ptr<PastorseMaterial> material_3[3];
	std::shared_ptr<PastorseActor> actor_3[3];

	float a = 0.0f;
	engine = CREATE_UNIQUE_PTR(PastorseEngine);
	engine->init(800, 600, "Pastorse Ultra Engine");
	input = engine->createInput();

	for (int i = 0; i < 3; i++){
		material_1[i] = engine->createMaterial();
		material_1[i]->initMaterial();
		material_1[i]->uploadTexture("../_assets/texture2.png");

		geometry_1[i] = engine->createGeometry();
		geometry_1[i]->createCube("cube1", 1.0f);

		actor_1[i] = engine->createActor();
		actor_1[i]->setGeometry(geometry_1[i]);
		actor_1[i]->setMaterial(material_1[i]);
		actor_1[i]->setPosition((i * 3.0f) - 3.0f , 0.0f, 0.0f);

		material_2[i] = engine->createMaterial();
		material_2[i]->initMaterial();
		material_2[i]->uploadTexture("../_assets/texture2.png");

		geometry_2[i] = engine->createGeometry();
		geometry_2[i]->createCube("cube2", 1.0f);

		actor_2[i] = engine->createActor();
		actor_2[i]->setGeometry(geometry_2[i]);
		actor_2[i]->setMaterial(material_2[i]);
		actor_2[i]->setPosition((i * 6.0f) - 6.0f, 3.0f, 0.0f);
		actor_2[i]->addChild(actor_1[i]);

		material_3[i] = engine->createMaterial();
		material_3[i]->initMaterial();
		material_3[i]->uploadTexture("../_assets/texture2.png");

		geometry_3[i] = engine->createGeometry();
		geometry_3[i]->createCube("cube3", 1.0f);

		actor_3[i] = engine->createActor();
		actor_3[i]->setGeometry(geometry_3[i]);
		actor_3[i]->setMaterial(material_3[i]);
		actor_3[i]->setPosition((i * 9.0f) - 9.0f, 6.0f, 0.0f);
		actor_3[i]->addChild(actor_2[i]);
	}

	camera = engine->createCamera();

	//engine->thread();
	while (!engine->getWindow()->isClosedWindow())
	{
		a += 0.01f;
		input->keyInput(engine->getWindow()->getWindow());
		engine->getWindow()->pollEvents();


		// Input
		camera->setLookUp(glm::vec3(input->getX(), input->getY(), input->getZ()), glm::vec3(input->getX(), input->getY(), -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		camera->setLookProjection(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

		// Update
		for (int i = 0; i < 3; i++){

			actor_3[i]->setRotation(0.0f, 1.0f, 1.0f, a);
			material_3[i]->setColor(1.0f, 1.0f, 1.0f);

			actor_2[i]->setPosition(0.0f, -5.0f, 0.0f);
			material_2[i]->setColor(0.0f, 0.0f, 1.0f);

			actor_1[i]->setPosition(0.0f, -5.0f, 0.0f);
			material_1[i]->setColor(0.0f, 1.0f, 0.0f);
		}

		// Render.
		/// Engine.h does it for u.
		engine->getWindow()->swapBuffers(0);
	}

	engine->getWindow()->closeWindow();

	for (int i = 0; i < 3; i++){
		geometry_1[i]->deleteBuffers();
	}

	engine->GPU_Instance_->delete_shader_program();
	exit(EXIT_SUCCESS);
}
