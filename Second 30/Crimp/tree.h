#pragma once
#include "Obj.h"
#include <Scene\SceneMng.h>
#include <Scene\BaseScene.h>

class tree :
	public Obj
{
public:
	tree();
	tree(Vector2Dbl pos, Vector2Dbl size);
	~tree();
	void Update(void) override;
private:
	void Init(void);
};

