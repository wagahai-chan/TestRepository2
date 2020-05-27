#include <algorithm>
#include <DxLib.h>
#include <_debug\_DebugConOut.h>
#include "GameScene.h"
#include <Scene/func/FuncCheckHit.h>
#include <Scene/func/FuncCheckDeath.h>
#include <Scene/func/FuncCheckMove.h>



GameScene::GameScene()
{
	FILE *file;
	fopen_s(&file, "data/map.data", "rb");
	if (file == nullptr)
	{
		std::copy(lpSceneMng._saveList.begin(), lpSceneMng._saveList.end(), std::back_inserter(_objList));
	}
	else
	{
		//_keyConには値が入っていないから要素(INPUT_ID分)のサイズを確保しないといけない
		_objList.resize(lpSceneMng._saveList.end()));
		fread(
			_objList.data(),
			sizeof(_objList[0]),
			_objList.size(),
			file);
		fclose(file);
	}


	lpSceneMng.makeFlag = false;
}


GameScene::~GameScene()
{
}

unique_Base GameScene::Update(unique_Base own)
{
	lpSceneMng.AddDrawQue({ IMAGE_ID("背景")[0],lpSceneMng.Pos[0],lpSceneMng.ScreenCenter.y,0,false });
	lpSceneMng.AddDrawQue({ IMAGE_ID("背景")[0],lpSceneMng.Pos[1],lpSceneMng.ScreenCenter.y,0,false });

	for (auto data : _objList)
	{
		if ((*data).objID() == OBJ_ID::PLAYER)
		{
			if ((*data).state() == STATE::GOAL)
			{
				return std::make_unique<GoalScene>();
			}
		}
	}

	for (auto data : _objList)
	{
		(*data).Update();

	}

	

	auto itr = std::remove_if(
		_objList.begin(),	// ﾁｪｯｸ範囲の開始
		_objList.end(),		// ﾁｪｯｸ範囲の終了
		[](sharedObj& obj) {return(*obj).isDead(); } 	// 死んでるやつを除外 ここは真偽を必ず返す(プレディケート)
	);
	// itr 消したい要素の先頭アドレス
	_objList.erase(itr, _objList.end());

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
		case ACT_QUE::CHECK_DEATH:
			FuncCheckDeath()(actQue, this);
			break;
		case ACT_QUE::CHECK_MOVE:
			FuncCheckMove()(actQue, this);
			break;
		default:
			AST();
			break;
		}
	}
}
