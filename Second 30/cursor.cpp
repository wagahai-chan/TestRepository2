#include "cursor.h"



cursor::cursor()
{
}

cursor::cursor(Vector2Dbl pos, Vector2Dbl size)
{
	_cPos = pos;
	_chip.x = static_cast<int>(_cPos.x) / 50.0 - 1.0;
	_chip.y = static_cast<int>(_cPos.y) / 50.0 - 1.0;
	_pos.x = (50.0 *_chip.x) + 25;
	_pos.y = (50.0 *_chip.y) + 25;
	_size = size;

	for (int y = 0; y < 12; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			_map[y][x] = 0;
		}
	}

	_name = IMAGE_ID("Ãﬁ€Ø∏")[0];
	obj = OBJ_ID::BLOCK;
	_unitID = UNIT_ID::CURSOR;
	_objID = OBJ_ID::NON;

	Init();
}


void cursor::Update(void)
{
	_input->Update();

	Move();
	change();

	lpSceneMng.AddDrawQue({ _name,_pos.x,_pos.y,0,false });

	if (!_input->state(INPUT_ID::RIGHTBUTTON).first && _input->state(INPUT_ID::RIGHTBUTTON).second && _map[_chip.y][_chip.x] == 0)
	{
		_map[_chip.y][_chip.x] = static_cast<int>(obj);
		lpSceneMng.AddMakeQue({ obj,*this });
	}
	if (_input->state(INPUT_ID::LEFTBUTTON).first && !_input->state(INPUT_ID::LEFTBUTTON).second && _map[_chip.y][_chip.x] != 0)
	{
		_map[_chip.y][_chip.x] = 0;
		lpSceneMng.AddDeleteQue({ obj,*this });
	}

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

	move(_input, INPUT_ID::LEFT, _cPos.x, -10);
	move(_input, INPUT_ID::RIGHT, _cPos.x, 10);
	move(_input, INPUT_ID::UP, _cPos.y, -10);
	move(_input, INPUT_ID::DOWN, _cPos.y, 10);

	_chip.x = static_cast<int>(_cPos.x) / 50 - 1;
	_chip.y = static_cast<int>(_cPos.y) / 50 - 1;
	_pos.x = (50.0 *_chip.x) + 25;
	_pos.y = (50.0 *_chip.y) + 25;
}

void cursor::change(void)
{
	if (_input->state(INPUT_ID::R1).first && !_input->state(INPUT_ID::R1).second)
	{
		_name = IMAGE_ID("ƒﬁ◊—")[0];
		obj = OBJ_ID::DRUM;
	}
	if (_input->state(INPUT_ID::L1).first && !_input->state(INPUT_ID::L1).second)
	{
		_name = IMAGE_ID("Ãﬁ€Ø∏")[0];
		obj = OBJ_ID::BLOCK;
	}
}

void cursor::Init(void)
{
	AnimVector data;

	data.emplace_back(IMAGE_ID("∂∞øŸ")[0], 0);
	SetAnim(STATE::NORMAL, data);

	state(STATE::NORMAL);

	_input = std::make_shared<KeyState>();
}
