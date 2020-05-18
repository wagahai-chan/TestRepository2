#pragma once
#include "BaseScene.h"
class GoalScene :
	public BaseScene
{
public:
	GoalScene();
	~GoalScene();
	unique_Base Update(unique_Base own);
};

