#pragma once
#ifndef Artist
#include "Artist.h"
#endif
#ifndef vector
#include <vector>
#endif
class Controller {
public:
	static bool quit;
	//Keeps track of mouse Pos
	static int mouseX, mouseY;
	static bool mouseMoved;
	static SDL_Point lastMousePos;
	static Uint32 SDLMouseStates;
	static std::vector<int> keyboardStates;
	static std::vector<int> mouseStates;
	static bool TickLimiter;
	static SDL_Point mouseWheelMovment;
	static Uint32 state;
	enum state
	{
		STATE_TITLE,
		STATE_MAP,
		STATE_COMBAT
	};


	bool loadController();
	//Checks for inputs from the user
	void controller();
};
