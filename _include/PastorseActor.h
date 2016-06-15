#ifndef INCLUDE_PASTORSEACTOR_H_
#define INCLUDE_PASTORSEACTOR_H_ 1

#include "PastorseMaterial.h"
#include "PastorseGeometry.h"
#include "PastorseNode.h"
#include <sstream>

class PastorseActor : public PastorseNode
{
public:
  ~PastorseActor(){ printf("delete actor"); };
	/**
	* Sets a new geometry.
	*
	* @param geometry The new geometry.
	*/
	void setGeometry(std::shared_ptr<PastorseGeometry> geometry);

	/**
	* Sets a new material.
	*
	* @param material The new material.
	*/
	void setMaterial(std::shared_ptr<PastorseMaterial> material);


	///Calls to the draw of the GPU (Don't call it).
	void draw(glm::mat4 view, glm::mat4 project, glm::vec3 camera_position, glm::mat4 shadow_view = glm::mat4(1.0f), glm::mat4 shadow_projection = glm::mat4(1.0f), glm::mat4 shadow_view2 = glm::mat4(1.0f), glm::mat4 shadow_projection2 = glm::mat4(1.0f));


  void setSpecialMaterial(std::shared_ptr<PastorseMaterial> special_material_);


  ///Calls to the draw of the GPU (Don't call it).
  void specialDraw(glm::mat4 view, glm::mat4 project, glm::vec3 camera_position, int camera);

	/**
	* Visits the children node.
	*
	* @param node The node
	*/
    virtual void visitNode(std::shared_ptr<PastorseNode> node);


	/**
	* Sets the model of the node.
	*
	* @param node The node
	*/
    virtual void updateNode(std::shared_ptr<PastorseNode> node);

	/**
	* Loads an OBJ.
	*
	* @param obj_name Where the obj it is stored.
	*/
	std::string loadOBJ(const char* obj_name);

	/// Delete Actor
  void deleteActor();

private:
  friend class PastorseEngine;
  PastorseActor(const PastorseActor&);
  PastorseActor& operator= (const PastorseActor&);
  PastorseActor(){};

	std::shared_ptr<PastorseGeometry> geometry_;
	std::shared_ptr<PastorseMaterial> material_;
  std::shared_ptr<PastorseMaterial> special_material_;
	std::string* obj_name_;
};

#endif