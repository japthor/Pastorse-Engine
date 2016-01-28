#include "PastorseNode.h"

PastorseNode::PastorseNode(){

	rotation_matrix_ = glm::mat4(1.0f);
	scale_matrix_ = glm::mat4(1.0f);
	translation_matrix = glm::mat4(1.0f);

	model_ = glm::mat4(1.0f);
	world_ = glm::mat4(1.0f);

	position_ = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation_ = glm::vec3(0.0f, 0.0f, 0.0f);
	scale_ = glm::vec3(0.0f, 0.0f, 0.0f);

}

void PastorseNode::addChild(std::shared_ptr<PastorseNode> node_child){
	node_children_.push_back(node_child);
	node_child->setParent(returnMyself());
}


void PastorseNode::setPosition(float32 x, float32 y, float32 z){
	position_ = glm::vec3(x, y, z);
	translation_matrix = glm::translate(glm::mat4(1.0f), position_);
  model_ *= translation_matrix;
}

glm::vec3 PastorseNode::getPosition(){
	return position_;
}

void PastorseNode::setRotation(float32 x, float32 y, float32 z, float32 angle){
	rotation_ = glm::vec3(x, y, z);
	rotation_matrix_ = glm::rotate(glm::mat4(1.0f), angle, rotation_);
  model_ *= rotation_matrix_;
}

glm::vec3 PastorseNode::getRotation(){
	return rotation_;
}

void PastorseNode::setScale(float32 x, float32 y, float32 z){
	scale_ = glm::vec3(x, y, z);
	scale_matrix_ = glm::scale(glm::mat4(1.0f), scale_);
  model_ *= scale_matrix_;
}

glm::vec3 PastorseNode::getScale(){
	return scale_;
}

glm::mat4 PastorseNode::getRotationMatrix(){
	return rotation_matrix_;
}

void PastorseNode::setRotationMatrix(glm::mat4 rotation){
	rotation_matrix_ = rotation;
}

glm::mat4 PastorseNode::getScaleMatrix(){
	return scale_matrix_;
}

void PastorseNode::setScaleMatrix(glm::mat4 scale){
	scale_matrix_ = scale;
}

glm::mat4 PastorseNode::getTranslationMatrix(){
	return translation_matrix;
}

void PastorseNode::setTranslationMatrix(glm::mat4 translation){
	translation_matrix = translation;
}

std::vector<std::shared_ptr<PastorseNode>> PastorseNode::getChildren() const{
  return node_children_;
}

std::weak_ptr<PastorseNode> PastorseNode::getParent(){
  return node_parent_;
}

glm::mat4 PastorseNode::getModel() const{
	return model_;
}

glm::mat4 PastorseNode::getWorld() const{
	return world_;
}

void PastorseNode::setWorld(glm::mat4 world){
	world_ = world;
}

void PastorseNode::setParent(std::weak_ptr<PastorseNode> node_parent){
	node_parent_ = node_parent;
}



