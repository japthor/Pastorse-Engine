#ifndef INCLUDE_PASTORSENODE_H_
#define INCLUDE_PASTORSENODE_H_ 1

#include <vector>
#include <memory>
#include "PastorseTypes.h"
#include "gtc\matrix_transform.hpp"

class PastorseNode : std::enable_shared_from_this<PastorseNode>
{
public:
	PastorseNode();

  /**
  * Adds a Child
  *
  * @param node_child The actor you want to make child.
  */
  void addChild(std::shared_ptr<PastorseNode> node_child);

  /**
  * removes a Child
  *
  * @param node_child The actor you want to remove from.
  */
  void removeChild(std::shared_ptr<PastorseNode> node_child);

  ///removes children
  void removeChildren();

  ///removes the parent
  void removeParent();

  /**
  * Sets the node Position
  *
  * @param x X.
  * @param y Y.
  * @param z Z.
  */
  void setPosition(float32 x, float32 y, float32 z);

  /// Gets the node Position.
  glm::vec3 getPosition();


  /**
  * Sets the node Rotation
  *
  * @param x X.
  * @param y Y.
  * @param z Z.
  * @param angle angle.
  */
  void setRotation(float32 x, float32 y, float32 z, float32 angle);
  /// Gets the node Rotation.
  glm::vec3 getRotation();

  /**
  * Sets the node Scale
  *
  * @param x X.
  * @param y Y.
  * @param z Z.
  */
  void setScale(float32 x, float32 y, float32 z);
  /// Gets the node Scale.
  glm::vec3 getScale();

  /// Gets the Rotation Matrix.
  glm::mat4 getRotationMatrix();

  /**
  * Sets the rotation matrix
  *
  * @param rotation Rotation Matrix.
  */
  void setRotationMatrix(glm::mat4 rotation);
  /// Gets the Scale Matrix.
  glm::mat4 getScaleMatrix();

  /**
  * Sets the scale matrix
  *
  * @param scale scale Matrix.
  */
  void setScaleMatrix(glm::mat4 scale);
  /// Gets the Translation Matrix.
  glm::mat4 getTranslationMatrix();

  /**
  * Sets the translation matrix
  *
  * @param translation translation Matrix.
  */
  void setTranslationMatrix(glm::mat4 translation);

  /// Sets the Parent
  std::shared_ptr<PastorseNode> returnMyself() { return shared_from_this(); }

  /// Children's Vector.
  std::vector<std::shared_ptr<PastorseNode>> getChildren() const;

  /// Gets the Model
  glm::mat4 getModel() const;
  /// Gets the World
  glm::mat4 getWorld() const;


protected:
  virtual ~PastorseNode(){};
  void setWorld(glm::mat4 world);

  std::weak_ptr<PastorseNode> getParent();

  virtual void visitNode(std::shared_ptr<PastorseNode> node) = 0;
  virtual void updateNode(std::shared_ptr<PastorseNode> node) = 0;

private:
	void setParent(std::weak_ptr<PastorseNode> node_parent);

	std::vector<std::shared_ptr<PastorseNode>> node_children_;
	std::weak_ptr<PastorseNode> node_parent_;

	glm::mat4 rotation_matrix_;
	glm::mat4 scale_matrix_;
	glm::mat4 translation_matrix;

	glm::mat4 model_;
	glm::mat4 world_;

	glm::vec3 position_;
	glm::vec3 rotation_;
	glm::vec3 scale_;
};



#endif