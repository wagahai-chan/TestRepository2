#include <DxLib.h>
#include "FuncCheckMove.h"
#include <Obj.h>
#include <Scene/GameScene.h>

bool FuncCheckMove::operator()(ActQueT & actQue, void * scene)
{
	UNIT_ID unitID = (actQue.second.unitID() == UNIT_ID::PLAYER ? UNIT_ID::PLAYER : UNIT_ID::CRIMP);

	// ½²¯Á‚Ì“–‚½‚è”»’è
	for (auto data : ((GameScene*)scene)->_objList)
	{
		if ((*data).objID() == OBJ_ID::BUTTON)
		{
			if (actQue.second.pos().x - 5.0 <= (*data).pos().x && actQue.second.pos().x + 5.0 >= (*data).pos().x &&
				actQue.second.pos().y >= (*data).pos().y - (*data).size().y / 2 && actQue.second.pos().y <= (*data).pos().y + (*data).size().y / 2)
			{
				(*data).SetAlive(STATE::GOAL);

				for (auto data : ((GameScene*)scene)->_objList)
				{
					if ((*data).objID() == OBJ_ID::GATE)
					{
						(*data).SetAlive(STATE::GOAL);
					}
				}
			}
		}
	}

	// ºÞ°Ù”»’è
	for (auto data : ((GameScene*)scene)->_objList)
	{
		if ((*data).objID() == OBJ_ID::GATE && (*data).state() == STATE::GOAL)
		{
			if (actQue.second.pos().x - 5.0 <= (*data).pos().x && actQue.second.pos().x + 5.0 >= (*data).pos().x &&
				actQue.second.pos().y >= (*data).pos().y - (*data).size().y / 2 && actQue.second.pos().y <= (*data).pos().y + (*data).size().y / 2)
			{
				actQue.second.SetAlive(STATE::GOAL);
			}
		}
	}

	return false;
}
