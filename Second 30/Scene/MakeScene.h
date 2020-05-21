#pragma once
#include <Scene\BaseScene.h>
#include <common\ImageMng.h>
#include <cursor.h>
#include <Scene\SceneMng.h>

class MakeScene :
	public BaseScene
{
public:
	MakeScene();
	~MakeScene();
	unique_Base Update(unique_Base own);
private:
	std::vector<sharedObj> _objList;
};

