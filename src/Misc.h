#pragma once

inline void normalizeRect(SDL2pp::Rect& r)
{
	int w = r.GetW();
	if (w < 0)
	{
		r.SetX(r.GetX() + w);
		r.SetW(-w);
	}

	int h = r.GetH();
	if (h < 0)
	{
		r.SetY(r.GetY() + h);
		r.SetH(-h);
	}
}

inline SDL2pp::Rect rectFromCorners(const SDL2pp::Point& p0, const SDL2pp::Point& p1)
{
	SDL2pp::Rect rect(p0, p1 - p0);
	normalizeRect(rect);
	rect.SetW(rect.GetW() + 1);
	rect.SetH(rect.GetH() + 1);
	return rect;
}
