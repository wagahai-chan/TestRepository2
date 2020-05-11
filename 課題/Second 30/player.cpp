#include <DxLib.h>
#include "player.h"
#include <Scene\GameScene.h>


player::player()
{
}

player::player(Vector2Dbl pos, Vector2Dbl size)
{
	_pos = pos;
	_size = size;

	
	Init();
}


void player::Update(void)
{
	//_input->Update();


	

	Obj::Draw();
	return;
}

player::~player()
{
}

void player::Init(void)
{
	AnimVector data;

	data.emplace_back(IMAGE_ID("·¬×")[0], 0);

	//_input = std::make_shared<KeyState>();
}
