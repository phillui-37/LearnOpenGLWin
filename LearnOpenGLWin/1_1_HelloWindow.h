#pragma once
#ifndef __1_1_HelloWindow_H__
#define __1_1_HelloWindow_H__

#include "ILesson.h"

class Lesson : public ILesson
{
public:
	int start(unsigned, unsigned) override;
protected:
	GLFWwindow* init(unsigned, unsigned);
	void loop(GLFWwindow*);
};

#endif // __1_1_HelloWindow_H__
