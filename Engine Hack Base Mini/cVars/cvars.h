#ifndef __CVARS__
#define __CVARS__

#pragma once

#include <Windows.h>
#include "../locals.h"

struct CVars
{
	
};
extern CVars cvar;

struct CFunc
{
public:
	void Init();
};
extern CFunc cfunc;

#endif