#include "PastorseEngine.h"
#include "PastorseMap.h"

int generateMap(lua_State * L)
{
	lua_Number n1 = lua_tonumber(L, 1);
	lua_Number n2 = lua_tonumber(L, 2);

	return 0;
}

int main(int argc, const char* argv[])
{

	std::shared_ptr<PastorseInput> input;
	std::shared_ptr<PastorseCamera> camera;
	std::unique_ptr<PastorseEngine> engine(PastorseEngine::getInstance());

	std::shared_ptr<PastorseGeometry> geoCube;
  std::shared_ptr<PastorseTexture> texture;

	std::shared_ptr<PastorseMaterial> matPalaInf;
	std::shared_ptr<PastorseMaterial> matPalaSup;
	std::shared_ptr<PastorseActor> palaInf[4];
	std::shared_ptr<PastorseActor> palaSup[4];

	std::shared_ptr<PastorseMaterial> matBarraExterna;
	std::shared_ptr<PastorseActor> barraExternaSuperior[10];
	std::shared_ptr<PastorseActor> barraExternaInferior[10];

	std::shared_ptr<PastorseMaterial> matBola;
	std::shared_ptr<PastorseActor> bola;

	//std::shared_ptr<PastorseMap> map(new PastorseMap);

	float32 movement = 0.0f;
	float32 color = 0.0f;
	char8 goDown = false;

  float32 input_W_S = 0.0f;
  float32 input_A_D = 0.0f;
  float32 input_Left_Right = 0.0f;

	engine->init(800, 600, "Pastorse Ultra Engine");
	input = engine->createInput();

	/// Geometria para todos los actores
	geoCube = engine->createGeometry();
	geoCube->createPlane(1.0f);

  texture = engine->createTexture();
  texture->loadTexture("../_assets/texture2.png");
  //texture->loadTexture("texture2.png");

	// Paletas
	matPalaInf = engine->createMaterial();
	matPalaInf->initMaterial();
	matPalaInf->setTexture(texture);
	matPalaInf->setColor(0.0f, 1.0f, 0.0f, 0);

	matPalaSup = engine->createMaterial();
	matPalaSup->initMaterial();
  matPalaSup->setTexture(texture);
	matPalaSup->setColor(0.0f, 0.0f, 1.0f, 0);

	for (int i = 0; i < 4; i++){
		palaInf[i] = engine->createActor();
		palaInf[i]->setGeometry(geoCube);
		palaInf[i]->setMaterial(matPalaInf);
		palaInf[i]->setPosition(i * 2.0f, 0.0f, 0.0f);

		palaSup[i] = engine->createActor();
		palaSup[i]->setGeometry(geoCube);
		palaSup[i]->setMaterial(matPalaSup);
		palaSup[i]->setPosition(i * 2.0f, 10.0f, 0.0f);
	}

	// Parte superior e inferior de la escena
	matBarraExterna = engine->createMaterial();
	matBarraExterna->initMaterial();
  matBarraExterna->setTexture(texture);

	matBarraExterna->setColor(1.0f, 0.0f, 0.0f, 0);

	for (int i = 0; i < 10; i++){
		barraExternaSuperior[i] = engine->createActor();
		barraExternaSuperior[i]->setGeometry(geoCube);
		barraExternaSuperior[i]->setMaterial(matBarraExterna);
		barraExternaSuperior[i]->setPosition((i * 2.0f) - 6.0f, 12.0f, 0.0f);

		barraExternaInferior[i] = engine->createActor();
		barraExternaInferior[i]->setGeometry(geoCube);
		barraExternaInferior[i]->setMaterial(matBarraExterna);
		barraExternaInferior[i]->setPosition((i * 2.0f) - 6.0f, -2.0f, 0.0f);
	}

	/// Bola
	matBola = engine->createMaterial();
	matBola->initMaterial();
  matBola->setTexture(texture);
  matBola->setColor(0.0f, 0.0f, 1.0f,1);

	bola = engine->createActor();
	bola->setGeometry(geoCube);
	bola->setMaterial(matBola);

	palaInf[2]->addChild(bola);
	bola->setPosition(-1.0f, 2.0f, 0.0f);

	camera = engine->createCamera();
  camera->setLookProjection(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

	while (!engine->getWindow()->isClosedWindow())
	{
    engine->getWindow()->frameTime();
	  engine->getWindow()->pollEvents();

	// Input

    if (input->getKey(kKey_A)){
      input_A_D -= 10.0f * engine->getWindow()->getDeltaTime();
    }

	if (input->getKey(kKey_S)){
    input_W_S -= 10.0f * engine->getWindow()->getDeltaTime();
    }

	if (input->getKey(kKey_D)){
    input_A_D += 10.0f * engine->getWindow()->getDeltaTime();
    }

	if (input->getKey(kKey_W)){
    input_W_S += 10.0f * engine->getWindow()->getDeltaTime();
    }

	if (input->getSpecialKey(kSpecial_Key_Down)){
    input_Left_Right += 10.0f * engine->getWindow()->getDeltaTime();
    }

	if (input->getSpecialKey(kSpecial_Key_Up)){
    input_Left_Right -= 10.0f * engine->getWindow()->getDeltaTime();
    }

	camera->setLookUp(glm::vec3(input_A_D, input_W_S, input_Left_Right + 20.0f), glm::vec3(input_A_D, input_W_S, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		// Update
		/*if (!goDown && input->getSpace()){
			palaInf[2]->removeChild(bola);
			movement += 0.001f;
			color += 0.001f;
			bola->setPosition(palaInf[2]->getPosition().x, 2.0f + movement, 0.0f);
			matBola->setColor(color, color, color, 1);
			if (movement >= 6.0f){
				bola->setPosition(-1.0f, -2.0f, 0.0f);
				goDown = true;
				input->setSpace(false);
				palaSup[2]->addChild(bola);
				movement = 0.0f;

			}
		}
		else if (goDown && input->getSpace()){
			palaSup[2]->removeChild(bola);
			movement -= 0.001f;
			color -= 0.001f;
			bola->setPosition(palaSup[2]->getPosition().x, 8.0f + movement, 0.0f);
			matBola->setColor(color, color, color, 1);
			if (movement <= -6.0f){
				bola->setPosition(-1.0f, 2.0f, 0.0f);
				goDown = false;
				input->setSpace(false);
				palaInf[2]->addChild(bola);
				movement = 0.0f;
			}
		}*/

		/*for (int i = 0; i < 4; i++){
			palaInf[i]->setPosition((i * 2) + input->getT(), 0.0f, 0.0f);
			palaSup[i]->setPosition((i * 2) + input->getR(), 10.0f, 0.0f);
		}*/

		engine->draw();
		engine->getWindow()->swapBuffers(0);
	}

	engine->getWindow()->closeWindow();
	exit(EXIT_SUCCESS);
}
