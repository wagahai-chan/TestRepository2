#pragma once
#include "Obj.h"
#include <Scene\SceneMng.h>
#include <Scene\BaseScene.h>

class button :
	public Obj
{
public:
	button();
	button(Vector2Dbl pos, Vector2Dbl size);
	~button();
	void Update(void) override;
private:
	void Init(void);
};

