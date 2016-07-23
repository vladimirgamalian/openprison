#include "App.h"
#include <SDL2/SDL.h>
#include "Misc.h"

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
	selectionMode = false;
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
	processEvent();
	world.update();
	renderer.Clear();
	world.draw(worldScale, shiftX, shiftY);
}

void App::processEvent()
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
			std::cout << "scale " << worldScale << std::endl;
		}
		break;
		case SDL_MOUSEBUTTONDOWN:
		{
			Vec2 pos{ event.button.x, event.button.y };

			if (event.button.button == SDL_BUTTON_LEFT)
				onMouseLeftDown(pos);
			else if (event.button.button == SDL_BUTTON_RIGHT)
				onMouseRightDown(pos);

			//std::cout << "SDL_MOUSEBUTTONDOWN " << x << ":" << y << std::endl;
			//SDL2pp::Point cellPos = world.screenToWorld(x, y, worldScale, shiftX, shiftY);
			//std::cout << "WORLD POS " << cellPos << std::endl;
			// 			if (event.button.button == SDL_BUTTON_LEFT)
			// 				world.addWallBuildTask(cellPos);
			// 			else if (event.button.button == SDL_BUTTON_RIGHT)
			// 				world.removeWall(cellPos);
			// 			else if (event.button.button == SDL_BUTTON_MIDDLE)
			// 				world.setWall(cellPos);
		}
		break;
		case SDL_MOUSEBUTTONUP:
		{
			Vec2 pos{ event.button.x, event.button.y };

			if (event.button.button == SDL_BUTTON_LEFT)
				onMouseLeftUp(pos);
			else if (event.button.button == SDL_BUTTON_RIGHT)
				onMouseRightUp(pos);

			//std::cout << "SDL_MOUSEBUTTONDOWN " << x << ":" << y << std::endl;
			//SDL2pp::Point cellPos = world.screenToWorld(x, y, worldScale, shiftX, shiftY);
			//std::cout << "WORLD POS " << cellPos << std::endl;
			// 			if (event.button.button == SDL_BUTTON_LEFT)
			// 				world.addWallBuildTask(cellPos);
			// 			else if (event.button.button == SDL_BUTTON_RIGHT)
			// 				world.removeWall(cellPos);
			// 			else if (event.button.button == SDL_BUTTON_MIDDLE)
			// 				world.setWall(cellPos);
		}
		break;
		case SDL_MOUSEMOTION:
		{
			Vec2 pos{ event.motion.x, event.motion.y };
			onMouseMove(pos);
		}
		}

	}
}

void App::onMouseLeftDown(const Vec2& pos)
{
	selectionMode = true;
	selectionPoint = world.screenToWorld(pos.GetX(), pos.GetY(), worldScale, shiftX, shiftY);
}

void App::onMouseLeftUp(const Vec2& pos)
{
	selectionMode = false;
}

void App::onMouseRightDown(const Vec2& pos)
{

}

void App::onMouseRightUp(const Vec2& pos)
{

}

void App::onMouseMove(const Vec2& pos)
{
	if (selectionMode)
	{
		Vec2 p = world.screenToWorld(pos.GetX(), pos.GetY(), worldScale, shiftX, shiftY);
		SDL2pp::Rect r(selectionPoint, p - selectionPoint);
		normalizeRect(r);
		r.SetW(r.GetW() + 1);
		r.SetH(r.GetH() + 1);
		world.setAreaSelection(r);
	}
}
