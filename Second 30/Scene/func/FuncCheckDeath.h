#pragma once
#include <Scene/BaseScene.h>


struct FuncCheckDeath
{
	bool operator()(ActQueT& actQue, void* scene);
};