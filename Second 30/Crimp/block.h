#pragma once
#include "Obj.h"
#include <Scene\SceneMng.h>
#include <Scene\BaseScene.h>

class block :
	public Obj
{
public:
	block();
	block(Vector2Dbl pos, Vector2Dbl size);
	~block();
	void Update(void) override;
private:
	void Init(void);
};

