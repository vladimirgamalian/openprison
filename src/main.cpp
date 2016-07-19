#include <iostream>
#include <exception>
#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include "World.h"

int main(int argc, char *args[])
{
	try {

		SDL2pp::SDL sdl(SDL_INIT_VIDEO);

		SDL2pp::Window window("Open Prison",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			640, 480,
			SDL_WINDOW_RESIZABLE);

		SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
		float worldScale = 1.f;

		World world(renderer);

		for (;;)
		{
			SDL_Event event;
			while (SDL_PollEvent(&event)) 
			{
				switch (event.type)
				{
				case SDL_QUIT:
					return EXIT_SUCCESS;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						return EXIT_SUCCESS;
					}
					break;
				case SDL_MOUSEWHEEL:
					{
						int y = event.wheel.y;
						if (y > 0)
						{
							worldScale += 0.1f;
						}
						if (y < 0)
						{
							worldScale -= 0.1f;
						}
					}
					break;
				}
				
			}

			renderer.Clear();
			world.draw(worldScale);
			renderer.Present();
			SDL_Delay(1);
		}

		return EXIT_SUCCESS;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}
