#ifndef INCLUDE_PASTORSETEXTURE_H_
#define INCLUDE_PASTORSETEXTURE_H_ 1

#include "PastorseGPU.h"

class PastorseTexture
{
public:
  ~PastorseTexture(){};

  void loadTexture(const char8* location = nullptr);
  void loadDepthTexture();
  void setTexture(uint32 program);
  uint32 getTexture();


private:
  friend class PastorseEngine;
  friend class PastorseRenderToTexture;

  PastorseTexture(const PastorseTexture&);
  PastorseTexture& operator= (const PastorseTexture&);
  PastorseTexture();
  
  uint32 texture_;
};

#endif