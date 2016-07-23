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
