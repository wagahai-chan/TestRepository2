#include <DxLib.h>
#include "player.h"
#include <Scene\GameScene.h>


player::player()
{
	Init();
}

player::player(Vector2Dbl pos, Vector2Dbl size)
{
	_pos = pos;
	_size = size;

	
	Init();
}


void player::Update(void)
{
	_input->Update();

	/*if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT)
	{
		_pos.x += 5.0;
	}
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP)
	{
		_pos.y -= 5.0;
	}*/
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_13)
	{
		_pos.y -= 5.0;
	}

	if (_input->state(INPUT_ID::LEFT1).first)
	{
		_pos.y -= 5.0;
	}
	

	Obj::Draw();
	return;
}

player::~player()
{
}

void player::Init(void)
{
	AnimVector data;

	data.emplace_back(IMAGE_ID("·¬×")[0], 0);
	SetAnim(STATE::NORMAL, data);

	_input = std::make_shared<KeyState>();

	state(STATE::NORMAL);
}
