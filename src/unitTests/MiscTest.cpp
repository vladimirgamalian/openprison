#include "catch.hpp"
#include <SDL2pp/SDL2pp.hh>
#include "../Misc.h"

TEST_CASE("normalizeRect") 
{
	{
		SDL2pp::Rect r{ 0, 0, 4, 2 };
		REQUIRE(r.GetSize() == SDL2pp::Point(4, 2));
		REQUIRE(r.GetTopLeft() == SDL2pp::Point(0, 0));
	}
	{
		SDL2pp::Rect r{ 2, 2, -1, 1 };
		REQUIRE(r.GetSize() == SDL2pp::Point(-1, 1));
		REQUIRE(r.GetTopLeft() == SDL2pp::Point(2, 2));
		normalizeRect(r);
		REQUIRE(r.GetSize() == SDL2pp::Point(1, 1));
		REQUIRE(r.GetTopLeft() == SDL2pp::Point(1, 2));
	}
	{
		SDL2pp::Rect r{ 10, 10, -4, -2 };
		REQUIRE(r.GetSize() == SDL2pp::Point(-4, -2));
		REQUIRE(r.GetTopLeft() == SDL2pp::Point(10, 10));
		normalizeRect(r);
		REQUIRE(r.GetSize() == SDL2pp::Point(4, 2));
		REQUIRE(r.GetTopLeft() == SDL2pp::Point(6, 8));
	}

}

TEST_CASE("rectFromCorners")
{
	//TODO: test
}
