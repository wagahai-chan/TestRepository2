#include "tree.h"



tree::tree()
{
}

tree::tree(Vector2Dbl pos, Vector2Dbl size)
{
	_pos = pos;
	_size = size;
	_unitID = UNIT_ID::CRIMP;
	_objID = OBJ_ID::TREE;

	Init();
}


tree::~tree()
{
}

void tree::Update(void)
{
	if (DestroyProc())
	{
		return;
	}

	Obj::Draw();

	return;
}

void tree::Init(void)
{
	AnimVector data;

	data.emplace_back(IMAGE_ID("–Ø")[0], 0);
	SetAnim(STATE::NORMAL, data);

	state(STATE::NORMAL);
}
