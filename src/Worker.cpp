#include "Worker.h"
#include "Utils.h"

Worker::Worker(SDL2pp::Renderer& renderer) : renderer(renderer)
{
	for (int i = 0; i < 3; ++i)
	{
		std::string fileName = "data/people/worker/" + intTextureName(i) + ".png";
		textures[i] = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(renderer, fileName));
	}

	setDebugPath();
}

void Worker::draw()
{
	SDL2pp::Texture* texture = textures[0].get();
	renderer.Copy(*texture, SDL2pp::NullOpt, pos);
}

void Worker::update()
{
	if (cursor >= path.size())
		return;
	Vec2 target = path[cursor];

	if (target.x > pos.x)
		pos.x++;
	else if (target.x != pos.x)
		pos.x--;

	if (target.y > pos.y)
		pos.y++;
	else if (target.y != pos.y)
		pos.y--;

	if ((target.x == pos.x) && (target.y == pos.y))
		cursor++;
}

void Worker::setDebugPath()
{
	path.push_back({ 64, 0 });
	path.push_back({ 64, 64 });
	path.push_back({ 64, 128 });
	path.push_back({ 128, 128 });
	path.push_back({ 128, 196 });
	path.push_back({ 64, 196 });
	path.push_back({ 0, 196 });
	path.push_back({ 0, 128 });
	path.push_back({ 0, 64 });
	path.push_back({ 0, 0 });
	cursor = 0;
}
