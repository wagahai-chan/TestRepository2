#include <algorithm>
#include <DxLib.h>
#include "GameScene.h"



GameScene::GameScene()
{
	lpImageMng.GetID("·¬×", "image/kyara.png", { 416,454 }, { 1,1 });
    

	_objList.emplace_back(new player({ 100.0,500.0 }, { 0,0 }));

}


GameScene::~GameScene()
{
}

unique_Base GameScene::Update(unique_Base own)
{

	for (auto data : _objList)
	{
		(*data).Update();

	}

	/*for (auto data : _objList)
	{
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			(*data).SetAlive(false);
		}
	}*/



	return std::move(own);
}
