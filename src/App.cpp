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
	selectionMode = false;
	dragMapMode = false;
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

	world.draw(worldView.getShift(), worldView.getScale());
	renderer.Present();
}

void App::update()
{
	processEvent();
	worldView.update();
	world.update();
}

void App::processEvent()
{
	const float shiftSpeed = 16.f;

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
				//shiftY += shiftSpeed / worldScale.getScale();
				break;
			case SDLK_DOWN:
				//shiftY -= shiftSpeed / worldScale.getScale();
				break;
			case SDLK_LEFT:
				//shiftX += shiftSpeed / worldScale.getScale();
				break;
			case SDLK_RIGHT:
				//shiftX -= shiftSpeed / worldScale.getScale();
				break;
			case SDLK_PAGEDOWN:
				//worldScale.zoomOut();
				break;
			case SDLK_PAGEUP:
				//worldScale.zoomIn();
				break;
			}
			break;
		case SDL_MOUSEWHEEL:
		{
			int y = event.wheel.y;
			int mx, my;
			SDL_GetMouseState(&mx, &my);
			if (y > 0)
				worldView.zoomIn({ mx, my });
			if (y < 0)
				worldView.zoomOut({ mx, my });
		}
		break;
		case SDL_MOUSEBUTTONDOWN:
		{
			Vec2 pos{ event.button.x, event.button.y };
			if (event.button.button == SDL_BUTTON_LEFT)
				onMouseLeftDown(pos);
			else if (event.button.button == SDL_BUTTON_MIDDLE)
				onMouseMiddleDown(pos);
			else if (event.button.button == SDL_BUTTON_RIGHT)
				onMouseRightDown(pos);
		}
		break;
		case SDL_MOUSEBUTTONUP:
		{
			Vec2 pos{ event.button.x, event.button.y };
			if (event.button.button == SDL_BUTTON_LEFT)
				onMouseLeftUp(pos);
			else if (event.button.button == SDL_BUTTON_MIDDLE)
				onMouseMiddleUp(pos);
			else if (event.button.button == SDL_BUTTON_RIGHT)
				onMouseRightUp(pos);
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
	selectionCorner = screenToWorldCell(pos);
	setSelection(selectionCorner);
}

void App::onMouseLeftUp(const Vec2& pos)
{
	world.setAreaSelection(SDL2pp::Rect());
	if (selectionMode)
	{
		selectionMode = false;
		Vec2 secondCorner = screenToWorldCell(pos);
		SDL2pp::Rect selectionRect = rectFromCorners(selectionCorner, secondCorner);
		for (int row = selectionRect.GetY(); row <= selectionRect.GetY2(); ++row)
			for (int col = selectionRect.GetX(); col <= selectionRect.GetX2(); ++col)
				world.addWallBuildTask({ col, row });
	}
}

void App::onMouseMiddleDown(const Vec2& pos)
{
	dragMapMode = true;
	dragStartWorldPos = Vec2f(pos) / worldView.getScale();
	dragStartShift = worldView.getShiftF();
}

void App::onMouseMiddleUp(const Vec2& pos)
{
	dragMapMode = false;
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
		setSelection(screenToWorldCell(pos));
	else if (dragMapMode)
	{
		Vec2f s = (Vec2f(pos) / worldView.getScale()) - dragStartWorldPos;
		worldView.setShift(dragStartShift + s);
	}
}

void App::setSelection(const Vec2& secondCorner)
{
	SDL2pp::Rect selectionRect = rectFromCorners(selectionCorner, secondCorner);
	world.setAreaSelection(selectionRect);
}

Vec2 App::screenToWorldCell(const Vec2& pos)
{
	return worldView.screenToWorld(pos) / 64;
}
