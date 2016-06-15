#include "PastorseFrameBuffer.h"
#include "PastorseGPU.h"

PastorseFrameBuffer::PastorseFrameBuffer():frame_buffer_(0), render_buffer_(0){

}

void PastorseFrameBuffer::createFrameBuffer(){
	PastorseGPU* GPUInstance = nullptr;
	GPUInstance = PastorseGPU::getInstance();
	GPUInstance->createFrameBuffer(&frame_buffer_,&render_buffer_);
}

void PastorseFrameBuffer::BindFrameBuffer(){
	PastorseGPU* GPUInstance = nullptr;
	GPUInstance = PastorseGPU::getInstance();
	GPUInstance->bindFrameBuffer(&frame_buffer_);
}

void PastorseFrameBuffer::unBindFrameBuffer(){
  PastorseGPU* GPUInstance = nullptr;
  GPUInstance = PastorseGPU::getInstance();
  GPUInstance->unBindFrameBuffer();
}

void PastorseFrameBuffer::AttachFrameBuffer(uint32 texture, uint32 texture2){
  PastorseGPU* GPUInstance = nullptr;
  GPUInstance = PastorseGPU::getInstance();
  GPUInstance->attachFrameBuffer(texture, texture2, &render_buffer_);
}