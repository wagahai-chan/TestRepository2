#pragma once
#include "Obj.h"
#include <Scene\SceneMng.h>
#include <Scene\BaseScene.h>

class saw :
	public Obj
{
public:
	saw();
	saw(Vector2Dbl pos, Vector2Dbl size);
	~saw();
	void Update(void) override;
	void Move(void);
private:
	void Init(void);
	int count;
	Vector2Dbl _endPos;
};

