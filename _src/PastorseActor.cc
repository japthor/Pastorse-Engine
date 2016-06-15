#include "PastorseActor.h"

void PastorseActor::setGeometry(std::shared_ptr<PastorseGeometry> geometry){
	geometry_ = geometry;
}

void PastorseActor::setMaterial(std::shared_ptr<PastorseMaterial> material){
	material_ = material;
}

void PastorseActor::draw(glm::mat4 view, glm::mat4 projection, glm::vec3 camera_position, glm::mat4 shadow_view, glm::mat4 shadow_projection, glm::mat4 shadow_view2, glm::mat4 shadow_projection2){
	if (material_ == nullptr || geometry_ == nullptr){
		printf("\nError: No se ejecuta la funcion de draw del actor");
	}
	else{
        material_->draw(view, projection, camera_position, 0, shadow_view, shadow_projection,shadow_view2,shadow_projection2);
		visitNode(this->returnMyself());
		geometry_->draw(getWorld(),material_->getProgram());
	}
}

void PastorseActor::setSpecialMaterial(std::shared_ptr<PastorseMaterial> special_material){
  special_material_ = special_material;
}

void PastorseActor::specialDraw(glm::mat4 view, glm::mat4 projection, glm::vec3 camera_position, int camera){
  if (special_material_ == nullptr || geometry_ == nullptr){
    //printf("\nError: No se ejecuta la funcion de draw del actor");
  }
  else{
	  if (camera == 1){
		  special_material_->draw(view, projection, camera_position, 1);
		  visitNode(this->returnMyself());
		  geometry_->draw(getWorld(), special_material_->getProgram());
	  }
	  
	  if (camera == 2){
		  special_material_->draw(view, projection, camera_position, 2);
		  visitNode(this->returnMyself());
		  geometry_->draw(getWorld(), special_material_->getProgram());
	  }
  }
}

void PastorseActor::visitNode(std::shared_ptr<PastorseNode> node){
  updateNode(node);
  std::vector<std::shared_ptr<PastorseNode>> children = node->getChildren();

  if (!children.empty()){
    for (int32 i = 0; i < children.size(); i++){
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
    //setWorld(model * parent->getWorld());

  }
}

std::string PastorseActor::loadOBJ(const char* obj_name){
	std::vector<tinyobj::material_t> mat;
	std::vector<tinyobj::shape_t> shapes;
	std::string error;

	if (!tinyobj::LoadObj(shapes, mat, error, obj_name)){
		printf("error loading OBJ\n");
	}

	geometry_->geometryOBJ(static_cast<void*>(&(shapes[0])));
	material_->setColor(mat[0].diffuse[0], mat[0].diffuse[1], mat[0].diffuse[2]);

	std::string key("/");
	std::string conver = obj_name;
	std::size_t found = conver.rfind(key);
	conver.erase(conver.begin() + found + 1, conver.end());


	std::stringstream location;
	
	location << conver << mat[0].diffuse_texname.c_str() << '\0';
	std::string loc = location.str();
	printf("Texture name %s\n", loc.c_str());
    // TODO --> En vez de material, llamar a la clase textura
	//material_->uploadTexture(loc.c_str());

	return loc;

}

void PastorseActor::deleteActor(){
  this->~PastorseActor();
}



