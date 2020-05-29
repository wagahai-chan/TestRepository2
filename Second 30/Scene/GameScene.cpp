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
		//_objList�ɂ͒l�������Ă��Ȃ�����v�f(INPUT_ID��)�̃T�C�Y���m�ۂ��Ȃ��Ƃ����Ȃ�
		//_objList.resize(static_cast<size_t>(lpSceneMng._saveList.end()));
		fread(
			_objList.data(),
			sizeof(_objList[0]),
			_objList.size(),
			file);
		fclose(file);
	}

	//std::copy(lpSceneMng._saveList.begin(), lpSceneMng._saveList.end(), std::back_inserter(_objList));

	lpSceneMng.makeFlag = false;
}


GameScene::~GameScene()
{
}

unique_Base GameScene::Update(unique_Base own)
{
	cnt--;

	lpSceneMng.AddDrawQue({ IMAGE_ID("�w�i")[0],lpSceneMng.Pos[0],lpSceneMng.ScreenCenter.y,1.0,0,LAYER::BG,false });
	lpSceneMng.AddDrawQue({ IMAGE_ID("�w�i")[0],lpSceneMng.Pos[1],lpSceneMng.ScreenCenter.y,1.0,0,LAYER::BG,false });

	lpSceneMng.AddDrawQue({ IMAGE_ID("����")[cnt / 60 / 10],lpSceneMng.Pos[2],50.0,1.0,0,LAYER::UI,false });
	lpSceneMng.AddDrawQue({ IMAGE_ID("����")[cnt / 60 % 10],lpSceneMng.Pos[2] + 32.0,50.0,1.0,0,LAYER::UI,false });

	if (cnt < 0)
	{
		return std::make_unique<GoalScene>();
	}
	

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

	/*for (auto data : _objList)
	{
		if ((*data).unitID() == UNIT_ID::PLAYER)
		{
			lpSceneMng.AddDrawQue({ IMAGE_ID("����")[0],(*data).pos().x + lpSceneMng.ScreenCenter.x - 50.0,50.0,0,false });
		}

	}*/

	

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
