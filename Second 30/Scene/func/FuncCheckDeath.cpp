#include <DxLib.h>
#include "FuncCheckDeath.h"
#include <Obj.h>
#include <Scene/GameScene.h>


bool FuncCheckDeath::operator()(ActQueT & actQue, void * scene)
{
	UNIT_ID unitID = (actQue.second.unitID() == UNIT_ID::PLAYER ? UNIT_ID::PLAYER : UNIT_ID::CRIMP);

	// ‹˜‚Ì“–‚½‚è”»’è
	for (auto data : ((GameScene*)scene)->_objList)
	{
		if ((*data).objID() == OBJ_ID::SAW)
		{
			if (actQue.second.pos().x + actQue.second.size().x / 2.0 >= (*data).pos().x - (*data).size().x / 2.0 &&
				actQue.second.pos().x - actQue.second.size().x / 2.0 <= (*data).pos().x + (*data).size().x / 2.0 &&
				actQue.second.pos().y + actQue.second.size().y / 2.0 >= (*data).pos().y - (*data).size().y / 2.0 &&
				actQue.second.pos().y - actQue.second.size().y / 2.0 <= (*data).pos().y + (*data).size().y / 2.0
				)
			{
				actQue.second.SetAlive(STATE::DEATH);
			}
		}
	}

	return false;
}
