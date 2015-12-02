#ifndef INCLUDE_PASTORSEACTOR_H_
#define INCLUDE_PASTORSEACTOR_H_ 1

#include <memory>
#include "PastorseMaterial.h"
#include "PastorseGeometry.h"
#include "PastorseGPU.h"
#include "PastorseNode.h"
#include "PastorseTypes.h"

class PastorseActor : public PastorseNode
{
public:
	PastorseActor();
	~PastorseActor(){};

	void set_geometry(std::shared_ptr<PastorseGeometry> geometry);
	void set_material(std::shared_ptr<PastorseMaterial> material);

	void draw();

  virtual void visitNode(std::shared_ptr<PastorseNode> node);
  virtual void updateNode(std::shared_ptr<PastorseNode> node);

private:
	std::shared_ptr<PastorseGeometry> geometry_;
	std::shared_ptr<PastorseMaterial> material_;
};

#endif