#pragma once
#include <Scene\BaseScene.h>
#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <common\ImageMng.h>
#include <player.h>
#include <Crimp/block.h>
#include <Crimp/saw.h>
#include<Crimp/gate.h>
#include <Crimp/button.h>
#include <Crimp/drum.h>
#include <Crimp/tree.h>
#include <Scene\SceneMng.h>
#include <Scene/GoalScene.h>

struct FuncCheckHit;
struct FuncCheckDeath;
struct FuncCheckMove;

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base Update(unique_Base own);
private:
	friend FuncCheckHit;
	friend FuncCheckDeath;
	friend FuncCheckMove;
	std::vector<sharedObj> _objList;
	void RunActQue(std::vector<ActQueT> actList)  override;

	int cnt = 1861;
};
