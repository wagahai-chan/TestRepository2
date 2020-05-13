#include <DxLib.h>
#include "player.h"
#include <Scene\GameScene.h>


player::player()
{
	_unitID = UNIT_ID::PLAYER;
	Init();
}

player::player(Vector2Dbl pos, Vector2Dbl size)
{
	_pos = pos;
	_size = size;
	_unitID = UNIT_ID::PLAYER;
	
	Init();
}


void player::Update(void)
{
	_input->Update();

	/*if (_input->state(INPUT_ID::DOWNBUTTON).first)
	{
		_pos.x += 10.0;
	}*/
	
	Move();

	Obj::Draw();
	return;
}

player::~player()
{
}

void player::Move(void)
{
	// ç∂âEà⁄ìÆêßå‰
	auto move = [](std::weak_ptr<InputState> keyData, INPUT_ID id, double& pNum, const int speed) {
		// keyData.expired() èIÇÌÇ¡ÇƒÇ¢ÇÈÇ©Ç¢Ç»Ç¢Ç©
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
	move(_input, INPUT_ID::UP, _pos.y, -2);
	move(_input, INPUT_ID::DOWN, _pos.y, 2);

	// ºﬁ¨›Ãﬂêßå‰
	if (_input->state(INPUT_ID::LEFTBUTTON).first && !_input->state(INPUT_ID::LEFTBUTTON).second && !flag)
	{
		flag = true;
		count = 0;
	}

	if (flag)
	{
		if (count < 15)
		{
			_pos.y -= 5.0;
		}
		else if (15 <= count && count < 30)
		{
			_pos.y += 5.0;
		}
		else if (count >= 30)
		{
			flag = false;
		}

		count++;
	}
}

void player::Init(void)
{
	AnimVector data;

	data.emplace_back(IMAGE_ID("∑¨◊")[0], 0);
	SetAnim(STATE::NORMAL, data);

	_input = std::make_shared<KeyState>();

	state(STATE::NORMAL);
}
