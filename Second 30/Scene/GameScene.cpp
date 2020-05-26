#include <algorithm>
#include <DxLib.h>
#include <_debug\_DebugConOut.h>
#include "GameScene.h"
#include <Scene/func/FuncCheckHit.h>
#include <Scene/func/FuncCheckDeath.h>
#include <Scene/func/FuncCheckMove.h>



GameScene::GameScene()
{
	//_objList.emplace_back(new gate({ 725.0,435.0 }, { 48,80 }));
	//_objList.emplace_back(new button({ 300.0,440 + 10.0 }, { 14,50 }));

	///*_objList.emplace_back(new player({ 150.0,440.0 }, { 50,50 }));*/
	//_objList.emplace_back(new player({ 200.0,300.0 }, { 34,50 }));

	///*_objList.emplace_back(new drum({ 300.0,400.0 }, { 38,50 }));
	//_objList.emplace_back(new tree({ 500.0,325.0 }, { 50,300 }));*/

	//_objList.emplace_back(new saw({ 400.0,475.0 }, { 50,50 }));
	//
	//for (int j = 0; j < 10; j++)
	//{
	//	_objList.emplace_back(new block({ 100.0 + 50.0 * j,500.0 }, { 50,50 }));
	//}
	//_objList.emplace_back(new block({ 400.0,400.0 }, { 50,50 }));
	_objList.emplace_back(new block({ 675.0,500.0 }, { 50,50 }));
	_objList.emplace_back(new block({ 725.0,500.0 }, { 50,50 }));
	/*_objList.emplace_back(new block({ 100.0,450.0 }, { 50,50 }));
	_objList.emplace_back(new block({ 100.0,400.0 }, { 50,50 }));
	_objList.emplace_back(new block({ 100.0,350.0 }, { 50,50 }));
	_objList.emplace_back(new block({ 100.0,300.0 }, { 50,50 }));
	_objList.emplace_back(new block({ 200.0,450.0 }, { 50,50 }));*/

	std::copy(lpSceneMng._saveList.begin(), lpSceneMng._saveList.end(), std::back_inserter(_objList));

	lpSceneMng.makeFlag = false;
}


GameScene::~GameScene()
{
}

unique_Base GameScene::Update(unique_Base own)
{
	lpSceneMng.AddDrawQue({ IMAGE_ID("�w�i")[0],lpSceneMng.Pos[0],lpSceneMng.ScreenCenter.y,0,false });
	lpSceneMng.AddDrawQue({ IMAGE_ID("�w�i")[0],lpSceneMng.Pos[1],lpSceneMng.ScreenCenter.y,0,false });

	for (auto data : _objList)
	{
		(*data).Update();

	}

	for (auto data : _objList)
	{
		if ((*data).crimpID() == CRIMP_ID::MOVEOBJECT)
		{
			if ((*data).state() == STATE::GOAL)
			{
				return std::make_unique<GoalScene>();
			}
		}
	}

	auto itr = std::remove_if(
		_objList.begin(),	// �����͈͂̊J�n
		_objList.end(),		// �����͈͂̏I��
		[](sharedObj& obj) {return(*obj).isDead(); } 	// ����ł������O �����͐^�U��K���Ԃ�(�v���f�B�P�[�g)
	);
	// itr ���������v�f�̐擪�A�h���X
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
