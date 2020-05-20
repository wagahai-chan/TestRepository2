#include <DxLib.h>
#include "FuncCheckMove.h"
#include <Obj.h>
#include <Scene/GameScene.h>

bool FuncCheckMove::operator()(ActQueT & actQue, void * scene)
{
	CRIMP_ID crimpID = (actQue.second.crimpID() == CRIMP_ID::MOVEOBJECT ? CRIMP_ID::MOVEOBJECT : CRIMP_ID::CRIMP);

	// ½²¯Á‚Ì“–‚½‚è”»’è
	for (auto data : ((GameScene*)scene)->_objList)
	{
		if ((*data).objID() == OBJ_ID::BUTTON && actQue.second.unitID() == UNIT_ID::PLAYER)
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
		if ((*data).objID() == OBJ_ID::GATE && (*data).state() == STATE::GOAL && actQue.second.unitID() == UNIT_ID::PLAYER)
		{
			if (actQue.second.pos().x - 5.0 <= (*data).pos().x && actQue.second.pos().x + 5.0 >= (*data).pos().x &&
				actQue.second.pos().y >= (*data).pos().y - (*data).size().y / 2 && actQue.second.pos().y <= (*data).pos().y + (*data).size().y / 2)
			{
				actQue.second.SetAlive(STATE::GOAL);
			}
		}
	}

	// ÄÞ×ÑŠÊ‚Æ–Ø‚Ì”RÄ”»’è
	for (auto data : ((GameScene*)scene)->_objList)
	{
		if ((*data).objID() == OBJ_ID::TREE && actQue.second.unitID() == UNIT_ID::DRUM)
		{
			if (actQue.second.pos().x - actQue.second.size().x / 2.0 <= (*data).pos().x + (*data).size().x / 2.0 &&
				actQue.second.pos().x + actQue.second.size().x / 2.0 >= (*data).pos().x - (*data).size().x / 2.0 &&
				actQue.second.pos().y - actQue.second.size().y / 2.0 < (*data).pos().y + (*data).size().y / 2.0 &&
				actQue.second.pos().y + actQue.second.size().y / 2.0 > (*data).pos().y - (*data).size().y / 2.0)
			{
				(*data).SetAlive(STATE::DEATH);
				actQue.second.SetAlive(STATE::DEATH);
			}
		}
	}

	return false;
}
