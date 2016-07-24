#include "App.h"
#include <SDL2/SDL.h>
#include "Misc.h"

App::App() :
	sdl(SDL_INIT_VIDEO),
	window("Open Prison",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		1280, 960,
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
	shiftX = 0;
	shiftY = 0;
	selectionMode = false;
}

void App::mainLoop()
{
	while (!exitFlag)
	{
		update();
		draw();

		SDL_Delay(1);
	}
}

void App::draw()
{
	renderer.SetDrawBlendMode(SDL_BLENDMODE_NONE);
	renderer.SetDrawColor();
	renderer.Clear();

	world.draw(worldScale.get(), shiftX, shiftY);
	renderer.Present();
}

void App::update()
{
	processEvent();
	worldScale.update();
	world.update();
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
				shiftY += shiftSpeed * worldScale.get();
				break;
			case SDLK_DOWN:
				shiftY -= shiftSpeed * worldScale.get();
				break;
			case SDLK_LEFT:
				shiftX += shiftSpeed * worldScale.get();
				break;
			case SDLK_RIGHT:
				shiftX -= shiftSpeed * worldScale.get();
				break;
			case SDLK_PAGEDOWN:
				worldScale.zoomOut();
				break;
			case SDLK_PAGEUP:
				worldScale.zoomIn();
				break;
			}
			break;
		case SDL_MOUSEWHEEL:
		{
			int y = event.wheel.y;
			if (y > 0)
				worldScale.zoomIn();
			if (y < 0)
				worldScale.zoomOut();
			std::cout << "scale " << worldScale.get() << std::endl;
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
	selectionPoint = world.screenToWorld(pos.GetX(), pos.GetY(), worldScale.get(), shiftX, shiftY);
	setSelection(selectionPoint);
}

void App::onMouseLeftUp(const Vec2& pos)
{
	selectionMode = false;
	world.setAreaSelection(SDL2pp::Rect());

	for (int row = selectionRect.GetY(); row <= selectionRect.GetY2(); ++row)
	{
		for (int col = selectionRect.GetX(); col <= selectionRect.GetX2(); ++col)
		{
			world.addWallBuildTask({ col, row });
		}
	}
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
		setSelection(world.screenToWorld(pos.GetX(), pos.GetY(), worldScale.get(), shiftX, shiftY));
}

void App::setSelection(const Vec2& pos)
{
	selectionRect = rectFromCorners(selectionPoint, pos);
	world.setAreaSelection(selectionRect);
}
