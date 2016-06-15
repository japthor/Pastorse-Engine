#ifndef INCLUDE_PASTORSEWINDOW_H_
#define INCLUDE_PASTORSEWINDOW_H_ 1

#include <string> 
#include "PastorseTypes.h"

class PastorseWindow
{
public:
	~PastorseWindow(){};

	/// The function Init in engine Calls this function
	void initWindow(int width, int height, std::string name);

	/**
	* Resizes the window
	*
	* @param width new width.
	* @param height new height.
	*/
	void resizeWindow(int width, int height);

	/// Close the Window
	void closeWindow();

	/**
	* Testing MultiThreading 
	*
	* @param win_swap 0 window context, 1 thread context.
	*/
	void swapBuffers(int32 win_swap);
	/// Calls the GLFW PollEvents
	void pollEvents();
	/// Is the Window Closed
	bool isClosedWindow();
	/**
	* Sets the window color
	*
	* @param r r.
	* @param g g.
	* @param b b.
	* @param a a.
	*/
	void setColor(float r, float g, float b, float a);
	
	/**
	* Testing MultiThreading. Makes the current context (dont' use it)
	*
	* @param win_swap 0 window context, 1 thread context.
	*/
	void makeContextCurrent(int32 context);

  void frameTime();
  float getDeltaTime();

private:
  friend class PastorseEngine;
  PastorseWindow(const PastorseWindow&);
  PastorseWindow& operator= (const PastorseWindow&);
  PastorseWindow();

	std::string name_;
	int width_;
	int height_;

  float delta_time_;
  float last_frame_;

};


enum Key{
	kKey_0 = 48,
	kKey_1,
	kKey_2,
	kKey_3,
	kKey_4,
	kKey_5,
	kKey_6,
	kKey_7,
	kKey_8,
	kKey_9,

	kKey_A = 65,
	kKey_B,
	kKey_C,
	kKey_D,
	kKey_E,
	kKey_F,
	kKey_G,
	kKey_H,
	kKey_I,
	kKey_J,
	kKey_K,
	kKey_L,
	kKey_M,
	kKey_N,
	kKey_O,
	kKey_P,
	kKey_Q,
	kKey_R,
	kKey_S,
	kKey_T,
	kKey_U,
	kKey_V,
	kKey_W,
	kKey_X,
	kKey_Y,
	kKey_Z,
};

enum Special_Key{
	kSpecial_Key_Space = 32,

	kSpecial_Key_Escape = 256,
	kSpecial_Key_Enter,

	kSpecial_Key_Right = 262,
	kSpecial_Key_Left,
	kSpecial_Key_Down,
	kSpecial_Key_Up,

	kSpecial_Key_F1 = 290,
	kSpecial_Key_F2,
	kSpecial_Key_F3,
	kSpecial_Key_F4,
	kSpecial_Key_F5,
	kSpecial_Key_F6,
	kSpecial_Key_F7,
	kSpecial_Key_F8,
	kSpecial_Key_F9,
	kSpecial_Key_F10,
	kSpecial_Key_F11,
	kSpecial_Key_F12,

};

class PastorseInput
{
public:
  ~PastorseInput(){};

  bool getKey(Key key);
  bool getSpecialKey(Special_Key key);

private:
  friend class PastorseEngine;
  PastorseInput(const PastorseInput&);
  PastorseInput& operator= (const PastorseInput&);
  PastorseInput();

};

#endif