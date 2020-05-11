#pragma once
#include <Scene\BaseScene.h>
#include <common\ImageMng.h>
#include <player.h>
#include <Scene\SceneMng.h>



class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base Update(unique_Base own);
private:
	std::vector<sharedObj> _objList;
};
