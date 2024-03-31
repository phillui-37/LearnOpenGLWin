#pragma once
#ifndef __CONST_H__
#define __CONST_H__

#define LESSON_1_3
constexpr unsigned HEIGHT = 768;
constexpr unsigned WIDTH = 1024;


#ifdef LESSON_1_1
#include "1_1_HelloWindow.h"
#endif

#ifdef LESSON_1_2
#include "1_2_Hello_Triangle.h"
#endif

#ifdef LESSON_1_3
#include "1_3_Shaders.h"
#endif

#endif // __CONST_H__