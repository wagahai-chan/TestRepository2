#include "drum.h"



drum::drum()
{
}

drum::drum(Vector2Dbl pos, Vector2Dbl size)
{
	_pos = pos;
	_size = size;
	_unitID = UNIT_ID::CRIMP;
	_objID = OBJ_ID::DRUM;

	Init();
}


drum::~drum()
{
}

void drum::Update(void)
{
	if (DestroyProc())
	{
		return;
	}

	Obj::Draw();

	return;
}

void drum::Init(void)
{
	AnimVector data;

	data.emplace_back(IMAGE_ID("Фозб")[0], 0);
	SetAnim(STATE::NORMAL, data);

	state(STATE::NORMAL);
}
