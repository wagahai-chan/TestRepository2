#pragma once
#include "Obj.h"
#include <memory>
#include <Scene\SceneMng.h>
#include <Scene\BaseScene.h>
#include <input\inputState.h>
#include <input\keyState.h>

class cursor :
	public Obj
{
public:
	cursor();
	cursor(Vector2Dbl pos, Vector2Dbl size);
	void Update(void) override;
	~cursor();
	void Move(void);
private:
	void Init(void);
	std::shared_ptr<InputState> _input;
};

