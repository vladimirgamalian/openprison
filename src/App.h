#pragma once
#include <SDL2pp/SDL2pp.hh>
#include "World.h"

class App
{
public:
	App();
	void execute();

private:
	void init();
	void mainLoop();
	void update();

	SDL2pp::SDL sdl;
	SDL2pp::Window window;
	SDL2pp::Renderer renderer;
	World world;

	bool exitFlag = false;
	float worldScale;
	float shiftX;
	float shiftY;
};
