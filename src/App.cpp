#include "App.h"
#include <SDL2/SDL.h>

App::App() :
	sdl(SDL_INIT_VIDEO),
	window("Open Prison",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		640, 480,
		SDL_WINDOW_RESIZABLE),
	renderer(window, -1, SDL_RENDERER_ACCELERATED),
	world(renderer)
{

}

void App::execute()
{
	init();
	mainLoop();
}

void App::init()
{
	exitFlag = false;
	worldScale = 0.5f;
	shiftX = 0;
	shiftY = 0;
}

void App::mainLoop()
{
	while (!exitFlag)
	{
		update();
		renderer.Present();
		SDL_Delay(1);
	}
}

void App::update()
{
	const float shiftSpeed = 4.f;

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			exitFlag = true;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				exitFlag = true;
			case SDLK_UP:
				shiftY += shiftSpeed * worldScale;
				break;
			case SDLK_DOWN:
				shiftY -= shiftSpeed * worldScale;
				break;
			case SDLK_LEFT:
				shiftX += shiftSpeed * worldScale;
				break;
			case SDLK_RIGHT:
				shiftX -= shiftSpeed * worldScale;
				break;
			case SDLK_PAGEDOWN:
				worldScale += 0.1f;
				break;
			case SDLK_PAGEUP:
				worldScale -= 0.1f;
				break;
			}
			break;
		case SDL_MOUSEWHEEL:
		{
			int y = event.wheel.y;
			if (y > 0)
				worldScale += 0.1f;
			if (y < 0)
				worldScale -= 0.1f;
		}
		break;
		case SDL_MOUSEBUTTONDOWN:
		{
			int x = event.button.x;
			int y = event.button.y;
			//std::cout << "SDL_MOUSEBUTTONDOWN " << x << ":" << y << std::endl;
			SDL2pp::Point cellPos = world.screenToWorld(x, y, worldScale, shiftX, shiftY);
			//std::cout << "WORLD POS " << cellPos << std::endl;
			if (event.button.button == SDL_BUTTON_LEFT)
				world.addWallBuildTask(cellPos);
			else if (event.button.button == SDL_BUTTON_RIGHT)
				world.removeWall(cellPos);
			else if (event.button.button == SDL_BUTTON_MIDDLE)
				world.setWall(cellPos);
		}
		break;
		}

	}

	world.update();

	renderer.Clear();
	world.draw(worldScale, shiftX, shiftY);
}
