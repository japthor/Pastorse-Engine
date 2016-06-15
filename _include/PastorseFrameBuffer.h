#ifndef PASTORSEFRAMEBUFFER_H_
#define PASTORSEFRAMEBUFFER_H_ 1

#include "PastorseTypes.h"
#include <memory>

class PastorseFrameBuffer
{
public:
  PastorseFrameBuffer();
  ~PastorseFrameBuffer(){};

  void createFrameBuffer();
  void BindFrameBuffer();
  void unBindFrameBuffer();
  void AttachFrameBuffer(uint32 texture, uint32 texture2);

private:
  PastorseFrameBuffer(const PastorseFrameBuffer&);
  PastorseFrameBuffer& operator= (const PastorseFrameBuffer&);

  uint32 render_buffer_;
  uint32 frame_buffer_;
};

#endif