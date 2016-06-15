#include "PastorseEngine.h"

std::unique_ptr<PastorseEngine> engine(PastorseEngine::getInstance());

struct Init{
	std::shared_ptr<PastorseInput> input;
	std::shared_ptr<PastorseCamera> camera;
	std::shared_ptr<PastorseCamera> camera_2;
	std::shared_ptr<PastorseCamera> camera_3;


	float32 input_W_S = 30.0f;
	float32 input_A_D = 0.0f;
	float32 input_Left_Right = 1.0f;

}init;

struct Earth{
	std::shared_ptr<PastorseGeometry> geometryEarth;
	std::shared_ptr<PastorseMaterial> materialEarth;
	std::shared_ptr<PastorseActor> actorEarth;

	std::shared_ptr<PastorseTexture> texture;
	std::string loc;
} earth;

struct Sun{
	std::shared_ptr<PastorseGeometry> geometryEarth;
	std::shared_ptr<PastorseMaterial> materialEarth;
	std::shared_ptr<PastorseActor> actorEarth;

	std::shared_ptr<PastorseTexture> texture;
	std::string loc;
} sun;

struct Moon{
	std::shared_ptr<PastorseGeometry> geometryEarth;
	std::shared_ptr<PastorseMaterial> materialEarth;
	std::shared_ptr<PastorseActor> actorEarth;

	std::shared_ptr<PastorseTexture> texture;
	std::string loc;
} moon;


void initEarth(){
	earth.materialEarth = engine->createMaterial();
	earth.materialEarth->initMaterial(kShaderType_Texture);

	earth.geometryEarth = engine->createGeometry();

	earth.actorEarth = engine->createActor();
	earth.actorEarth->setGeometry(earth.geometryEarth);
	earth.actorEarth->setMaterial(earth.materialEarth);


	earth.texture = engine->createTexture();
	earth.texture->loadTexture(earth.actorEarth->loadOBJ("../_assets/Earth/Earth.obj").c_str());

	earth.materialEarth->setTexture(earth.texture);

	earth.actorEarth->setScale(5.0f, 5.0f, 5.0f);
	earth.actorEarth->setPosition(-20.0f, 40.0f, 0.0f);
	earth.materialEarth->setColor(0.0f, 1.0f, 0.0f);

}

void initSun(){
	sun.materialEarth = engine->createMaterial();
	sun.materialEarth->initMaterial(kShaderType_Texture);

	sun.geometryEarth = engine->createGeometry();

	sun.actorEarth = engine->createActor();
	sun.actorEarth->setGeometry(sun.geometryEarth);
	sun.actorEarth->setMaterial(sun.materialEarth);


	sun.texture = engine->createTexture();
	sun.texture->loadTexture(sun.actorEarth->loadOBJ("../_assets/Earth/Earth.obj").c_str());

	sun.materialEarth->setTexture(sun.texture);

	sun.actorEarth->setScale(10.0f, 10.0f, 10.0f);
	sun.actorEarth->setPosition(0.0f, 40.0f, 0.0f);
	sun.materialEarth->setColor(1.0f, 1.0f, 0.0f);

}

void initMoon(){
	moon.materialEarth = engine->createMaterial();
	moon.materialEarth->initMaterial(kShaderType_Texture);

	moon.geometryEarth = engine->createGeometry();

	moon.actorEarth = engine->createActor();
	moon.actorEarth->setGeometry(moon.geometryEarth);
	moon.actorEarth->setMaterial(moon.materialEarth);


	moon.texture = engine->createTexture();
	moon.texture->loadTexture(moon.actorEarth->loadOBJ("../_assets/Earth/Earth.obj").c_str());

	moon.materialEarth->setTexture(moon.texture);

	moon.actorEarth->setScale(10.0f, 10.0f, 10.0f);
	moon.actorEarth->setPosition(0.0f, 40.0f, 0.0f);
	moon.materialEarth->setColor(0.0f, 0.0f, 1.0f);

}

void updateThread(){

	float a = 0.0f;

	while (!engine->getWindow()->isClosedWindow())
	{
		/// Update Delta Time
		engine->getWindow()->frameTime();

		// Input
		if (init.input->getKey(kKey_A)){
			init.input_A_D -= 10.0f * engine->getWindow()->getDeltaTime();
		}

		if (init.input->getKey(kKey_S)){
			init.input_W_S -= 10.0f * engine->getWindow()->getDeltaTime();
		}

		if (init.input->getKey(kKey_D)){
			init.input_A_D += 10.0f * engine->getWindow()->getDeltaTime();
		}

		if (init.input->getKey(kKey_W)){
			init.input_W_S += 10.0f * engine->getWindow()->getDeltaTime();
		}

		if (init.input->getSpecialKey(kSpecial_Key_Down)){
			init.input_Left_Right += 10.0f * engine->getWindow()->getDeltaTime();
		}

		if (init.input->getSpecialKey(kSpecial_Key_Up)){
			init.input_Left_Right -= 10.0f * engine->getWindow()->getDeltaTime();
		}

		a += 0.00001f;
		

		// Camera
		init.camera->setLookUp(glm::vec3(init.input_A_D, init.input_W_S, init.input_Left_Right + 20.0f), glm::vec3(init.input_A_D, init.input_W_S, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	
		sun.actorEarth->setRotation(0.0f, 1.0f, 0.0f,a);
		earth.actorEarth->setRotation(0.0f, 1.0f, 0.0f, a);
		
	}


}


int main(int argc, const char* argv[])
{
	/// Init
	engine->init(800, 600, "Pastorse Ultra Engine");
	engine->id_camera = 0;
	/// Input
	init.input = engine->createInput();


	/// Camera
	init.camera = engine->createCamera();
	init.camera->setLookProjection(45.0f, 800.0f / 600.0f, 0.1f, 120.0f);

	init.camera_2 = engine->createCamera();
	init.camera_3 = engine->createCamera();

	/// Test Obj
	initEarth();
	initSun();
	initMoon();

	sun.actorEarth->addChild(earth.actorEarth);
	earth.actorEarth->addChild(moon.actorEarth);

	earth.actorEarth->setPosition(-2.0f, 0.0f, 0.0f);
	earth.actorEarth->setScale(0.7f,0.7f,0.7f);

	moon.actorEarth->setPosition(-1.0f, 0.0f, 0.0f);
	moon.actorEarth->setScale(0.5f, 0.5f, 0.5f);


	
	//engine->launchThread();
	std::thread* u_thread = new std::thread(&updateThread);

	while (!engine->getWindow()->isClosedWindow())
	{

		/// Init
		engine->getWindow()->pollEvents();


	




		/// Draw
		engine->draw();

	}
	engine->getWindow()->closeWindow();
	exit(EXIT_SUCCESS);
}
