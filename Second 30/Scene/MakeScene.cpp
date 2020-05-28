#include <algorithm>
#include <DxLib.h>
#include "MakeScene.h"



MakeScene::MakeScene()
{
	lpSceneMng.makeFlag = true;

	lpImageMng.GetID("����", "image/cursor.png", { 30,30 }, { 1,1 });
	

	lpSceneMng._saveList.emplace_back(new cursor({ 200.0,300.0 }, { 30,30 }));
}


MakeScene::~MakeScene()
{
}

unique_Base MakeScene::Update(unique_Base own)
{
	draw();

	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		Move();
		return std::make_unique<GameScene>();
	}

	for (auto data : lpSceneMng._saveList)
	{
		(*data).Update();

	}

	auto itr = std::remove_if(
		lpSceneMng._saveList.begin(),	// �����͈͂̊J�n
		lpSceneMng._saveList.end(),		// �����͈͂̏I��
		[](sharedObj& obj) {return(*obj).isDead(); } 	// ����ł������O �����͐^�U��K���Ԃ�(�v���f�B�P�[�g)
	);
	// itr ���������v�f�̐擪�A�h���X
	lpSceneMng._saveList.erase(itr, lpSceneMng._saveList.end());

	return std::move(own);
}

void MakeScene::Move(void)
{
	for (auto data : lpSceneMng._saveList)
	{
		if ((*data).objID() == OBJ_ID::NON)
		{
			(*data).End();
		}
	}
	//std::copy(_objList.begin(), _objList.end(), std::back_inserter(lpSceneMng._saveList));

	for (auto list : lpSceneMng._saveList)
	{
		FILE* file;
		fopen_s(&file, "data/map.data", "wb");
		if (file != nullptr)
		{
			fwrite(
				(&list), // �v�f���߲������擾���Ă����n�� 
				sizeof(lpSceneMng._saveList[0]),
				lpSceneMng._saveList.size(),
				file
			);
			fclose(file);
		}
	}
	
	//File();

	auto itr = std::remove_if(
		lpSceneMng._saveList.begin(),	// �����͈͂̊J�n
		lpSceneMng._saveList.end(),		// �����͈͂̏I��
		[](sharedObj& obj) {return(*obj).isDead(); } 	// ����ł������O �����͐^�U��K���Ԃ�(�v���f�B�P�[�g)
	);
	// itr ���������v�f�̐擪�A�h���X
	lpSceneMng._saveList.erase(itr, lpSceneMng._saveList.end());
}

void MakeScene::RunMakeQue(std::vector<MakeQueT> makeList)
{
	for (auto makeQue : makeList)
	{
		switch (makeQue.first)
		{
		case OBJ_ID::BLOCK:
			lpSceneMng._saveList.emplace_back(new block({ makeQue.second.pos().x,makeQue.second.pos().y }, { 50,50 }));
			break;
		case OBJ_ID::PLAYER:
			lpSceneMng._saveList.emplace_back(new player({ makeQue.second.pos().x,makeQue.second.pos().y }, { 34,50 }));
			break;
		case OBJ_ID::DRUM:
			lpSceneMng._saveList.emplace_back(new drum({ makeQue.second.pos().x,makeQue.second.pos().y }, { 38,50 }));
			break;
		case OBJ_ID::GATE:
			lpSceneMng._saveList.emplace_back(new gate({ makeQue.second.pos().x,makeQue.second.pos().y - 15.0}, { 48,80 }));
			break;
		case OBJ_ID::BUTTON:
			lpSceneMng._saveList.emplace_back(new button({ makeQue.second.pos().x,makeQue.second.pos().y }, { 14,50 }));
			break;
		case OBJ_ID::SAW:
			lpSceneMng._saveList.emplace_back(new saw({ makeQue.second.pos().x,makeQue.second.pos().y }, { 50,50 }));
			break;
		case OBJ_ID::TREE:
			lpSceneMng._saveList.emplace_back(new tree({ makeQue.second.pos().x,makeQue.second.pos().y - 25.0 }, { 50,300 }));
			break;
		default:
			break;
		}
	}
}

void MakeScene::RunDeleteQue(std::vector<DeleteQueT> deleteList)
{
	for (auto deleteQue : deleteList)
	{
		if (deleteQue.second.unitID() == UNIT_ID::CURSOR)
		{
			for (auto data : lpSceneMng._saveList)
			{
				if ((*data).objID() != OBJ_ID::NON)
				{
					if ((*data).objID() == OBJ_ID::GATE)
					{
						if (deleteQue.second.pos().x == (*data).pos().x &&
							deleteQue.second.pos().y - 15.0 == (*data).pos().y)
						{
							(*data).End();
						}
					}
					else if ((*data).objID() == OBJ_ID::TREE)
					{
						if (deleteQue.second.pos().x == (*data).pos().x &&
							deleteQue.second.pos().y - 25.0 == (*data).pos().y)
						{
							(*data).End();
						}
					}
					else if (deleteQue.second.pos() == (*data).pos())
					{
						(*data).End();	// ����������޼ު��
					}
				}
			}
		}
	}
}

void MakeScene::draw(void)
{
	lpSceneMng.AddDrawQue({ IMAGE_ID("white")[0],lpSceneMng.ScreenCenter.x,lpSceneMng.ScreenCenter.y,0,false });

	for (int y = 0; y < 600; y += 50)
	{
		for (int x = 0; x < 1000; x += 50)
		{
			lpSceneMng.AddDrawQue({ IMAGE_ID("�c")[0],x,lpSceneMng.ScreenCenter.y - 75.0,0,false });
		}
		lpSceneMng.AddDrawQue({ IMAGE_ID("��")[0],lpSceneMng.ScreenCenter.x,y,0,false });
	}
	lpSceneMng.AddDrawQue({ IMAGE_ID("�c")[0],lpSceneMng.ScreenSize.x - 1,lpSceneMng.ScreenCenter.y,0,false });
	lpSceneMng.AddDrawQue({ IMAGE_ID("��")[0],lpSceneMng.ScreenCenter.x,lpSceneMng.ScreenSize.y - 1,0,false });

	lpSceneMng.AddDrawQue({ IMAGE_ID("��ۯ�")[0],100.0,675.0,0,false });
	lpSceneMng.AddDrawQue({ IMAGE_ID("����")[0],150.0,675.0,0,false });
}

void MakeScene::File(void)
{
	FILE* file;
	fopen_s(&file, "data/map.data", "wb");
	if (file != nullptr)
	{
		fwrite(
			lpSceneMng._saveList.data(), // �v�f���߲������擾���Ă����n�� 
			sizeof(lpSceneMng._saveList[0]),
			lpSceneMng._saveList.size(),
			file
		);
		fclose(file);
	}
}

