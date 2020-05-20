#include <DxLib.h>
#include "block.h"
#include <Scene\GameScene.h>



block::block()
{
}

block::block(Vector2Dbl pos, Vector2Dbl size)
{
	_pos = pos;
	_size = size;
	_crimpID = CRIMP_ID::CRIMP;
	_objID = OBJ_ID::BLOCK;

	Init();
}


block::~block()
{
}

void block::Update(void)
{
	

	if (DestroyProc())
	{
		return;
	}

	Obj::Draw();

	return;
}

void block::Init(void)
{
	AnimVector data;

	data.emplace_back(IMAGE_ID("ÌÞÛ¯¸")[0], 0);
	SetAnim(STATE::NORMAL, data);

	

	state(STATE::NORMAL);
}
