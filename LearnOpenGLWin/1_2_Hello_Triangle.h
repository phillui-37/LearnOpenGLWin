#pragma once
#ifndef __1_2_HELLO_TRIANGLE_H__
#define __1_2_HELLO_TRIANGLE_H__

#include "ILesson.h"

class Lesson : public ILesson
{
public:
	int start(unsigned, unsigned) override;
};

#endif // __1_2_HELLO_TRIANGLE_H__
