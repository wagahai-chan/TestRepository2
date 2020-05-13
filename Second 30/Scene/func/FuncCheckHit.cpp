#include "FuncCheckHit.h"
#include <Obj.h>
#include <Scene/GameScene.h>


bool FuncCheckHit::operator()(ActQueT & actQue, void * scene)
{
	UNIT_ID unitID = (actQue.second.unitID() == UNIT_ID::PLAYER ? UNIT_ID::PLAYER : UNIT_ID::CRIMP);

	for (auto data : ((GameScene*)scene)->_objList)
	{
		if ((*data).unitID() != unitID)
		{
			if (abs(actQue.second.pos().y - (*data).pos().y) <= actQue.second.size().y + (*data).size().y &&
				abs(actQue.second.pos().x - (*data).pos().x) <= actQue.second.size().x + (*data).size().x)
			{
				(*data).SetAlive(false);
				actQue.second.SetAlive(false);
			}
		}
	}

	return false;
}
