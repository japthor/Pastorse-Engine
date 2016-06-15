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


struct Box {
	std::shared_ptr<PastorseGeometry> geo;
	std::shared_ptr<PastorseMaterial> mat[4];
    std::shared_ptr<PastorseTexture> texture;
	std::shared_ptr<PastorseActor> actor[35];

	std::shared_ptr<PastorseActor> boxCenter[7];
	std::shared_ptr<PastorseGeometry> geoCenter;

} box;

void InitBox(){
	box.geo = engine->createGeometry();
	box.geo->createCube("MyCube", 2.0f);

	box.geoCenter = engine->createGeometry();
	box.geoCenter->createCube("MyCube", 0.01f);

	box.texture = engine->createTexture();
	box.texture->loadTexture("../_assets/steel_wall.jpg");

	box.mat[0] = engine->createMaterial();
	box.mat[0]->initMaterial(kShaderType_Texture);
	box.mat[0]->setTexture(box.texture);

	for (unsigned int i = 0; i < 7; i++){
		box.boxCenter[i] = engine->createActor();
		box.boxCenter[i]->setPosition((i * 20.0f), 26.0f, 0.0f);
		
		box.boxCenter[i]->setGeometry(box.geoCenter);
		box.boxCenter[i]->setMaterial(box.mat[0]);
	}

	for (unsigned int i = 0; i < 20; i++){
		box.actor[i] = engine->createActor();
		box.actor[i]->setGeometry(box.geo);
		box.actor[i]->setMaterial(box.mat[0]);
		box.actor[i]->setScale(3.0f, 0.0f, 3.0f);
	}

	for (unsigned int i = 0; i < 4; i++){
		// 0
		box.actor[i * 5]->setPosition(0.0f , 0.0f, -5.0f);
		box.actor[i * 5]->setRotation(1.0f, 0.0f, 0.0f, 1.5f);
		box.boxCenter[i]->addChild(box.actor[i * 5]);
		// 1
		box.actor[(i * 5) + 1]->setPosition(0.0f, -6.0f, 0.0f);
		box.actor[(i * 5) + 1]->setRotation(1.0f, 1.0f, 1.0f, 0.0f);
		box.boxCenter[i]->addChild(box.actor[(i * 5) + 1]);
		// 2
		box.actor[(i * 5) + 2]->setPosition(0.0f, 6.0f, 0.0f);
		box.actor[(i * 5) + 2]->setRotation(1.0f, 1.0f, 1.0f, 0.0f);
		box.boxCenter[i]->addChild(box.actor[(i * 5) + 2]);
		// 3
		box.actor[(i * 5) + 3]->setPosition(6.0f , 0.0f, 0.0f);
		box.actor[(i * 5) + 3]->setRotation(0.0f, 0.0f, 1.0f, 1.58f);
		box.boxCenter[i]->addChild(box.actor[(i * 5) + 3]);
		// 4
		box.actor[(i * 5) + 4]->setPosition(-6.0f, 0.0f, 0.0f);
		box.actor[(i * 5) + 4]->setRotation(0.0f, 0.0f, 1.0f, 1.58f);
		box.boxCenter[i]->addChild(box.actor[(i * 5) + 4]);
	}

	
}

struct Scene1 {
	std::shared_ptr<PastorseGeometry> geo;
	std::shared_ptr<PastorseMaterial> mat;
	std::shared_ptr<PastorseTexture> texture;
	std::shared_ptr<PastorseActor> actor;
	float32 rotation = 0.0f;

} scene1;

void InitScene1(){
	scene1.geo = engine->createGeometry();
	scene1.geo->createCube("MyCube", 2.0f);

	scene1.texture = engine->createTexture();
	scene1.texture->loadTexture("../_assets/lava_rock.jpg");

	scene1.mat = engine->createMaterial();
	scene1.mat->initMaterial(kShaderType_Texture);
	scene1.mat->setTexture(scene1.texture);

	scene1.actor = engine->createActor();
	scene1.actor->setGeometry(scene1.geo);
	scene1.actor->setMaterial(scene1.mat);
}

