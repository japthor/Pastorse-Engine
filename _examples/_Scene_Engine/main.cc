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

	std::shared_ptr<PastorseGeometry> geometry_1[4];
	std::shared_ptr<PastorseMaterial> material_1[4];
	std::shared_ptr<PastorseActor> pala_inf[4];

	std::shared_ptr<PastorseGeometry> geometry_2[4];
	std::shared_ptr<PastorseMaterial> material_2[4];
	std::shared_ptr<PastorseActor> pala_sup[4];

	std::shared_ptr<PastorseGeometry> geometry_3;
	std::shared_ptr<PastorseMaterial> material_3;
	std::shared_ptr<PastorseActor> bola;

	std::shared_ptr<PastorseGeometry> geometry_4[10];
	std::shared_ptr<PastorseMaterial> material_4[10];
	std::shared_ptr<PastorseActor> actor_4[10];

	std::shared_ptr<PastorseGeometry> geometry_5[10];
	std::shared_ptr<PastorseMaterial> material_5[10];
	std::shared_ptr<PastorseActor> actor_5[10];

	float a = 0.0f;
  float b = 0.0f;
	float color = 0.0f;
	bool goDown = false;
  bool removeChildBola = false;

	engine = CREATE_UNIQUE_PTR(PastorseEngine);
	engine->init(800, 600, "Pastorse Ultra Engine");
	input = engine->createInput();

	for (int i = 0; i < 4; i++){
		material_1[i] = engine->createMaterial();
		material_1[i]->initMaterial();
		material_1[i]->uploadTexture("../_assets/texture2.png");

		geometry_1[i] = engine->createGeometry();
		geometry_1[i]->createCube("cube1", 1.0f);

		pala_inf[i] = engine->createActor();
		pala_inf[i]->setGeometry(geometry_1[i]);
		pala_inf[i]->setMaterial(material_1[i]);
		pala_inf[i]->setPosition(i * 2.0f , 5.0f, 0.0f);

		material_2[i] = engine->createMaterial();
		material_2[i]->initMaterial();
		material_2[i]->uploadTexture("../_assets/texture2.png");

		geometry_2[i] = engine->createGeometry();
		geometry_2[i]->createCube("cube2", 1.0f);

		pala_sup[i] = engine->createActor();
		pala_sup[i]->setGeometry(geometry_2[i]);
		pala_sup[i]->setMaterial(material_2[i]);
		pala_sup[i]->setPosition(i * 2, 10.0f, 0.0f);
	}

  material_3 = engine->createMaterial();
  material_3->initMaterial();
  material_3->uploadTexture("../_assets/texture2.png");
  material_3->setColor(0.1, 0.1, 0.1, 1);

  geometry_3 = engine->createGeometry();
  geometry_3->createCube("cube3", 1.0f);

  bola = engine->createActor();
  bola->setGeometry(geometry_3);
  bola->setMaterial(material_3);
  bola->setPosition(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < 10; i++){

		material_4[i] = engine->createMaterial();
		material_4[i]->initMaterial();
		material_4[i]->uploadTexture("../_assets/texture2.png");

		geometry_4[i] = engine->createGeometry();
		geometry_4[i]->createCube("cube3", 1.0f);

		actor_4[i] = engine->createActor();
		actor_4[i]->setGeometry(geometry_4[i]);
		actor_4[i]->setMaterial(material_4[i]);
		actor_4[i]->setPosition((i * 2) - 6, 12.0f, 0.0f);

		material_5[i] = engine->createMaterial();
		material_5[i]->initMaterial();
		material_5[i]->uploadTexture("../_assets/texture2.png");

		geometry_5[i] = engine->createGeometry();
		geometry_5[i]->createCube("cube3", 1.0f);

		actor_5[i] = engine->createActor();
		actor_5[i]->setGeometry(geometry_5[i]);
		actor_5[i]->setMaterial(material_5[i]);
		actor_5[i]->setPosition((i * 2) - 6, -2.0f, 0.0f);
	}

  pala_inf[2]->addChild(bola);
  bola->setPosition(0.0f, 2.0f, 0.0f);
   

	camera = engine->createCamera();


	//engine->thread();
	while (!engine->getWindow()->isClosedWindow())
	{
		input->keyInput(engine->getWindow()->getWindow());
		engine->getWindow()->pollEvents();


		// Input
		camera->setLookUp(glm::vec3(input->getX(), input->getY(), input->getZ() + 10.0f), glm::vec3(input->getX(), input->getY(), -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		camera->setLookProjection(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

		// Update
		if (input->getSpace()){
			if (!goDown && input->getSpace()){
        pala_inf[2]->removeChild(bola);
				a += 0.1f;
				//actor_5[0]->addChild(bola);
				color += 0.01f;
				bola->setPosition(pala_inf[2]->getPosition().x, 2.0f + a, 0.0f);
				material_3->setColor(color + 0.1f, color + 0.1f, color + 0.1f, 1);
				if (a >= 6.0f){
          bola->setPosition(0.0f, -2.0f , 0.0f);
					goDown = true;
					input->setSpace(false);
          pala_sup[2]->addChild(bola);
          b = 0.f;
          //bola->setPosition(0.0f, -2.0f, 0.0f);
				}
			}
			else if (goDown && input->getSpace()){
        pala_sup[2]->removeChild(bola);
        b -= 0.1f;
        color -= 0.01f;
				//actor_4[0]->addChild(bola);
        bola->setPosition(pala_sup[2]->getPosition().x, 8.0f + b, 0.0f);
				material_3->setColor(color + 0.1f, color + 0.1f, color + 0.1f, 1);
				if (b <= -6.0f){
          bola->setPosition(0.0f, 2.0f, 0.0f);
					goDown = false;
					input->setSpace(false);
          pala_inf[2]->addChild(bola);
          a = 0.f;
          //bola->setPosition(0.0f, 2.0f, 0.0f);
				}
			}
		}

		for (int i = 0; i < 4; i++){
			pala_inf[i]->setPosition((i * 2) + input->getT(), 0.0f, 0.0f);
			pala_sup[i]->setPosition((i * 2) + input->getR(), 10.0f, 0.0f);
			material_2[i]->setColor(0.0f, 1.0f, 1.0f,0);
			material_1[i]->setColor(0.0f, 1.0f, 0.0f,0);
		}

		for (int i = 0; i < 10; i++){
			material_4[i]->setColor(1.0f, 0.0f, 0.0f,0);
			material_5[i]->setColor(1.0f, 0.0f, 0.0f,0);
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
