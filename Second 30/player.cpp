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
	// 左右移動制御
	auto move = [](std::weak_ptr<InputState> keyData, INPUT_ID id, double& pNum, const int speed) {
		// keyData.expired() 終わっているかいないか
		if (!keyData.expired())
		{
			if ((*keyData.lock()).state(id).first)
			{
				pNum += speed;
			}
		}
	};

	move(_input, INPUT_ID::LEFT, _pos.x, -2);
	move(_input, INPUT_ID::RIGHT, _pos.x, 2);
	/*move(_input, INPUT_ID::UP, _pos.y, -2);
	move(_input, INPUT_ID::DOWN, _pos.y, 2);*/

	// 落下
	if (_actID == ACT_ID::FALL)
	{
		_pos.y += 10.0;
	}
	

	// ｼﾞｬﾝﾌﾟ制御
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

	data.emplace_back(IMAGE_ID("ｷｬﾗ")[0], 0);
	SetAnim(STATE::NORMAL, data);

	data.emplace_back(IMAGE_ID("ｷｬﾗ")[0], 1);
	data.emplace_back(-1, 2);
	SetAnim(STATE::DEATH,data);

	_input = std::make_shared<KeyState>();

	

	state(STATE::NORMAL);
}
