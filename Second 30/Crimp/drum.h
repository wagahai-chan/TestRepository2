#pragma once
#include "Obj.h"
#include <Scene\SceneMng.h>
#include <Scene/GameScene.h>
#include <Scene\BaseScene.h>

class drum :
	public Obj
{
public:
	drum();
	drum(Vector2Dbl pos, Vector2Dbl size);
	~drum();
	void Update(void) override;
private:
	void Init(void);
	bool flag = false;
};

