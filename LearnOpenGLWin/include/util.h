#pragma once
#ifndef __UTIL_H__
#define __UTIL_H__

#include <string>
#include <fstream>

enum ShaderType {Fragment, Vertex};

std::string load_shader(ShaderType shader_t, const std::string filename)
{
	std::string ret, line;
	const std::string file_ext = shader_t == ShaderType::Fragment ? "frag" : "vert";

	std::ifstream file("shader/" + filename + "." + file_ext);
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			ret += line;
			ret += "\n";
		}
		file.close();
	}
	else
	{
		std::cerr << filename << "." << file_ext << " cannot be opened";
	}
	
	return ret;
}

#endif // __UTIL_H__
