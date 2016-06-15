#include "PastorseTexture.h"

PastorseTexture::PastorseTexture(){

}

void PastorseTexture::loadTexture(const char8* location){
  PastorseGPU* GPUInstance = nullptr;
  GPUInstance = PastorseGPU::getInstance();

  GPUInstance->uploadTexture(location, &texture_);
}

void PastorseTexture::loadDepthTexture(){
  PastorseGPU* GPUInstance = nullptr;
  GPUInstance = PastorseGPU::getInstance();

  GPUInstance->uploadDepthTexture(&texture_);
}


void PastorseTexture::setTexture(uint32 program){
  PastorseGPU* GPUInstance = nullptr;
  GPUInstance = PastorseGPU::getInstance();

  GPUInstance->setTexture("texture_",&texture_, program);
}

uint32 PastorseTexture::getTexture(){
  return texture_;
}