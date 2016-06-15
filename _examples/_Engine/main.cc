#include "PastorseEngine.h"

/* Anotation: 
   Sometimes there's and error about not generating the material or geometry 
   when you compile the project. It's because there are some bugs with the 
   threads system in PastorseEngine. Just compile it again. :)
*/

int main(int argc, const char* argv[])
{

	float angle = 0.0f;

	std::unique_ptr<PastorseInput> input;
	std::shared_ptr<PastorseCamera> camera;

	std::shared_ptr<PastorseGeometry> geometryR2D2;
	std::shared_ptr<PastorseGeometry> geometryCube;

	std::shared_ptr<PastorseMaterial> materialCube;
	std::shared_ptr<PastorseMaterial> materialR2D2;

	std::shared_ptr<PastorseActor> Cube;
	std::shared_ptr<PastorseActor> R2D2;

  std::shared_ptr<PastorseActor> cube2;

	std::unique_ptr<PastorseEngine> engine;

	engine = CREATE_UNIQUE_PTR(PastorseEngine);
	engine->init(800, 600, "Pastorse Ultra Engine");

	input = engine->createInput();
	camera = engine->createCamera();

	/// R2-D2
	materialR2D2 = engine->createMaterial();
	materialR2D2->initMaterial();

	geometryR2D2 = engine->createGeometry();
	R2D2 = engine->createActor();

	R2D2->setGeometry(geometryR2D2);
	R2D2->setMaterial(materialR2D2);
	R2D2->loadOBJ("../_assets/R2-D2/R2-D2.obj");

	R2D2->setPosition(0.0f, 0.0f, 5.0f);

	/// Cube
	materialCube = engine->createMaterial();
	materialCube->initMaterial();
	materialCube->uploadTexture("../_assets/texture2.png");

	geometryCube = engine->createGeometry();
	geometryCube->createCube("MyCube", 1.0f);

	Cube = engine->createActor();
	Cube->setGeometry(geometryCube);
	Cube->setMaterial(materialCube);

  /// Cube2
  cube2 = engine->createActor();
  cube2->setGeometry(geometryCube);
  cube2->setMaterial(materialCube);
  cube2->setPosition(3.0f, 2.0f, 0.0f);
  materialCube->setColor(0.0f, 1.0f, 0.0f, 0.0f);

	Cube->addChild(cube2);
  Cube->setScale(0.5f, 0.5f, 0.5f);
	while (!engine->getWindow()->isClosedWindow())
	{
		angle += 0.0001f;
		input->keyInput(engine->getWindow()->getWindow());
		engine->getWindow()->pollEvents();

    Cube->addChild(R2D2);
		
		// Input
		/// W,A,S,D,Up and Down Arrow.
		camera->setLookUp(glm::vec3(input->getX(), input->getY(),input->getZ()), glm::vec3(input->getX(), input->getY(), -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		camera->setLookProjection(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

		// Update
		R2D2->setRotation(0.0f, 1.0f, 0.0f, angle);

		Cube->setPosition(sin(angle), 0.0f, Cube->getPosition().z);
		Cube->setRotation(0.0f, 1.0f, 0.0f, angle);
		// Render.

    // TEMPORAAAAAAAAAALL
    engine->draw();
		engine->getWindow()->swapBuffers(0);
	}

	engine->getWindow()->closeWindow();
	engine->GPU_Instance_->delete_shader_program();
	exit(EXIT_SUCCESS);	
}
