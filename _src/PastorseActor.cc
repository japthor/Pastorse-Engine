#include "PastorseActor.h"

void PastorseActor::setGeometry(std::shared_ptr<PastorseGeometry> geometry){
	geometry_ = geometry;
}

void PastorseActor::setMaterial(std::shared_ptr<PastorseMaterial> material){
	material_ = material;
}

void PastorseActor::draw(){
	if (material_ == nullptr || geometry_ == nullptr){
		printf("\nError: No se ejecuta la funcion de draw del actor");
	}
	else{
		material_->draw();
		visitNode(this->returnMyself());
		geometry_->draw(getWorld());
	}
}

void PastorseActor::visitNode(std::shared_ptr<PastorseNode> node){
  updateNode(node);
  std::vector<std::shared_ptr<PastorseNode>> children = node->getChildren();

  if (!children.empty()){
    for (int16 i = 0; i < children.size(); i++){
      visitNode(children[i]);
    }
  }
}

void PastorseActor::updateNode(std::shared_ptr<PastorseNode> node){
  glm::mat4 model;
  model = getTranslationMatrix() * getRotationMatrix() * getScaleMatrix();

  //model = getModel();

  if (getParent().expired()){
	  setWorld(model);
  }
  else{
	  std::shared_ptr<PastorseNode> parent = getParent().lock();
    // It's the world * the model, not the model * the world.
    setWorld( parent->getWorld() * model);
  }
}

void PastorseActor::loadOBJ(const char* obj_name){
	std::vector<tinyobj::material_t> mat;
	std::vector<tinyobj::shape_t> shapes;
	std::string error;

	if (!tinyobj::LoadObj(shapes, mat, error, obj_name)){
		printf("error loading OBJ\n");
	}

	geometry_->geometryOBJ(static_cast<void*>(&shapes[0]));
	material_->setColor(mat[0].diffuse[0], mat[0].diffuse[1], mat[0].diffuse[2]);

	std::string key("/");
	std::string conver = obj_name;
	std::size_t found = conver.rfind(key);
	conver.erase(conver.begin() + found + 1, conver.end());


	std::stringstream location;
	
	location << conver << mat[0].diffuse_texname.c_str() << '\0';
	std::string loc = location.str();
	printf("Texture name %s\n", loc.c_str());
	material_->uploadTexture(loc.c_str());

}

void PastorseActor::deleteBuffers(){
	if (geometry_ == nullptr){
		printf("\nError: No se ejecutar la funcion deleteBuffers");
	}
	else{
		geometry_->deleteBuffers();
	}
}



