#include "Worker.h"
#include "Utils.h"

Worker::Worker(SDL2pp::Renderer& renderer) : renderer(renderer)
{
	for (int i = 0; i < 4; ++i)
	{
		std::string fileName = "data/people/worker/" + intTextureName(i) + ".png";
		textures[i] = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(renderer, fileName));
	}

	pos.x = 64;
	pos.y = 64;
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

void Worker::clearPath()
{
	path.clear();
	cursor = 0;
}

void Worker::addPath(const Vec2& pos)
{
	path.push_back(pos);
}

Vec2 Worker::getCellPos() const
{
	return Vec2(pos.x / 64, pos.y / 64);
}
