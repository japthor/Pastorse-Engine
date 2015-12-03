#include "PastorseNode.h"

PastorseNode::PastorseNode(){
	model_ = glm::mat4(1.0f);
	world_ = glm::mat4(1.0f);
}

void PastorseNode::add_child(std::shared_ptr<PastorseNode> node_child){
	node_children_.push_back(node_child);
  node_child->set_parent(returnMyself());
}


void PastorseNode::set_parent(std::weak_ptr<PastorseNode> node_parent){
	node_parent_ = node_parent;
}

void PastorseNode::set_position(float32 x, float32 y, float32 z){
	glm::vec3 v_pos = glm::vec3(x,y,z);
  translation_ = glm::translate(glm::mat4(1.0f), v_pos);
}

void PastorseNode::set_rotation(float32 x, float32 y, float32 z, float32 angle){
	glm::vec3 v_rot = glm::vec3(x, y, z);
	rotation_ = glm::rotate(glm::mat4(1.0f), angle ,v_rot);
}

void PastorseNode::set_scale(float32 x, float32 y, float32 z){
	glm::vec3 v_scale = glm::vec3(x, y, z);
  scale_ = glm::scale(glm::mat4(1.0f), v_scale);
}

glm::mat4 PastorseNode::get_model() const{
	return model_;
}

glm::mat4 PastorseNode::get_world() const{
  return world_;
}

void PastorseNode::set_world(glm::mat4 world){
  world_ = world;
}

std::vector<std::shared_ptr<PastorseNode>> PastorseNode::get_children() const{
  return node_children_;
}

std::weak_ptr<PastorseNode> PastorseNode::get_parent(){
  return node_parent_;
}

glm::mat4 PastorseNode::get_rotation(){
  return rotation_;
}

void PastorseNode::set_rotation(glm::mat4 rotation){
  rotation_ = rotation;
}

glm::mat4 PastorseNode::get_scale(){
  return scale_;
}

void PastorseNode::set_scale(glm::mat4 scale){
  scale_ = scale;
}

glm::mat4 PastorseNode::get_translation(){
  return translation_;
}

void PastorseNode::set_translation(glm::mat4 translation){
  translation_ = translation;
}




