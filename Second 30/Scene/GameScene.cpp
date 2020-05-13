#include <algorithm>
#include <DxLib.h>
#include <_debug\_DebugConOut.h>
#include "GameScene.h"
#include <Scene/func/FuncCheckHit.h>



GameScene::GameScene()
{
	lpImageMng.GetID("·¬×", "image/kyara.png", { 183,200 }, { 1,1 });
	lpImageMng.GetID("ÌÞÛ¯¸", "image/block.png", { 200,200 }, { 1,1 });
    

	_objList.emplace_back(new player({ 400.0,300.0 }, { 0,0 }));
	_objList.emplace_back(new block({ 600.0,300.0 }, { 0,0 }));

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

	for (auto data : _objList)
	{
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			(*data).SetAlive(false);
		}
	}



	return std::move(own);
}

void GameScene::RunActQue(std::vector<ActQueT> actList)
{
	for (auto actQue : actList)
	{
		switch (actQue.first)
		{
		case ACT_QUE::CHECK_HIT:
			FuncCheckHit()(actQue, this);
			break;
		default:
			AST();
			break;
		}
	}
}