struct Scene2{
	std::shared_ptr<PastorseGeometry> geometryEarth;
	std::shared_ptr<PastorseMaterial> materialEarth;
	std::shared_ptr<PastorseActor> actorEarth;

	std::shared_ptr<PastorseTexture> texture;
	std::string loc;

	float32 rotation = 0.0f;
} scene2;

void InitScene2(){
	scene2.materialEarth = engine->createMaterial();
	scene2.materialEarth->initMaterial(kShaderType_Texture);

	scene2.geometryEarth = engine->createGeometry();

	scene2.actorEarth = engine->createActor();
	scene2.actorEarth->setGeometry(scene2.geometryEarth);
	scene2.actorEarth->setMaterial(scene2.materialEarth);


	scene2.texture = engine->createTexture();
	scene2.texture->loadTexture(scene2.actorEarth->loadOBJ("../_assets/Earth/Earth.obj").c_str());

	scene2.materialEarth->setTexture(scene2.texture);
}

struct Scene3 {
	std::shared_ptr<PastorseGeometry> geo;
	std::shared_ptr<PastorseMaterial> mat;
	std::shared_ptr<PastorseTexture> texture;
	std::shared_ptr<PastorseActor> actor[3];
	float32 rotation_father = 0.0f;
	float32 rotatio_child = 0.0f;

} scene3;

void InitScene3(){
	scene3.geo = engine->createGeometry();
	scene3.geo->createCube("MyCube", 1.5f);

	scene3.texture = engine->createTexture();
	scene3.texture->loadTexture("../_assets/brick.jpg");

	scene3.mat = engine->createMaterial();
	scene3.mat->initMaterial(kShaderType_Texture);
	scene3.mat->setTexture(scene3.texture);

	scene3.actor[0] = engine->createActor();
	scene3.actor[0]->setGeometry(scene3.geo);
	scene3.actor[0]->setMaterial(scene3.mat);

    scene3.actor[1] = engine->createActor();
	scene3.actor[1]->setGeometry(scene3.geo);
	scene3.actor[1]->setMaterial(scene3.mat);

	scene3.actor[2] = engine->createActor();
	scene3.actor[2]->setGeometry(scene3.geo);
	scene3.actor[2]->setMaterial(scene3.mat);

	scene3.actor[0]->addChild(scene3.actor[1]);
	scene3.actor[0]->addChild(scene3.actor[2]);

	scene3.actor[1]->setPosition(3.0f,0.0f,0.0f);
	scene3.actor[1]->setScale(0.7f, 0.7f, 0.7f);

	scene3.actor[2]->setPosition(-3.0f, 0.0f, 0.0f);
	scene3.actor[2]->setScale(0.7f, 0.7f, 0.7f);


}

struct Scene4 {
	std::shared_ptr<PastorseGeometry> geo;
	std::shared_ptr<PastorseMaterial> mat;
	std::shared_ptr<PastorseTexture> texture;
	std::shared_ptr<PastorseActor> actor;
	std::shared_ptr<PastorseLight> light;
	float32 rotation = 0.0f;

} scene4;

void InitScene4(){
	scene4.geo = engine->createGeometry();
	scene4.geo->createCube("MyCube", 1.5f);

	scene4.texture = engine->createTexture();
	scene4.texture->loadTexture("../_assets/stone.jpg");

	scene4.mat = engine->createMaterial();
	scene4.mat->initMaterial(kShaderType_DirectionalLight_Texture);
	scene4.mat->setTexture(scene4.texture);

	scene4.light = engine->createLight();
	scene4.light->setDirectionalLightDirection(glm::vec3(10.0f, -10.0f, -5.0f));
	scene4.light->setDirectionalLightColor(glm::vec3(0.9f, 0.9f, 0.9f));
	scene4.mat->setLight(scene4.light);

	scene4.actor = engine->createActor();
	scene4.actor->setGeometry(scene4.geo);
	scene4.actor->setMaterial(scene4.mat);
}

