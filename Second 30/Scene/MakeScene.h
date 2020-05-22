#pragma once
#include <Scene\BaseScene.h>
#include <common\ImageMng.h>
#include <cursor.h>
#include <Scene\SceneMng.h>
#include <Crimp/block.h>
#include <Crimp/drum.h>

class MakeScene :
	public BaseScene
{
public:
	MakeScene();
	~MakeScene();
	unique_Base Update(unique_Base own);
	void list(int id);
private:
	std::vector<sharedObj> _objList;
	void RunMakeQue(std::vector<MakeQueT> makeList)  override;
	void RunDeleteQue(std::vector<DeleteQueT> deleteList) override;
	void draw(void);	
};

