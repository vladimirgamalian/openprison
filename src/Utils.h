#pragma once
#include <string>

std::string intTextureName(int v)
{
	std::string s = "0000" + std::to_string(v);
	return s.substr(s.size() - 4);
}
