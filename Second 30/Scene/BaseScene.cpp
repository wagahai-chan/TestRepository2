#include "BaseScene.h"



BaseScene::BaseScene()
{
}


BaseScene::~BaseScene()
{
}

void BaseScene::RunActQue(std::vector<ActQueT> actList)
{
	actList.clear();
}

void BaseScene::RunMakeQue(std::vector<MakeQueT> makeList)
{
	makeList.clear();
}

void BaseScene::RunDeleteQue(std::vector<DeleteQueT> deleteList)
{
	deleteList.clear();
}
