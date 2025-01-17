#include <memory>
#include <DxLib.h>
#include "TitleScene.h"
#include "SelectScene.h"
#include "SceneMng.h"


TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

unique_Base TitleScene::Update(unique_Base own)
{
	lpSceneMng.AddDrawQue({ IMAGE_ID("����")[0],400.0,300.0,1.0,0,LAYER::BG,false });

	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_4)
	{
		return std::make_unique<SelectScene>();
	}

	return std::move(own);
}