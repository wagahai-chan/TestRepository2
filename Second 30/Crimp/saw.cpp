#include "saw.h"



saw::saw()
{
}

saw::saw(Vector2Dbl pos, Vector2Dbl size)
{
	_pos = pos;
	_size = size;
	_crimpID = CRIMP_ID::CRIMP;
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

	if (!lpSceneMng.makeFlag)
	{
		Move();
	}

	Obj::Draw();

	return;
}

void saw::Move(void)
{
	_pos.x = _endPos.x + abs(75 - count % (75 * 2));
	_rad += 0.05;
	count++;
}

void saw::Init(void)
{
	AnimVector data;

	data.emplace_back(IMAGE_ID("‹˜")[0], 0);
	SetAnim(STATE::NORMAL, data);



	state(STATE::NORMAL);
}
