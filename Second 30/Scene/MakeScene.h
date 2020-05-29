#pragma once
#include <Scene\BaseScene.h>
#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <common\ImageMng.h>
#include <cursor.h>
#include <Scene\SceneMng.h>
#include <player.h>
#include <Crimp/block.h>
#include <Crimp/saw.h>
#include<Crimp/gate.h>
#include <Crimp/button.h>
#include <Crimp/drum.h>
#include <Crimp/tree.h>

class MakeScene :
	public BaseScene
{
public:
	MakeScene();
	~MakeScene();
	unique_Base Update(unique_Base own);
	void Move(void);
private:
	//std::vector<sharedObj> _objList;
	void RunMakeQue(std::vector<MakeQueT> makeList)  override;
	void RunDeleteQue(std::vector<DeleteQueT> deleteList) override;
	void draw(void);	
	void File(void);
	char moji;
};

