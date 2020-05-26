#include <memory>
#include <DxLib.h>
#include <Obj.h>
#include "SelectScene.h"
#include "GameScene.h"
#include "MakeScene.h"
#include "SceneMng.h"


SelectScene::SelectScene()
{
	gameID = GAME_ID::MAKE;
}


SelectScene::~SelectScene()
{
}

unique_Base SelectScene::Update(unique_Base own)
{
	lpSceneMng.AddDrawQue({ IMAGE_ID("¾Ú¸Ä")[0], 200.0 + static_cast<int>(gameID) * 400, 300.0, 0 ,false});

	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT)
	{
		gameID = GAME_ID::MAKE;
	}
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT)
	{
		gameID = GAME_ID::PLAY;
	}

	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_4 && gameID == GAME_ID::MAKE)
	{
		return std::make_unique<MakeScene>();
	}
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_4 && gameID == GAME_ID::PLAY)
	{
		return std::make_unique<GameScene>();
	}


	return std::move(own);
}
