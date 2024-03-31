#pragma once
#ifndef __1_3_SHADER_H__
#define __1_3_SHADER_H__

#include "ILesson.h"

class Lesson : public ILesson
{
public:
	int start(unsigned, unsigned) override;
};

#endif // __1_3_SHADER_H__
