#pragma once
#ifndef __ILESSON_H__
#define __ILESSON_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

class ILesson
{
public:
	virtual int start(unsigned, unsigned) = 0;
};

#endif // __ILESSON_H__