struct Scene5 {
	std::shared_ptr<PastorseGeometry> geo;
	std::shared_ptr<PastorseMaterial> mat;
	std::shared_ptr<PastorseTexture> texture;
	std::shared_ptr<PastorseActor> actor;
	std::shared_ptr<PastorseLight> light;
	float32 rotation = 0.0f;
	float32 position = 0.0f;
	bool change = false;

} scene5;


void InitScene5(){

	box.mat[1] = engine->createMaterial();
	box.mat[1]->initMaterial(kShaderType_PointLight_Texture);
	box.mat[1]->setTexture(box.texture);

	scene5.light = engine->createLight();
	scene5.light->setPointLightPosition(glm::vec3(85.0f, 25.0f, 8.0f));
	scene5.light->setPointLightColor(glm::vec3(0.8f, 0.1f, 0.8f));

	box.mat[1]->setLight(scene5.light);

	for (unsigned int i = 20; i < 25; i++){
		box.actor[i] = engine->createActor();
		box.actor[i]->setGeometry(box.geo);
		box.actor[i]->setMaterial(box.mat[1]);
		box.actor[i]->setScale(3.0f, 0.0f, 3.0f);
	}

	for (unsigned int i = 4; i < 5; i++){
		// 0
		box.actor[i * 5]->setPosition(0.0f, 0.0f, -5.0f);
		box.actor[i * 5]->setRotation(1.0f, 0.0f, 0.0f, 1.5f);
		box.boxCenter[i]->addChild(box.actor[i * 5]);
		// 1
		box.actor[(i * 5) + 1]->setPosition(0.0f, -6.0f, 0.0f);
		box.actor[(i * 5) + 1]->setRotation(1.0f, 1.0f, 1.0f, 0.0f);
		box.boxCenter[i]->addChild(box.actor[(i * 5) + 1]);
		// 2
		box.actor[(i * 5) + 2]->setPosition(0.0f, 6.0f, 0.0f);
		box.actor[(i * 5) + 2]->setRotation(1.0f, 1.0f, 1.0f, 0.0f);
		box.boxCenter[i]->addChild(box.actor[(i * 5) + 2]);
		// 3
		box.actor[(i * 5) + 3]->setPosition(6.0f, 0.0f, 0.0f);
		box.actor[(i * 5) + 3]->setRotation(0.0f, 0.0f, 1.0f, 1.58f);
		box.boxCenter[i]->addChild(box.actor[(i * 5) + 3]);
		// 4
		box.actor[(i * 5) + 4]->setPosition(-6.0f, 0.0f, 0.0f);
		box.actor[(i * 5) + 4]->setRotation(0.0f, 0.0f, 1.0f, 1.58f);
		box.boxCenter[i]->addChild(box.actor[(i * 5) + 4]);
	}

	scene5.geo = engine->createGeometry();
	scene5.geo->createCube("MyCube", 1.5f);

	scene5.texture = engine->createTexture();
	scene5.texture->loadTexture("../_assets/amethyst.jpg");

	scene5.mat = engine->createMaterial();
	scene5.mat->initMaterial(kShaderType_PointLight_Texture);
	scene5.mat->setTexture(scene5.texture);
	scene5.mat->setLight(scene5.light);

	scene5.actor = engine->createActor();
	scene5.actor->setGeometry(scene5.geo);
	scene5.actor->setMaterial(scene5.mat);
}

struct Scene6 {
	std::shared_ptr<PastorseGeometry> geo;
	std::shared_ptr<PastorseMaterial> mat;
	std::shared_ptr<PastorseTexture> texture;
	std::shared_ptr<PastorseActor> actor;
	std::shared_ptr<PastorseLight> light;
	float32 rotation = 0.0f;
	float32 position = 0.0f;
	float32 position_2 = 0.0f;
	bool change = false;

} scene6;

