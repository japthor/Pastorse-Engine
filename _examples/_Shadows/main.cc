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

struct TempleData {
	std::shared_ptr<PastorseGeometry> geo;
	std::shared_ptr<PastorseMaterial> mat;
    std::shared_ptr<PastorseTexture> texture;
	std::shared_ptr<PastorseLight> light;
	std::shared_ptr<PastorseActor> actor[200]; //8 * 8 + 7 * 7 + 6 * 6 + 5 * 5 + 4 * 4 + 3 * 3

    std::shared_ptr<PastorseMaterial> matPos;

	int32 size;
	int32 totalActors = 8 * 8 + 7 * 7 + 6 * 6 + 5 * 5 + 4 * 4 + 3 * 3;
} temple;

struct GroundData{
	std::shared_ptr<PastorseGeometry> geo;
	std::shared_ptr<PastorseMaterial> mat;
	std::shared_ptr<PastorseTexture> texture;
	std::shared_ptr<PastorseLight> light;
	std::shared_ptr<PastorseActor> actor;
} ground;

struct R2D2{
	std::shared_ptr<PastorseGeometry> geometryR2D2;
	std::shared_ptr<PastorseMaterial> materialR2D2;
	std::shared_ptr<PastorseActor> actorR2D2;

	std::shared_ptr<PastorseTexture> texture;
	std::string loc;
} r2d2;


void initTemple(){
	temple.size = 2;

	temple.geo = engine->createGeometry();
	temple.geo->createCube("MyCube", (float)temple.size / 2);

	temple.matPos = engine->createMaterial();
	temple.matPos->initMaterial(kShaderType_RenderPosition);

    temple.texture = engine->createTexture();
    temple.texture->loadTexture("../_assets/texture2.png");

	temple.mat = engine->createMaterial();
	temple.mat->initMaterial(kShaderType_TestSpotDirectionalLight_Texture);
    temple.mat->setTexture(temple.texture);

	temple.light = engine->createLight();
	temple.light->setDirectionalLightDirection(glm::vec3(10.0f, -10.0f, -5.0f));
	temple.light->setDirectionalLightColor(glm::vec3(0.9f, 0.9f, 0.9f));
	temple.mat->setLight(temple.light);

  for (int32 i = 0; i < temple.totalActors; i++){
	  temple.actor[i] = engine->createActor();
	  temple.actor[i]->setGeometry(temple.geo);
	  temple.actor[i]->setMaterial(temple.mat);
	  temple.actor[i]->setSpecialMaterial(temple.matPos);
  }
}

void initFloor(){
	ground.geo = engine->createGeometry();
	ground.geo->createCube("MyCube", 2.0f);

	ground.texture = engine->createTexture();
	ground.texture->loadTexture("../_assets/grass.png");

	ground.mat = engine->createMaterial();
	ground.mat->initMaterial(kShaderType_TestSpotDirectionalLight_Texture);
	ground.mat->setTexture(ground.texture);

	ground.light = engine->createLight();
	ground.light->setDirectionalLightDirection(glm::vec3(10.0f, -10.0f, -5.0f));
	ground.light->setDirectionalLightColor(glm::vec3(1.0f, 0.9f, 0.9f));
	ground.light->setSpotLightColor(glm::vec3(10.0f, 0.2f, 0.9f),0);
	ground.light->setSpotLightPosition(glm::vec3(-30.0f, 32.0f, 0.0f),0);
	ground.light->setSpotLightDirection(glm::vec3(1.0f, -1.0f, 0.0f),0);


	ground.mat->setLight(ground.light);

	ground.actor = engine->createActor();
	ground.actor->setGeometry(ground.geo);
	ground.actor->setMaterial(ground.mat);
	ground.actor->setSpecialMaterial(temple.matPos);
	ground.actor->setPosition(0.0f, 11.9f, 0.0f);
	ground.actor->setScale(20.0f, 0.0f, 20.0f);
}


void initR2D2(){
	r2d2.materialR2D2 = engine->createMaterial();
	r2d2.materialR2D2->initMaterial(kShaderType_Texture);
	
	r2d2.geometryR2D2 = engine->createGeometry();
	//r2d2.geometryR2D2->createCube("MyCube", 10);

	r2d2.actorR2D2 = engine->createActor();
	r2d2.actorR2D2->setGeometry(r2d2.geometryR2D2);
	r2d2.actorR2D2->setMaterial(r2d2.materialR2D2);
	r2d2.actorR2D2->setSpecialMaterial(r2d2.materialR2D2);

	//r2d2.actorR2D2->loadOBJ("../_assets/Earth/Earth.obj");

	r2d2.texture = engine->createTexture();
	r2d2.texture->loadTexture(r2d2.actorR2D2->loadOBJ("../_assets/Earth/Earth.obj").c_str());

	r2d2.materialR2D2->setTexture(r2d2.texture);

	r2d2.actorR2D2->setScale(10.0f, 10.0f, 10.0f);
	r2d2.actorR2D2->setPosition(-20.0f,50.0f,0.0f);

}



