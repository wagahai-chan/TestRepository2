#include <DxLib.h>
#include "player.h"
#include <Scene\GameScene.h>


player::player()
{
	_crimpID = CRIMP_ID::MOVEOBJECT;
	Init();
}

player::player(Vector2Dbl pos, Vector2Dbl size)
{
	for (int j = 0; j < 4; j++)
	{
		_move[j] = false;
	}

	_move[static_cast<int>(MOVE_ID::DOWN)] = true;

	_pos = pos;
	_size = size;
	_crimpID = CRIMP_ID::MOVEOBJECT;
	_unitID = UNIT_ID::PLAYER;
	_objID = OBJ_ID::PLAYER;
	_layer = LAYER::CHAR;

	Init();
}


void player::Update(void)
{
	Obj::Draw();

	if (DestroyProc())
	{
		return;
	}

	if (!lpSceneMng.makeFlag)
	{
		_input->Update();

		Screen();
		Move();

		for (int j = 0; j < static_cast<int>(MOVE_ID::MAX); j++)
		{
			lpSceneMng.check[static_cast<int>(UNIT_ID::PLAYER)][j] = false;
		}

		lpSceneMng.AddActQue({ ACT_QUE::CHECK_DEATH,*this });
		lpSceneMng.AddActQue({ ACT_QUE::CHECK_HIT,*this });		// ﾌﾞﾛｯｸ等の動かないｵﾌﾞｼﾞｪｸﾄとの当たり判定
		lpSceneMng.AddActQue({ ACT_QUE::CHECK_MOVE,*this });
	}

	return;
}

player::~player()
{
}

void player::Move(void)
{
	
	if (_input->state(INPUT_ID::RIGHT).first && !_move[static_cast<int>(MOVE_ID::RIGHT)])
	{
		_pos.x += 2;
		_turn = false;
		if (_pos.x >= lpSceneMng.ScreenCenter.x)
		{
			lpSceneMng.Pos[2] = lpSceneMng.Pos[2] + 2;
		}
	}
	if (_input->state(INPUT_ID::LEFT).first && !_move[static_cast<int>(MOVE_ID::LEFT)])
	{
		_pos.x -= 2;
		_turn = true;
		if (_pos.x >= lpSceneMng.ScreenCenter.x)
		{
			lpSceneMng.Pos[2] = lpSceneMng.Pos[2] - 2;
		}
	}

	if (_input->state(INPUT_ID::RIGHT).first || _input->state(INPUT_ID::LEFT).first)
	{
		SetAlive(STATE::RUN);
	}
	else
	{
		SetAlive(STATE::NORMAL);
	}

	// 落下
	if (!_move[static_cast<int>(MOVE_ID::DOWN)] && !flag)
	{
		_pos.y += 10.0;
	}
	

	// ｼﾞｬﾝﾌﾟ制御
	if (_input->state(INPUT_ID::LEFTBUTTON).first && !_input->state(INPUT_ID::LEFTBUTTON).second && !flag /*&& _actID == ACT_ID::STOP*/)
	{
		flag = true;
		count = 0;
	}

	if (flag && !_move[static_cast<int>(MOVE_ID::UP)])
	{
		if (count < 15)
		{
			_pos.y -= 10.0;
		}
		else
		{
			flag = false;
		}
		
		count++;
	}
	else if (_move[static_cast<int>(MOVE_ID::UP)])
	{
		flag = false;
	}
}

void player::Screen(void)
{
	if (lpSceneMng.ScreenCenter.x - _pos.x <= 0.0)
	{
		lpSceneMng.PX = lpSceneMng.ScreenCenter.x - _pos.x;
	}

	for (int j = 0; j < 2; j++)
	{
		if (lpSceneMng.Pos[j] - _pos.x >= lpSceneMng.ScreenSize.x)
		{
			lpSceneMng.Pos[j] = lpSceneMng.Pos[j] - lpSceneMng.ScreenSize.x * 2;
		}
		if (_pos.x - lpSceneMng.Pos[j] >= lpSceneMng.ScreenSize.x)
		{
			lpSceneMng.Pos[j] = lpSceneMng.Pos[j] + lpSceneMng.ScreenSize.x * 2;
		}
	}

	if (_pos.x < lpSceneMng.ScreenCenter.x)
	{
		lpSceneMng.Pos[2] = 900.0;
	}
}

void player::Init(void)
{
	AnimVector data;

	data.emplace_back(IMAGE_ID("ｷｬﾗ")[0], 0);
	SetAnim(STATE::NORMAL, data);

	for (int j = 0; j < 20; j++)
	{
		data.emplace_back(IMAGE_ID("ｷｬﾗrun")[j], j * 2 + 2);
	}
	SetAnim(STATE::RUN, data);

	data.emplace_back(IMAGE_ID("ｷｬﾗ")[0], 1);
	data.emplace_back(-1, 2);
	SetAnim(STATE::DEATH,data);

	data.emplace_back(IMAGE_ID("ｷｬﾗ")[0], 1);
	SetAnim(STATE::GOAL, data);

	/*data.emplace_back(IMAGE_ID("PL爆発")[0], 20);
	data.emplace_back(IMAGE_ID("PL爆発")[1], 25);
	data.emplace_back(IMAGE_ID("PL爆発")[2], 30);
	data.emplace_back(IMAGE_ID("PL爆発")[3], 35);
	data.emplace_back(-1, 40);
	SetAnim(STATE::NORMAL, data);*/

	_input = std::make_shared<KeyState>();

	

	state(STATE::NORMAL);
}
