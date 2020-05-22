#include <algorithm>
#include <DxLib.h>
#include "MakeScene.h"



MakeScene::MakeScene()
{
	lpSceneMng.makeFlag = true;

	lpImageMng.GetID("ｶｰｿﾙ", "image/cursor.png", { 30,30 }, { 1,1 });
	

	_objList.emplace_back(new cursor({ 200.0,300.0 }, { 30,30 }));
}


MakeScene::~MakeScene()
{
}

unique_Base MakeScene::Update(unique_Base own)
{
	draw();

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

void MakeScene::RunMakeQue(std::vector<MakeQueT> makeList)
{
	for (auto makeQue : makeList)
	{
		switch (makeQue.first)
		{
		case OBJ_ID::BLOCK:
			_objList.emplace_back(new block({ makeQue.second.pos().x,makeQue.second.pos().y }, { 50,50 }));
			break;
		case OBJ_ID::DRUM:
			_objList.emplace_back(new drum({ makeQue.second.pos().x,makeQue.second.pos().y }, { 38,50 }));
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
			for (auto data : _objList)
			{
				if ((*data).objID() != OBJ_ID::NON)
				{
					if (deleteQue.second.pos() == (*data).pos())
					{
						(*data).End();
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
			lpSceneMng.AddDrawQue({ IMAGE_ID("縦")[0],x,lpSceneMng.ScreenCenter.y - 75.0,0,false });
		}
		lpSceneMng.AddDrawQue({ IMAGE_ID("横")[0],lpSceneMng.ScreenCenter.x,y,0,false });
	}
	lpSceneMng.AddDrawQue({ IMAGE_ID("縦")[0],lpSceneMng.ScreenSize.x - 1,lpSceneMng.ScreenCenter.y,0,false });
	lpSceneMng.AddDrawQue({ IMAGE_ID("横")[0],lpSceneMng.ScreenCenter.x,lpSceneMng.ScreenSize.y - 1,0,false });

	lpSceneMng.AddDrawQue({ IMAGE_ID("ﾌﾞﾛｯｸ")[0],100.0,675.0,0,false });
	lpSceneMng.AddDrawQue({ IMAGE_ID("ﾄﾞﾗﾑ")[0],150.0,675.0,0,false });
}

void MakeScene::list(int id)
{
}
