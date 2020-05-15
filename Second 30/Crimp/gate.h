#pragma once
#include "Obj.h"
#include <Scene\SceneMng.h>
#include <Scene\BaseScene.h>

class gate :
	public Obj
{
public:
	gate();
	gate(Vector2Dbl pos, Vector2Dbl size);
	~gate();
	void Update(void) override;
private:
	void Init(void);
};

