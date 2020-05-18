#include <DxLib.h>
#include "player.h"
#include <Scene\GameScene.h>


player::player()
{
	_unitID = UNIT_ID::PLAYER;
	_actID = ACT_ID::FALL;
	Init();
}

player::player(Vector2Dbl pos, Vector2Dbl size)
{
	_pos = pos;
	_size = size;
	_move = true;
	_unitID = UNIT_ID::PLAYER;
	_actID = ACT_ID::FALL;
	
	Init();
}


void player::Update(void)
{
	if (DestroyProc())
	{
		return;
	}

	_input->Update();

	/*if (_input->state(INPUT_ID::DOWNBUTTON).first)
	{
		_pos.x += 10.0;
	}*/
	

	Move();

	lpSceneMng.AddActQue({ ACT_QUE::CHECK_HIT,*this });

	Obj::Draw();
	return;
}

player::~player()
{
}

void player::Move(void)
{
	
	if (_input->state(INPUT_ID::RIGHT).first && _move == true)
	{
		_pos.x += 2;
		_turn = false;
	}
	if (_input->state(INPUT_ID::LEFT).first && _move == true)
	{
		_pos.x -= 2;
		_turn = true;
	}
	/*if (!_input->state(INPUT_ID::RIGHT).first && !_input->state(INPUT_ID::RIGHT).second)
	{
		SetAlive(STATE::NORMAL);
	}
	SetAlive(STATE::NORMAL);*/

	// —Ž‰º
	if (_actID == ACT_ID::FALL)
	{
		_pos.y += 10.0;
	}
	

	// ¼Þ¬ÝÌß§Œä
	if (_input->state(INPUT_ID::LEFTBUTTON).first && !_input->state(INPUT_ID::LEFTBUTTON).second && !flag && _actID == ACT_ID::STOP)
	{
		_actID = ACT_ID::JUMP;
		flag = true;
		count = 0;
	}

	if (flag)
	{
		if (count < 15)
		{
			_pos.y -= 10.0;
		}
		else
		{
			flag = false;
			_actID = ACT_ID::FALL;
		}
		
		count++;
	}
}

void player::Init(void)
{
	AnimVector data;

	data.emplace_back(IMAGE_ID("·¬×")[0], 0);
	SetAnim(STATE::NORMAL, data);

	for (int j = 0; j < 20; j++)
	{
		data.emplace_back(IMAGE_ID("·¬×run")[j], j * 2 + 2);
	}	
	SetAnim(STATE::RUN, data);

	data.emplace_back(IMAGE_ID("·¬×")[0], 0);
	SetAnim(STATE::NORMAL, data);

	data.emplace_back(IMAGE_ID("·¬×")[0], 1);
	data.emplace_back(-1, 2);
	SetAnim(STATE::DEATH,data);

	data.emplace_back(IMAGE_ID("·¬×")[0], 1);
	data.emplace_back(-1, 2);
	SetAnim(STATE::GOAL, data);

	_input = std::make_shared<KeyState>();

	

	state(STATE::RUN);
}