void InitScene6(){

	box.mat[2] = engine->createMaterial();
	box.mat[2]->initMaterial(kShaderType_3SpotDirectionalLight_Texture);
	box.mat[2]->setTexture(box.texture);

	scene6.light = engine->createLight();
	scene6.light->setSpotLightPosition(glm::vec3(100.0f, 30.0f, 3.0f),0);
	scene6.light->setSpotLightColor(glm::vec3(3.0f, 0.0f, 0.0f),0);
	scene6.light->setSpotLightDirection(glm::vec3(10.0f, -10.0f, -3.0f), 0);

	scene6.light->setSpotLightPosition(glm::vec3(100.0f, 30.0f, 3.0f), 1);
	scene6.light->setSpotLightColor(glm::vec3(0.0f, 3.0f, 0.0f), 1);
	scene6.light->setSpotLightDirection(glm::vec3(10.0f, -10.0f, -3.0f), 1);

	box.mat[2]->setLight(scene6.light);

	for (unsigned int i = 25; i < 30; i++){
		box.actor[i] = engine->createActor();
		box.actor[i]->setGeometry(box.geo);
		box.actor[i]->setMaterial(box.mat[2]);
		box.actor[i]->setScale(3.0f, 0.0f, 3.0f);
	}

	for (unsigned int i = 5; i < 6; i++){
		// 0
		box.actor[i * 5]->setPosition(0.0f, 0.0f, -5.0f);
		box.actor[i * 5]->setRotation(1.0f, 0.0f, 0.0f, 1.5f);
		box.boxCenter[i]->addChild(box.actor[i * 5]);
		// 1
		box.actor[(i * 5) + 1]->setPosition(0.0f, -6.0f, 0.0f);
		box.actor[(i * 5) + 1]->setRotation(1.0f, 1.0f, 1.0f, 0.0f);
		box.boxCenter[i]->addChild(box.actor[(i * 5) + 1]);
		// 2
		box.actor[(i * 5) + 2]->setPosition(0.0f, 6.0f, 0.0f);
		box.actor[(i * 5) + 2]->setRotation(1.0f, 1.0f, 1.0f, 0.0f);
		box.boxCenter[i]->addChild(box.actor[(i * 5) + 2]);
		// 3
		box.actor[(i * 5) + 3]->setPosition(6.0f, 0.0f, 0.0f);
		box.actor[(i * 5) + 3]->setRotation(0.0f, 0.0f, 1.0f, 1.58f);
		box.boxCenter[i]->addChild(box.actor[(i * 5) + 3]);
		// 4
		box.actor[(i * 5) + 4]->setPosition(-6.0f, 0.0f, 0.0f);
		box.actor[(i * 5) + 4]->setRotation(0.0f, 0.0f, 1.0f, 1.58f);
		box.boxCenter[i]->addChild(box.actor[(i * 5) + 4]);
	}

	scene6.geo = engine->createGeometry();
	scene6.geo->createCube("MyCube", 1.5f);

	scene6.texture = engine->createTexture();
	scene6.texture->loadTexture("../_assets/hexagon.jpg");

	scene6.mat = engine->createMaterial();
	scene6.mat->initMaterial(kShaderType_3SpotDirectionalLight_Texture);
	scene6.mat->setTexture(scene6.texture);
	scene6.mat->setLight(scene6.light);

	scene6.actor = engine->createActor();
	scene6.actor->setGeometry(scene6.geo);
	scene6.actor->setMaterial(scene6.mat);
}

struct Scene7 {
	std::shared_ptr<PastorseGeometry> geo;
	std::shared_ptr<PastorseMaterial> mat;
	std::shared_ptr<PastorseTexture> texture;
	std::shared_ptr<PastorseActor> actor;
	std::shared_ptr<PastorseLight> light;
	std::shared_ptr<PastorseMaterial> matPos;

	float32 rotation = 0.0f;
	float32 position = 0.0f;
	bool change = false;

} scene7;

