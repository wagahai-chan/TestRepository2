#pragma once
#include "Obj.h"
#include <memory>
#include <Scene\SceneMng.h>
#include <Scene\BaseScene.h>
#include <input\inputState.h>
#include <input\keyState.h>

class player :
	public Obj
{
public:
	player();
	player(Vector2Dbl pos, Vector2Dbl size);
	void Update(void) override;
	~player();
	void Move(void);
	void Screen(void);

	bool flag = false;
	int count;
private:
	void Init(void);
	std::shared_ptr<InputState> _input;
};

