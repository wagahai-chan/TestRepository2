#include "gate.h"



gate::gate()
{
}

gate::gate(Vector2Dbl pos, Vector2Dbl size)
{
	_pos = pos;
	_size = size;
	_crimpID = CRIMP_ID::CRIMP;
	_objID = OBJ_ID::GATE;

	Init();
}


gate::~gate()
{
}

void gate::Update(void)
{
	if (DestroyProc())
	{
		return;
	}

	Obj::Draw();

	return;
}

void gate::Init(void)
{
	AnimVector data;

	data.emplace_back(IMAGE_ID("¹Þ°Ä")[0], 0);
	SetAnim(STATE::NORMAL, data);

	data.emplace_back(IMAGE_ID("¹Þ°Ä")[1], 0);
	SetAnim(STATE::GOAL, data);

	state(STATE::NORMAL);
}
