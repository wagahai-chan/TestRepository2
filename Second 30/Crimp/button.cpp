#include "button.h"



button::button()
{
}

button::button(Vector2Dbl pos, Vector2Dbl size)
{
	_pos = pos;
	_size = size;
	_crimpID = CRIMP_ID::CRIMP;
	_objID = OBJ_ID::BUTTON;

	Init();
}


button::~button()
{
}

void button::Update(void)
{
	if (DestroyProc())
	{
		return;
	}

	Obj::Draw();

	return;
}

void button::Init(void)
{
	AnimVector data;

	data.emplace_back(IMAGE_ID("½²¯Á")[0], 0);
	SetAnim(STATE::NORMAL, data);

	data.emplace_back(IMAGE_ID("½²¯Á")[1], 0);
	SetAnim(STATE::GOAL, data);

	state(STATE::NORMAL);
}