void InitScene7(){

	scene7.matPos = engine->createMaterial();
	scene7.matPos->initMaterial(kShaderType_RenderPosition);

	box.mat[3] = engine->createMaterial();
	box.mat[3]->initMaterial(kShaderType_TestDirectionalLight_Texture);
	box.mat[3]->setTexture(box.texture);

	scene7.light = engine->createLight();
	scene7.light->setDirectionalLightDirection(glm::vec3(10.0, -10.0, -100.0));
	scene7.light->setDirectionalLightColor(glm::vec3(1.0f, 1.0f, 1.0f));

	box.mat[3]->setLight(scene7.light);

	for (unsigned int i = 30; i < 35; i++){
		box.actor[i] = engine->createActor();
		box.actor[i]->setGeometry(box.geo);
		box.actor[i]->setMaterial(box.mat[3]);
		box.actor[i]->setSpecialMaterial(scene7.matPos);
		box.actor[i]->setScale(3.0f, 0.0f, 3.0f);
	}

	for (unsigned int i = 6; i < 7; i++){
		// 0
		box.actor[i * 5]->setPosition(0.0f, 0.0f, -5.0f);
		box.actor[i * 5]->setRotation(1.0f, 0.0f, 0.0f, 1.5f);
		box.boxCenter[i]->addChild(box.actor[i * 5]);
		// 1
		box.actor[(i * 5) + 1]->setPosition(0.0f, -6.0f, 0.0f);
		box.actor[(i * 5) + 1]->setRotation(1.0f, 1.0f, 1.0f, 0.0f);
		box.boxCenter[i]->addChild(box.actor[(i * 5) + 1]);
		// 2
		box.actor[(i * 5) + 2]->setPosition(0.0f, 6.0f, 0.0f);
		box.actor[(i * 5) + 2]->setRotation(1.0f, 1.0f, 1.0f, 0.0f);
		box.boxCenter[i]->addChild(box.actor[(i * 5) + 2]);
		// 3
		box.actor[(i * 5) + 3]->setPosition(6.0f, 0.0f, 0.0f);
		box.actor[(i * 5) + 3]->setRotation(0.0f, 0.0f, 1.0f, 1.58f);
		box.boxCenter[i]->addChild(box.actor[(i * 5) + 3]);
		// 4
		box.actor[(i * 5) + 4]->setPosition(-6.0f, 0.0f, 0.0f);
		box.actor[(i * 5) + 4]->setRotation(0.0f, 0.0f, 1.0f, 1.58f);
		box.boxCenter[i]->addChild(box.actor[(i * 5) + 4]);
	}

	scene7.geo = engine->createGeometry();
	scene7.geo->createCube("MyCube", 1.5f);

	scene7.texture = engine->createTexture();
	scene7.texture->loadTexture("../_assets/rock.jpg");

	scene7.mat = engine->createMaterial();
	scene7.mat->initMaterial(kShaderType_TestDirectionalLight_Texture);
	scene7.mat->setTexture(scene7.texture);
	scene7.mat->setLight(scene7.light);

	scene7.actor = engine->createActor();
	scene7.actor->setGeometry(scene7.geo);
	scene7.actor->setMaterial(scene7.mat);
	scene7.actor->setSpecialMaterial(scene7.matPos);
}

void moveBoxScene(float32 pos_x, float32 pos_y, float32 pos_z, int32 number_box){
	switch (number_box)
	{
	case 0:
		box.boxCenter[0]->setPosition(pos_x, pos_y, pos_z);
		break;
	case 1:
		box.boxCenter[1]->setPosition(pos_x, pos_y, pos_z);
		break;
	case 2:
		box.boxCenter[2]->setPosition(pos_x, pos_y, pos_z);
		break;
	case 3:
		box.boxCenter[3]->setPosition(pos_x, pos_y, pos_z);
		break;
	case 4:
		box.boxCenter[4]->setPosition(pos_x, pos_y, pos_z);
		break;
	case 5:
		box.boxCenter[5]->setPosition(pos_x, pos_y, pos_z);
		break;
	case 6:
		box.boxCenter[6]->setPosition(pos_x, pos_y, pos_z);
		break;
	default:
		break;
	}
	
}

