#include "saw.h"



saw::saw()
{
}

saw::saw(Vector2Dbl pos, Vector2Dbl size)
{
	_pos = pos;
	_size = size;
	_unitID = UNIT_ID::CRIMP;
	_objID = OBJ_ID::SAW;
	count = 0;
	_endPos = pos;

	Init();
}


saw::~saw()
{
}

void saw::Update(void)
{

	if (DestroyProc())
	{
		return;
	}

	Move();

	Obj::Draw();

	return;
}

void saw::Move(void)
{
	_pos.x = _endPos.x + abs(75 - count % (75 * 2));
	count += 2;
}

void saw::Init(void)
{
	AnimVector data;

	data.emplace_back(IMAGE_ID("‹˜")[0], 0);
	SetAnim(STATE::NORMAL, data);



	state(STATE::NORMAL);
}
