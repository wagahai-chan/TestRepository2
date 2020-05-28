#include <DxLib.h>
#include "drum.h"



drum::drum()
{
}

drum::drum(Vector2Dbl pos, Vector2Dbl size)
{
	_pos = pos;
	_size = size;
	_crimpID = CRIMP_ID::MOVEOBJECT;
	_objID = OBJ_ID::DRUM;
	_unitID = UNIT_ID::DRUM;

	for (int j = 0; j < 4; j++)
	{
		_move[j] = false;
	}

	_move[static_cast<int>(MOVE_ID::DOWN)] = true;

	Init();
}


drum::~drum()
{
}

void drum::Update(void)
{
	/*if (CheckHitKey(KEY_INPUT_SPACE))
	{
		SetAlive(STATE::RUN);
	}*/

	Obj::Draw();

	if (DestroyProc())
	{
		return;
	}

	if (!lpSceneMng.makeFlag)
	{
		if (!_move[static_cast<int>(MOVE_ID::DOWN)])
		{
			_pos.y += 10.0;
		}

		if (_move[static_cast<int>(MOVE_ID::LEFT)])
		{
			_pos.x += 2;
		}
		if (_move[static_cast<int>(MOVE_ID::RIGHT)])
		{
			_pos.x -= 2;
		}

		for (int j = 0; j < static_cast<int>(MOVE_ID::MAX); j++)
		{
			lpSceneMng.check[static_cast<int>(UNIT_ID::DRUM)][j] = false;
		}

		lpSceneMng.AddActQue({ ACT_QUE::CHECK_HIT,*this });		// ÌÞÛ¯¸“™‚Ì“®‚©‚È‚¢µÌÞ¼Þª¸Ä‚Æ‚Ì“–‚½‚è”»’è
		lpSceneMng.AddActQue({ ACT_QUE::CHECK_MOVE,*this });
	}

	return;
}

void drum::Init(void)
{
	AnimVector data;

	data.emplace_back(IMAGE_ID("ÄÞ×Ñ")[0], 0);
	SetAnim(STATE::NORMAL, data);

	data.emplace_back(IMAGE_ID("ÄÞ×Ñ")[0], 10);
	data.emplace_back(-1, 20);
	SetAnim(STATE::DEATH, data);

	state(STATE::NORMAL);
}