int32 moveBoxScene(lua_State * L){
	lua_Number n1 = (float32)lua_tonumber(L, 1);
	lua_Number n2 = (float32)lua_tonumber(L, 2);
	lua_Number n3 = (float32)lua_tonumber(L, 3);
	lua_Number n4 = (int32)lua_tonumber(L, 4);

	moveBoxScene(n1, n2, n3, n4);

	return 0;
}


void rotateBoxScene(float32 rot_x, float32 rot_y, float32 rot_z, float32 angle, int32 number_box){

	switch (number_box)
	{
	case 0:
		box.boxCenter[0]->setRotation(rot_x, rot_y, rot_z, angle);
		break;
	case 1:
		box.boxCenter[1]->setRotation(rot_x, rot_y, rot_z, angle);
		break;
	case 2:
		box.boxCenter[2]->setRotation(rot_x, rot_y, rot_z, angle);
		break;
	case 3:
		box.boxCenter[3]->setRotation(rot_x, rot_y, rot_z, angle);
		break;
	case 4:
		box.boxCenter[4]->setRotation(rot_x, rot_y, rot_z, angle);
		break;
	case 5:
		box.boxCenter[5]->setRotation(rot_x, rot_y, rot_z, angle);
		break;
	case 6:
		box.boxCenter[6]->setRotation(rot_x, rot_y, rot_z, angle);
		break;
	default:
		break;
	}
}


int32 rotateBoxScene(lua_State * L){
	lua_Number n1 = (float32)lua_tonumber(L, 1);
	lua_Number n2 = (float32)lua_tonumber(L, 2);
	lua_Number n3 = (float32)lua_tonumber(L, 3);
	lua_Number n4 = (float32)lua_tonumber(L, 4);
	lua_Number n5 = (int32)lua_tonumber(L, 5);

	rotateBoxScene(n1, n2, n3, n4, n5);

	return 0;
}


void scaleBoxScene(float32 scale_x, float32 scale_y, float32 scale_z, int32 number_box){

	switch (number_box)
	{
	case 0:
		box.boxCenter[0]->setScale(scale_x, scale_y, scale_z);
		break;
	case 1:
		box.boxCenter[1]->setScale(scale_x, scale_y, scale_z);
		break;
	case 2:
		box.boxCenter[2]->setScale(scale_x, scale_y, scale_z);
		break;
	case 3:
		box.boxCenter[3]->setScale(scale_x, scale_y, scale_z);
		break;
	case 4:
		box.boxCenter[4]->setScale(scale_x, scale_y, scale_z);
		break;
	case 5:
		box.boxCenter[5]->setScale(scale_x, scale_y, scale_z);
		break;
	case 6:
		box.boxCenter[6]->setScale(scale_x, scale_y, scale_z);
		break;
	default:
		break;
	}
}

int32 scaleBoxScene(lua_State * L){
	lua_Number n1 = (float32)lua_tonumber(L, 1);
	lua_Number n2 = (float32)lua_tonumber(L, 2);
	lua_Number n3 = (float32)lua_tonumber(L, 3);
	lua_Number n4 = (int32)lua_tonumber(L, 4);

	scaleBoxScene(n1, n2, n3, n4);

	return 0;
}

void moveObjectScene(float32 pos_x, float32 pos_y, float32 pos_z, int32 number_box){

	switch (number_box)
	{
	case 0:
		scene1.actor->setPosition(pos_x, pos_y, pos_z);
		break;
	case 1:
		scene2.actorEarth->setPosition(pos_x, pos_y, pos_z);
		break;
	case 2:
		scene3.actor[0]->setPosition(pos_x, pos_y, pos_z);
		break;
	case 3:
		scene4.actor->setPosition(pos_x, pos_y, pos_z);
		break;
	case 4:
		scene5.actor->setPosition(pos_x, pos_y, pos_z);
		break;
	case 5:
		scene6.actor->setPosition(pos_x, pos_y, pos_z);
		break;
	case 6:
		scene7.actor->setPosition(pos_x, pos_y, pos_z);
		break;
	default:
		break;
	}
}