void createFirstFloor(float32 x, float32 y, float32 z){
	for (int32 i = 0; i < 8; i++){
		for (int32 j = 0; j < 8; j++){
			temple.actor[i * 8 + j]->setPosition(i *temple.size + ((x * temple.size) / 2), (y * temple.size) / 2, j * temple.size + ((z * temple.size) / 2));
		}
	}
}

void createSecondFloor(float32 x, float32 y, float32 z){
	for (int32 i = 0; i < 7; i++){
		for (int32 j = 0; j < 7; j++){
			temple.actor[(i * 7 + j) + (8 * 8)]->setPosition((i*temple.size) + ((x * temple.size) / 2), (y * temple.size) / 2, (j*temple.size) + ((z * temple.size) / 2));
		}
	}
}

void createThirdFloor(float32 x, float32 y, float32 z){
	for (int32 i = 0; i < 6; i++){
		for (int32 j = 0; j < 6; j++){
			temple.actor[(i * 6 + j) + (7 * 7) + (8 * 8)]->setPosition((i*temple.size) + ((x * temple.size) / 2), (y * temple.size) / 2, (j*temple.size) + ((z * temple.size) / 2));
		}
	}
}

void createFourthFloor(float32 x, float32 y, float32 z){
	for (int32 i = 0; i < 5; i++){
		for (int32 j = 0; j < 5; j++){
			temple.actor[(i * 5 + j) + (8 * 8) + (7 * 7) + (6 * 6)]->setPosition((i*temple.size) + ((x * temple.size) / 2), (y * temple.size) / 2, (j*temple.size) + ((z * temple.size) / 2));
		}
	}
}

void createFifthFloor(float32 x, float32 y, float32 z){
	for (int32 i = 0; i < 4; i++){
		for (int32 j = 0; j < 4; j++){
			temple.actor[(i * 4 + j) + (8 * 8) + (7 * 7) + (6 * 6) + (5 * 5)]->setPosition((i*temple.size) + ((x * temple.size) / 2), (y * temple.size) / 2, (j*temple.size) + ((z * temple.size) / 2));
		}
	}
}

void createSixthFloor(float32 x, float32 y, float32 z){
	for (int32 i = 0; i < 3; i++){
		for (int32 j = 0; j < 3; j++){
			temple.actor[(i * 3 + j) + (8 * 8) + (7 * 7) + (6 * 6) + (5 * 5) + (4 * 4)]->setPosition((i*temple.size) + ((x * temple.size) / 2), (y * temple.size) / 2, (j*temple.size) + ((z * temple.size) / 2));
    }
  }
}

void setScale(float32 scale){
	for (int32 i = 0; i < temple.totalActors; i++){
		temple.actor[i]->setScale(scale, scale, scale);
		temple.size = (int32)scale * 2;
	}
}


void moveTemple(float32 x, float32 y, float32 z){
	for (int32 i = 0; i < temple.totalActors; i++){
		temple.actor[i]->setPosition(temple.actor[i]->getPosition().x + x, temple.actor[i]->getPosition().y + y, temple.actor[i]->getPosition().z + z);
  }
}

void setLightColor(float32 x, float32 y, float32 z){
	ground.light->setDirectionalLightColor(glm::vec3(x, y, z));
}

void setLightPosition(float32 x, float32 y, float32 z){
	ground.light->setPointLightPosition(glm::vec3(x, y, z));
}

void setLightDirection(float32 x, float32 y, float32 z){
	temple.light->setDirectionalLightDirection(glm::vec3(x, y, z));
}

int32 createFirstFloor(lua_State * L)
{

	lua_Number n1 = (float32)lua_tonumber(L, 1);
	lua_Number n2 = (float32)lua_tonumber(L, 2);
	lua_Number n3 = (float32)lua_tonumber(L, 3);

	createFirstFloor(n1, n2, n3);
	return 0;
}

int32 createSecondFloor(lua_State * L)
{

	lua_Number n1 = (float32)lua_tonumber(L, 1);
	lua_Number n2 = (float32)lua_tonumber(L, 2);
	lua_Number n3 = (float32)lua_tonumber(L, 3);

	createSecondFloor(n1, n2, n3);
	return 0;
}

int32 createThirdFloor(lua_State * L)
{

	lua_Number n1 = (float32)lua_tonumber(L, 1);
	lua_Number n2 = (float32)lua_tonumber(L, 2);
	lua_Number n3 = (float32)lua_tonumber(L, 3);

	createThirdFloor(n1, n2, n3);
	return 0;
}

int32 createFourthFloor(lua_State * L)
{

	lua_Number n1 = (float32)lua_tonumber(L, 1);
	lua_Number n2 = (float32)lua_tonumber(L, 2);
	lua_Number n3 = (float32)lua_tonumber(L, 3);

	createFourthFloor(n1, n2, n3);
	return 0;
}

int32 createFifthFloor(lua_State * L)
{

	lua_Number n1 = (float32)lua_tonumber(L, 1);
	lua_Number n2 = (float32)lua_tonumber(L, 2);
	lua_Number n3 = (float32)lua_tonumber(L, 3);

	createFifthFloor(n1, n2, n3);
	return 0;
}


