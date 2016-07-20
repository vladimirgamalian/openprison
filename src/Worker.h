#pragma once
#include <SDL2pp/SDL2pp.hh>

class Worker
{
public:
	Worker(SDL2pp::Renderer& renderer);
	void draw();
	void update();

private:
	std::unique_ptr<SDL2pp::Texture> textures[3];
	SDL2pp::Renderer& renderer;
	SDL2pp::Point pos;
};
