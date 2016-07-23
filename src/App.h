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
	void processEvent();

	void onMouseLeftDown(const Vec2& pos);
	void onMouseLeftUp(const Vec2& pos);
	void onMouseRightDown(const Vec2& pos);
	void onMouseRightUp(const Vec2& pos);
	void onMouseMove(const Vec2& pos);

	SDL2pp::SDL sdl;
	SDL2pp::Window window;
	SDL2pp::Renderer renderer;
	World world;

	bool exitFlag = false;
	float worldScale;
	float shiftX;
	float shiftY;
	bool selectionMode;
	SDL2pp::Point selectionPoint;
};
