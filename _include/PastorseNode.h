#ifndef INCLUDE_PASTORSENODE_H_
#define INCLUDE_PASTORSENODE_H_ 1

#include <string> 
#include <vector>
#include <memory>
#include "PastorseTypes.h"
#include "gtc\matrix_transform.hpp"
#include "gtc\type_ptr.hpp"

class PastorseNode : std::enable_shared_from_this<PastorseNode>
{
public:
	PastorseNode();
	~PastorseNode(){};

	void add_child(std::shared_ptr<PastorseNode> node_child);

	void set_position(float32 x, float32 y, float32 z);
	void set_rotation(float32 x, float32 y, float32 z, float32 angle);
	void set_scale(float32 x, float32 y, float32 z);
	std::shared_ptr<PastorseNode> returnMyself() { return shared_from_this(); }

  glm::mat4 get_world() const;
  glm::mat4 get_model() const;
  std::vector<std::shared_ptr<PastorseNode>> get_children() const;

  glm::mat4 get_rotation();
  void set_rotation(glm::mat4 rotation);

  glm::mat4 get_scale();
  void set_scale(glm::mat4 scale);

  glm::mat4 get_translation();
  void set_translation(glm::mat4 translation);


protected:
	
  
  void set_world(glm::mat4 world);

  std::weak_ptr<PastorseNode> get_parent();

  virtual void visitNode(std::shared_ptr<PastorseNode> node) = 0;
  virtual void updateNode(std::shared_ptr<PastorseNode> node) = 0;

private:
	void set_parent(std::weak_ptr<PastorseNode> node_parent);

	std::vector<std::shared_ptr<PastorseNode>> node_children_;
	std::weak_ptr<PastorseNode> node_parent_;

  glm::mat4 rotation_;
  glm::mat4 scale_;
  glm::mat4 translation_;

	glm::mat4 model_;
	glm::mat4 world_;
};



#endif