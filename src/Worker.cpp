#include "Worker.h"
#include "Utils.h"

Worker::Worker(SDL2pp::Renderer& renderer) : renderer(renderer)
{
	for (int i = 0; i < 4; ++i)
	{
		std::string fileName = "data/people/worker/" + intTextureName(i) + ".png";
		textures[i] = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(renderer, fileName));
	}

	setDebugPath();
}

void Worker::draw()
{
	int variant = 2;
	if (direction.y < 0)
		variant = 0;
	if (direction.y > 0)
		variant = 2;
	if (direction.x < 0)
		variant = 3;
	if (direction.x > 0)
		variant = 1;
	SDL2pp::Texture* texture = textures[variant].get();
	renderer.Copy(*texture, SDL2pp::NullOpt, pos);
}

void Worker::update()
{
	if (cursor >= path.size())
		return;
	Vec2 target = path[cursor];

	direction.reset();

	if (target.x > pos.x)
		direction.x = 1;
	else if (target.x != pos.x)
		direction.x = -1;

	if (target.y > pos.y)
		direction.y = 1;
	else if (target.y != pos.y)
		direction.y = -1;

	pos += direction;

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
