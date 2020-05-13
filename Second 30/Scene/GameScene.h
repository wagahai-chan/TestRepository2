#pragma once
#include <Scene\BaseScene.h>
#include <common\ImageMng.h>
#include <player.h>
#include <Crimp/block.h>
#include <Scene\SceneMng.h>

struct FuncCheckHit;

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base Update(unique_Base own);
private:
	friend FuncCheckHit;
	std::vector<sharedObj> _objList;
	void RunActQue(std::vector<ActQueT> actList)  override;
};
