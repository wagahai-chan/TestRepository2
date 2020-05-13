#pragma once
#include <Scene/BaseScene.h>


struct FuncCheckHit
{
	bool operator()(ActQueT& actQue, void* scene);
};

