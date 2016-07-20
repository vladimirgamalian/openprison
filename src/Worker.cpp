#include "Worker.h"
#include "Utils.h"

Worker::Worker(SDL2pp::Renderer& renderer) : renderer(renderer)
{
	for (int i = 0; i < 3; ++i)
	{
		std::string fileName = "data/people/worker/" + intTextureName(i) + ".png";
		textures[i] = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(renderer, fileName));
	}
}

void Worker::draw()
{
	SDL2pp::Texture* texture = textures[0].get();
	renderer.Copy(*texture, SDL2pp::NullOpt, pos);
}

void Worker::update()
{
	pos.x++;
	pos.y++;
}
