#include <algorithm>
#include <DxLib.h>
#include <_debug\_DebugConOut.h>
#include "GameScene.h"
#include <Scene/func/FuncCheckHit.h>



GameScene::GameScene()
{
	lpImageMng.GetID("ｷｬﾗ", "image/kyara3.png", { 50,50 }, { 1,1 });
	lpImageMng.GetID("ﾌﾞﾛｯｸ", "image/block2.png", { 50,50 }, { 1,1 });
	lpImageMng.GetID("鋸", "image/saw.png", { 50,50 }, { 1,1 });
	lpImageMng.GetID("ｹﾞｰﾄ", "image/gate.png", { 48,80 }, { 1,1 });

	_objList.emplace_back(new gate({ 300.0,435.0 }, { 48,80 }));

	_objList.emplace_back(new player({ 150.0,440.0 }, { 50,50 }));

	_objList.emplace_back(new saw({ 400.0,450.0 }, { 50,50 }));
	_objList.emplace_back(new saw({ 400.0,200.0 }, { 50,50 }));
	
	for (int j = 0; j < 10; j++)
	{
		_objList.emplace_back(new block({ 100.0 + 50.0 * j,500.0 }, { 50,50 }));
	}
	_objList.emplace_back(new block({ 675.0,500.0 }, { 50,50 }));
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
		default:
			AST();
			break;
		}
	}
}