int32 moveObjectScene(lua_State * L){
	lua_Number n1 = (float32)lua_tonumber(L, 1);
	lua_Number n2 = (float32)lua_tonumber(L, 2);
	lua_Number n3 = (float32)lua_tonumber(L, 3);
	lua_Number n4 = (int32)lua_tonumber(L, 4);

	moveObjectScene(n1, n2, n3, n4);

	return 0;
}


void scaleObjectScene(float32 scale_x, float32 scale_y, float32 scale_z, int32 number_box){

	switch (number_box)
	{
	case 0:
		scene1.actor->setScale(scale_x, scale_y, scale_z);
		break;
	case 1:
		scene2.actorEarth->setScale(scale_x, scale_y, scale_z);
		break;
	case 2:
		scene3.actor[0]->setScale(scale_x, scale_y, scale_z);
		break;
	case 3:
		scene4.actor->setScale(scale_x, scale_y, scale_z);
		break;
	case 4:
		scene5.actor->setScale(scale_x, scale_y, scale_z);
		break;
	case 5:
		scene6.actor->setScale(scale_x, scale_y, scale_z);
		break;
	case 6:
		scene7.actor->setScale(scale_x, scale_y, scale_z);
		break;
	default:
		break;
	}
}

int32 scaleObjectScene(lua_State * L){
	lua_Number n1 = (float32)lua_tonumber(L, 1);
	lua_Number n2 = (float32)lua_tonumber(L, 2);
	lua_Number n3 = (float32)lua_tonumber(L, 3);
	lua_Number n4 = (int32)lua_tonumber(L, 4);

	scaleObjectScene(n1, n2, n3, n4);

	return 0;
}

void rotateObjectScene(float32 rot_x, float32 rot_y, float32 rot_z, float32 angle, int32 number_box){

	switch (number_box)
	{
	case 0:
		scene1.actor->setRotation(rot_x, rot_y, rot_z, angle);
		break;
	case 1:
		scene2.actorEarth->setRotation(rot_x, rot_y, rot_z, angle);
		break;
	case 2:
		scene3.actor[0]->setRotation(rot_x, rot_y, rot_z, angle);
		break;
	case 3:
		scene4.actor->setRotation(rot_x, rot_y, rot_z, angle);
		break;
	case 4:
		scene4.actor->setRotation(rot_x, rot_y, rot_z, angle);
		break;
	case 5:
		scene5.actor->setRotation(rot_x, rot_y, rot_z, angle);
		break;
	case 6:
		scene6.actor->setRotation(rot_x, rot_y, rot_z, angle);
		break;
	default:
		break;
	}
}

int32 rotateObjectScene(lua_State * L){
	lua_Number n1 = (float32)lua_tonumber(L, 1);
	lua_Number n2 = (float32)lua_tonumber(L, 2);
	lua_Number n3 = (float32)lua_tonumber(L, 3);
	lua_Number n4 = (float32)lua_tonumber(L, 4);
	lua_Number n5 = (int32)lua_tonumber(L, 5);

	rotateObjectScene(n1, n2, n3, n4, n5);

	return 0;
}


