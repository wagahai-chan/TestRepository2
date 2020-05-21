#include "cursor.h"



cursor::cursor()
{
}

cursor::cursor(Vector2Dbl pos, Vector2Dbl size)
{
	_pos = pos;
	_size = size;

	Init();
}


void cursor::Update(void)
{
	_input->Update();

	Move();

	Obj::Draw();
}

cursor::~cursor()
{
}

void cursor::Move(void)
{
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

	move(_input, INPUT_ID::LEFT, _pos.x, -4);
	move(_input, INPUT_ID::RIGHT, _pos.x, 4);
	move(_input, INPUT_ID::UP, _pos.y, -4);
	move(_input, INPUT_ID::DOWN, _pos.y, 4);
}

void cursor::Init(void)
{
	AnimVector data;

	data.emplace_back(IMAGE_ID("∂∞øŸ")[0], 0);
	SetAnim(STATE::NORMAL, data);

	state(STATE::NORMAL);

	_input = std::make_shared<KeyState>();
}
