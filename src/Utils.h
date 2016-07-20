#pragma once
#include <string>

inline std::string intTextureName(int v)
{
	std::string s = "0000" + std::to_string(v);
	return s.substr(s.size() - 4);
}
