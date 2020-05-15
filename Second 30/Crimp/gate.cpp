#include "gate.h"



gate::gate()
{
}

gate::gate(Vector2Dbl pos, Vector2Dbl size)
{
	_pos = pos;
	_size = size;
	_unitID = UNIT_ID::CRIMP;
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

	state(STATE::NORMAL);
}
