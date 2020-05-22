#pragma once
#include "Obj.h"
#include <memory>
#include <Scene\SceneMng.h>
#include <Scene\BaseScene.h>
#include <input\inputState.h>
#include <input\keyState.h>
#include <Scene/MakeScene.h>
#include <Scene/SceneMng.h>

struct MakeScene;

class cursor :
	public Obj
{
public:
	cursor();
	cursor(Vector2Dbl pos, Vector2Dbl size);
	void Update(void) override;
	~cursor();
	void Move(void);
	void change(void);
private:
	friend MakeScene;
	void Init(void);
	std::shared_ptr<InputState> _input;
	Vector2    _chip;	// îzóÒî‘çÜ
	Vector2Dbl _cPos;	// é¿ç€ÇÃ∂∞øŸÇÃç¿ïW
	int _map[12][20];
	int _name;
	OBJ_ID obj;
};

