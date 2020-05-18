#include <memory>
#include <DxLib.h>
#include "GoalScene.h"
#include "GameScene.h"
#include "SceneMng.h"


GoalScene::GoalScene()
{
}


GoalScene::~GoalScene()
{
}

unique_Base GoalScene::Update(unique_Base own)
{
	return std::move(own);
}