void updateThread(){

	/// Init Lua
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	/// Scene
	lua_register(L, "moveBoxScene", moveBoxScene);
	lua_register(L, "rotateBoxScene", rotateBoxScene);
	lua_register(L, "scaleBoxScene", scaleBoxScene);

	lua_register(L, "moveObjectScene", moveObjectScene);
	lua_register(L, "scaleObjectScene", scaleObjectScene);
	lua_register(L, "rotateObjectScene", rotateObjectScene);
	/// Files
	luaL_dofile(L, "../_assets/Init_AN.lua");
	luaL_dofile(L, "../_assets/Update_AN.lua");

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

    // Camera
    init.camera->setLookUp(glm::vec3(init.input_A_D, init.input_W_S, init.input_Left_Right + 20.0f), glm::vec3(init.input_A_D, init.input_W_S, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  
	/// Scene1
	scene1.rotation += 0.00001f;
	scene1.actor->setRotation(1.0f, 1.0f, 1.0f, scene1.rotation);

	/// Scene2
	scene2.rotation += 0.00001f;
	scene2.actorEarth->setRotation(0.0f, 1.0f, 0.0f, scene2.rotation);


	/// Scene3
	scene3.rotation_father += 0.00001f;
	scene3.rotatio_child += 0.0001f;
	scene3.actor[0]->setRotation(1.0f, 1.0f, 1.0f, scene3.rotation_father);
	scene3.actor[1]->setRotation(1.0f, 1.0f, 1.0f, scene3.rotatio_child);
	scene3.actor[2]->setRotation(1.0f, 1.0f, 1.0f, -scene3.rotatio_child);

	/// Scene4
	scene4.rotation += 0.0001f;
	scene4.actor->setRotation(1.0f, 1.0f, 0.0f, scene4.rotation);

	/// Scene5
	scene5.rotation += 0.0001f;
	scene5.actor->setRotation(1.0f, 1.0f, 0.0f, scene5.rotation);
	
	if (!scene5.change){
		if (scene5.position >= 2.0f){
			scene5.change = true;
		}
		else{
			scene5.position += 0.001f;
		}
	}

	if (scene5.change){
		if (scene5.position <= -8.0f){
			scene5.change = false;
		}
		else{
			scene5.position -= 0.001f;
		}
	}

	scene5.light->setPointLightPosition(glm::vec3(85.0f + scene5.position, 25.0f, 0.0f));


	/// Scene6

	if (!scene6.change){
		if (scene6.position >= 4.0f){
			scene6.change = true;
		}
		else{
			scene6.position += 0.001f;
			scene6.position_2 -= 0.001f;
			
		}
	}

	if (scene6.change){
		if (scene6.position <= -7.0f){
			scene6.change = false;
		}
		else{
			scene6.position -= 0.001f;
			scene6.position_2 += 0.001f;
		
		}
	}

	scene6.light->setSpotLightPosition(glm::vec3(100.0f + scene6.position, 30.0f, 3.0f), 0);
	scene6.light->setSpotLightPosition(glm::vec3(100.0f - scene6.position, 30.0f, 3.0f), 1);


	/// Scene7
	scene7.rotation += 0.0001f;
	scene7.actor->setRotation(1.0f, 1.0f, 1.0f, scene7.rotation);

	/// Scene7 --> Camera shadow

	glm::vec3 light_dir = normalize(glm::vec3(10.0, -10.0, -100.0f));
	glm::vec3 light_pos = glm::vec3(120.0f, 25.0f, 0.0f);

	init.camera_2->setLookUp(light_pos, light_pos + light_dir, glm::vec3(0.0f, 1.0f, 0.0f));

	/// Lua
	if (init.input->getKey(kKey_I)){
		luaL_dofile(L, "../_assets/Init_AN.lua");
	}

	if (init.input->getKey(kKey_U)){
		luaL_dofile(L, "../_assets/Update_AN.lua");
	}

	lua_getglobal(L, "update");
	lua_pushnumber(L, 0.016f);
	lua_call(L, 1, 0);

  }
  lua_close(L);
}


int32 main(int argc, const char* argv[])
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
  init.camera_2->setOrthoProjection(0.1f, 120.0f);

  init.camera_3 = engine->createCamera();

  /// Init Camera
  InitBox();
  InitScene1();
  InitScene2();
  InitScene3();
  InitScene4();
  InitScene5();
  InitScene6();
  InitScene7();


  std::thread* u_thread = new std::thread(&updateThread);
	while (!engine->getWindow()->isClosedWindow())
	{

    /// Init
    engine->getWindow()->pollEvents();


	if (init.input->getKey(kKey_1)){
		engine->activate_pp = true;
	}

	if (init.input->getKey(kKey_2)){
		engine->activate_pp = false;
	}



    /// Draw
	engine->draw();

  }
	engine->getWindow()->closeWindow();
	exit(EXIT_SUCCESS);
}
