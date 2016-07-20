#pragma once
#include <SDL2pp/SDL2pp.hh>
#include <vector>
#include "Vec2.h"

class World;

class Worker
{
public:
	Worker(SDL2pp::Renderer& renderer, World* world);
	void draw();
	void update();
	void clearPath();
	void addPath(const Vec2& pos);
	Vec2 getCellPos() const;
	void setTarget(const Vec2& pos);
	void resolvePath();

private:
	SDL2pp::Renderer& renderer;
	World* world;
	std::unique_ptr<SDL2pp::Texture> textures[4];
	Vec2 pos;
	std::vector<Vec2> path;
	size_t cursor = 0;
	Vec2 direction;
	Vec2 target;
};
