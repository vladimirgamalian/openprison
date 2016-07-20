#pragma once
#include <SDL2pp/SDL2pp.hh>
#include <vector>
#include "Vec2.h"

class Worker
{
public:
	Worker(SDL2pp::Renderer& renderer);
	void draw();
	void update();
	void setDebugPath();

private:
	std::unique_ptr<SDL2pp::Texture> textures[3];
	SDL2pp::Renderer& renderer;
	SDL2pp::Point pos;
	std::vector<Vec2> path;
	size_t cursor = 0;
};
