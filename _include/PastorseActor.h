#ifndef INCLUDE_PASTORSEACTOR_H_
#define INCLUDE_PASTORSEACTOR_H_ 1

#include "PastorseMaterial.h"
#include "PastorseGeometry.h"
#include "PastorseNode.h"
#include <sstream>

class PastorseActor : public PastorseNode
{
public:
	PastorseActor(){};
	~PastorseActor(){};

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
	void draw();

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
	void loadOBJ(const char* obj_name);

	/// Delete Buffer
	void deleteBuffers();

private:
	std::shared_ptr<PastorseGeometry> geometry_;
	std::shared_ptr<PastorseMaterial> material_;
	std::string* obj_name_;
};

#endif