int32 createSixthFloor(lua_State * L)
{
	lua_Number n1 = (float32)lua_tonumber(L, 1);
	lua_Number n2 = (float32)lua_tonumber(L, 2);
	lua_Number n3 = (float32)lua_tonumber(L, 3);

	 createSixthFloor(n1, n2, n3);
 return 0;
}

int32 setScale(lua_State * L){
	lua_Number n1 = (float32)lua_tonumber(L, 1);

	 setScale(n1);
	 return 0;
}

int32 moveTemple(lua_State * L)
{
	lua_Number n1 = (float32)lua_tonumber(L, 1);
	lua_Number n2 = (float32)lua_tonumber(L, 2);
	lua_Number n3 = (float32)lua_tonumber(L, 3);
	moveTemple(n1, n2, n3);
	return 0;
}

int32 setLightColor(lua_State * L){
	lua_Number n1 = (float32)lua_tonumber(L, 1);
	lua_Number n2 = (float32)lua_tonumber(L, 2);
	lua_Number n3 = (float32)lua_tonumber(L, 3);
	setLightColor(n1, n2, n3);
	return 0;
}

int32 setLightPosition(lua_State * L){
	lua_Number n1 = (float32)lua_tonumber(L, 1);
	lua_Number n2 = (float32)lua_tonumber(L, 2);
	lua_Number n3 = (float32)lua_tonumber(L, 3);
	setLightPosition(n1, n2, n3);
	return 0;
}

int32 setLightDirection(lua_State * L){
	lua_Number n1 = (float32)lua_tonumber(L, 1);
	lua_Number n2 = (float32)lua_tonumber(L, 2);
	lua_Number n3 = (float32)lua_tonumber(L, 3);
	setLightDirection(n1, n2, n3);
	return 0;
}

void updateThread(){

  /// Init Lua
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  // Temple
  lua_register(L, "createFirstFloor", createFirstFloor);
  lua_register(L, "createSecondFloor", createSecondFloor);
  lua_register(L, "createThirdFloor", createThirdFloor);
  lua_register(L, "createFourthFloor", createFourthFloor);
  lua_register(L, "createFifthFloor", createFifthFloor);
  lua_register(L, "createSixthFloor", createSixthFloor);
  lua_register(L, "setScale", setScale);
  lua_register(L, "moveTemple", moveTemple);

  // Floor
  lua_register(L, "setLightColor", setLightColor);
  lua_register(L, "setLightPosition", setLightPosition);
  lua_register(L, "setLightDirection", setLightDirection);

  // Files
  luaL_dofile(L, "../_assets/init.lua");
  luaL_dofile(L, "../_assets/update.lua");

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


    /// Lua
    if (init.input->getKey(kKey_I)){
      luaL_dofile(L, "../_assets/init.lua");
    }

    if (init.input->getKey(kKey_U)){
      luaL_dofile(L, "../_assets/update.lua");
    }

    lua_getglobal(L, "update");
    lua_pushnumber(L, 0.016f);
    lua_call(L, 1, 0);

    glm::vec3 light_dir = normalize(glm::vec3(10.0, -10.0, -5.0));
    glm::vec3 light_pos = glm::vec3(-50.0f, 55.0f, 30.0f);

    // Camera
    init.camera->setLookUp(glm::vec3(init.input_A_D, init.input_W_S, init.input_Left_Right + 20.0f), glm::vec3(init.input_A_D, init.input_W_S, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    init.camera_2->setLookUp(light_pos, light_pos + light_dir, glm::vec3(0.0f, 1.0f, 0.0f));

    glm::vec3 light_dir_spot = normalize(glm::vec3(1.0, -1.0, 0.0));
    glm::vec3 light_pos_spot = glm::vec3(-30.0f, 32.0f, 0.0f);

	init.camera_3->setLookUp(light_pos_spot, light_pos_spot + light_dir_spot, glm::vec3(0.0f, 1.0f, 0.0f));
  }
  lua_close(L);

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
  init.camera_2->setOrthoProjection(0.1f,120.0f);

  init.camera_3 = engine->createCamera();
  init.camera_3->setOrthoProjection(0.1f, 120.0f);

  //init.camera_3 = engine->createCamera();
  //init.camera_3->setLookProjection(25.0f, 800.0f / 600.0f, 15.0f, 500.0f);

  /// Temple Lua
  initTemple();

  /// Floor Lua
  initFloor();

  /// Test Obj
  initR2D2();

  //engine->launchThread();
  std::thread* u_thread = new std::thread(&updateThread);
  float a = 0.0f;
	while (!engine->getWindow()->isClosedWindow())
	{

    /// Init
    engine->getWindow()->pollEvents();


    if (init.input->getKey(kKey_0)){
      engine->id_camera = 0;
    }

    if (init.input->getKey(kKey_1)){
      engine->id_camera = 1;
    }

	if (init.input->getKey(kKey_2)){
		engine->id_camera = 2;
	}

	


    /// Draw
	engine->draw();

  }
	engine->getWindow()->closeWindow();
	exit(EXIT_SUCCESS);
}
