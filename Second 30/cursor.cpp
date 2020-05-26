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
	gap.x = 0.0;
	gap.y = 0.0;

	for (int y = 0; y < 12; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			_map[y][x] = 0;
		}
	}

	name[1] = IMAGE_ID("Ãﬁ€Ø∏")[0];
	name[2] = IMAGE_ID("∑¨◊")[0];
	name[3] = IMAGE_ID("ãò")[0];
	name[4] = IMAGE_ID("πﬁ∞ƒ")[0];
	name[5] = IMAGE_ID("Ω≤Ø¡")[0];
	name[6] = IMAGE_ID("ƒﬁ◊—")[0];
	name[7] = IMAGE_ID("ñÿ")[0];

	obj[1] = OBJ_ID::BLOCK;
	obj[2] = OBJ_ID::PLAYER;
	obj[3] = OBJ_ID::SAW;
	obj[4] = OBJ_ID::GATE;
	obj[5] = OBJ_ID::BUTTON;
	obj[6] = OBJ_ID::DRUM;
	obj[7] = OBJ_ID::TREE;

	num = 1;

	_unitID = UNIT_ID::CURSOR;
	_objID = OBJ_ID::NON;

	Init();
}


void cursor::Update(void)
{
	_input->Update();

	Move();
	change();
	Gap();

	lpSceneMng.AddDrawQue({ name[num],_pos.x + gap.x,_pos.y + gap.y,0,false });

	if (!_input->state(INPUT_ID::RIGHTBUTTON).first && _input->state(INPUT_ID::RIGHTBUTTON).second && !Check())
	{
		Insert();
		lpSceneMng.AddMakeQue({ obj[num],*this });
	}
	if (_input->state(INPUT_ID::LEFTBUTTON).first && !_input->state(INPUT_ID::LEFTBUTTON).second && Check())
	{
		Removal();
		lpSceneMng.AddDeleteQue({ obj[num],*this });
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
	if (_input->state(INPUT_ID::R1).first && !_input->state(INPUT_ID::R1).second && num + 1 < static_cast<int>(OBJ_ID::MAX))
	{
		num++;
	}
	if (_input->state(INPUT_ID::L1).first && !_input->state(INPUT_ID::L1).second && num > 1)
	{
		num--;
	}
}

void cursor::Gap(void)
{
	switch (obj[num])
	{
	case OBJ_ID::GATE:
		gap.x = 0.0;
		gap.y = -15.0;
		break;
	case OBJ_ID::TREE:
		gap.x = 0.0;
		gap.y = -25.0;
		break;
	default:
		gap.x = 0.0;
		gap.y = 0.0;
		break;
	}
}

void cursor::Insert(void)
{
	switch (obj[num])
	{
	case OBJ_ID::GATE:
		_map[_chip.y - 1][_chip.x] = static_cast<int>(obj[num]);
		_map[_chip.y][_chip.x] = static_cast<int>(obj[num]);
		break;
	case OBJ_ID::TREE:
		_map[_chip.y][_chip.x] = static_cast<int>(obj[num]);
		_map[_chip.y + 1][_chip.x] = static_cast<int>(obj[num]);
		_map[_chip.y + 2][_chip.x] = static_cast<int>(obj[num]);
		_map[_chip.y + 2][_chip.x + 1] = static_cast<int>(obj[num]);
		_map[_chip.y + 2][_chip.x + 1] = static_cast<int>(obj[num]);
		break;
	default:
		_map[_chip.y][_chip.x] = static_cast<int>(obj[num]);
		break;
	}
}

void cursor::Removal(void)
{
	switch (obj[num])
	{
	case OBJ_ID::GATE:
		_map[_chip.y][_chip.x] = 0;
		_map[_chip.y - 1][_chip.x] = 0;	
		break;
	case OBJ_ID::TREE:
		_map[_chip.y][_chip.x] = 0;
		_map[_chip.y + 1][_chip.x] = 0;
		_map[_chip.y + 2][_chip.x] = 0;
		_map[_chip.y + 2][_chip.x + 1] = 0;
		_map[_chip.y + 2][_chip.x + 1] = 0;
		break;
	default:
		_map[_chip.y][_chip.x] = 0;
		break;
	}
}

bool cursor::Check(void)
{
	if (_map[_chip.y][_chip.x] != 0)
	{
		if (_map[_chip.y][_chip.x] == static_cast<int>(OBJ_ID::GATE))
		{
			if (_map[_chip.y - 1][_chip.x] == static_cast<int>(OBJ_ID::GATE))
			{
				return true;
			}
			return false;
		}
		if (_map[_chip.y][_chip.x] == static_cast<int>(OBJ_ID::TREE))
		{
			if (_map[_chip.y + 1][_chip.x] == static_cast<int>(OBJ_ID::TREE)     &&
				_map[_chip.y + 2][_chip.x] == static_cast<int>(OBJ_ID::TREE)     &&
				_map[_chip.y + 2][_chip.x + 1] == static_cast<int>(OBJ_ID::TREE) &&
				_map[_chip.y + 2][_chip.x + 1] == static_cast<int>(OBJ_ID::TREE))
			{
				return true;
			}
			return false;
		}

		return true;
	}

	if (obj[num] == OBJ_ID::GATE)
	{
		if (_map[_chip.y - 1][_chip.x] == 0)
		{
			return false;
		}
		return true;
	}
	if (obj[num] == OBJ_ID::TREE)
	{
		if (_map[_chip.y + 1][_chip.x] == 0 &&
			_map[_chip.y + 2][_chip.x] == 0 &&
			_map[_chip.y + 2][_chip.x + 1] == 0 &&
			_map[_chip.y + 2][_chip.x + 1] == 0)
		{
			return false;
		}
		return true;
	}

	return false;
}

void cursor::Init(void)
{
	AnimVector data;

	data.emplace_back(IMAGE_ID("∂∞øŸ")[0], 0);
	SetAnim(STATE::NORMAL, data);

	state(STATE::NORMAL);

	_input = std::make_shared<KeyState>();
}
