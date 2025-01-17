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
	void Gap(void);
	void Insert(void);
	void Removal(void);
	bool Check(void);
private:
	friend MakeScene;
	void Init(void);
	std::shared_ptr<InputState> _input;
	Vector2    _chip;	// 配列番号
	Vector2Dbl _cPos;	// 実際のｶｰｿﾙの座標
	int _map[12][20];
	int name[static_cast<int>(OBJ_ID::MAX)];
	int num = 0;
	OBJ_ID obj[static_cast<int>(OBJ_ID::MAX)];
	Vector2Dbl gap;	// ｵﾌﾞｼﾞｪｸﾄのy軸のｽﾞﾚ補正
};

