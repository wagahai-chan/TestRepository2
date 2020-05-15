#include <memory>
#include <DxLib.h>
#include "TitleScene.h"
#include "GameScene.h"
#include "SceneMng.h"


TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

unique_Base TitleScene::Update(unique_Base own)
{
	lpSceneMng.AddDrawQue({ IMAGE_ID("ю╡ды")[0],400.0,300.0,0 });

	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_4)
	{
		return std::make_unique<GameScene>();
	}

	return std::move(own);
}