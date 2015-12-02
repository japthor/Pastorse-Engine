#include "PastorseActor.h"

PastorseActor::PastorseActor()
{
	
}

void PastorseActor::set_geometry(std::shared_ptr<PastorseGeometry> geometry){
	geometry_ = geometry;
}

void PastorseActor::set_material(std::shared_ptr<PastorseMaterial> material){
	material_ = material;
}

void PastorseActor::draw(){
	material_->prepare_draw();
	visitNode(this->returnMyself());
	geometry_->draw(get_world());
}

void PastorseActor::visitNode(std::shared_ptr<PastorseNode> node){
  updateNode(node);
  std::vector<std::shared_ptr<PastorseNode>> children = node->get_children();

  if (!children.empty()){
    for (int16 i = 0; i < children.size(); i++){
      visitNode(children[i]);
    }
  }
}

void PastorseActor::updateNode(std::shared_ptr<PastorseNode> node){
  if (get_parent().expired()){
    set_world(get_model());
  }
  else{
    std::shared_ptr<PastorseNode> parent = get_parent().lock();
    set_world(get_model() * parent->get_world());
  }
}



