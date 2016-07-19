#include <iostream>
#include <exception>
#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

int main(int argc, char *args[])
{
	try {

		SDL2pp::SDL sdl(SDL_INIT_VIDEO);

		SDL2pp::Window window("Open Prison",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			640, 480,
			SDL_WINDOW_RESIZABLE);

		SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
		SDL2pp::Texture sprites(renderer, "M484SpaceSoldier.png");

		for (;;)
		{
			SDL_Event event;
			while (SDL_PollEvent(&event)) 
			{
				if (event.type == SDL_QUIT)
				{
					return EXIT_SUCCESS;
				}
				else if (event.type == SDL_KEYDOWN) 
				{
					switch (event.key.keysym.sym) 
					{
					case SDLK_ESCAPE:
						return EXIT_SUCCESS;
					}
				}
			}

			renderer.Clear();
			renderer.Copy(sprites);
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
