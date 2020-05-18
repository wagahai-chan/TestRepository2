#include <DxLib.h>
#include "FuncCheckHit.h"
#include <Obj.h>
#include <Scene/GameScene.h>


bool FuncCheckHit::operator()(ActQueT & actQue, void * scene)
{
	UNIT_ID unitID = (actQue.second.unitID() == UNIT_ID::PLAYER ? UNIT_ID::PLAYER : UNIT_ID::CRIMP);

	// ﾌﾞﾛｯｸの当たり判定
	if (actQue.second.actID() == ACT_ID::FALL)
	{
		for (auto data : ((GameScene*)scene)->_objList)
		{
			if ((*data).unitID() != unitID && (*data).objID() == OBJ_ID::BLOCK)
			{
				if (
					actQue.second.pos().y + actQue.second.size().y / 2.0 == (*data).pos().y - (*data).size().y / 2.0 &&
					actQue.second.pos().x + actQue.second.size().x / 2.0 >= (*data).pos().x - (*data).size().x / 2.0 &&	// ﾌﾟﾚｲﾔｰの右側とﾌﾞﾛｯｸの左側
					actQue.second.pos().x - actQue.second.size().x / 2.0 <= (*data).pos().x + (*data).size().x / 2.0)	// ﾌﾟﾚｲﾔｰの左側とﾌﾞﾛｯｸの右側
				{
					actQue.second.SetAct(ACT_ID::STOP);
					
				}
				if (actQue.second.pos().x + actQue.second.size().x / 2.0 == (*data).pos().x - (*data).size().x / 2.0 ||
					actQue.second.pos().x - actQue.second.size().x / 2.0 == (*data).pos().x + (*data).size().x / 2.0)
				{
					actQue.second.SetMove(false);
				}
			}	
		}
	}

	// 鋸の当たり判定
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

	// ｽｲｯﾁの当たり判定
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

	// ｺﾞｰﾙ判定
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

	// はみ出し判定
	if (actQue.second.actID() == ACT_ID::STOP)
	{
		for (auto data : ((GameScene*)scene)->_objList)
		{
			if ((*data).unitID() != unitID)
			{
				if (actQue.second.pos().y + actQue.second.size().y / 2.0 == (*data).pos().y - (*data).size().y / 2.0 &&
					actQue.second.pos().x + actQue.second.size().x / 2.0 >= (*data).pos().x - (*data).size().x / 2.0 &&	// ﾌﾟﾚｲﾔｰの右側とﾌﾞﾛｯｸの左側
					actQue.second.pos().x - actQue.second.size().x / 2.0 <= (*data).pos().x + (*data).size().x / 2.0)	// ﾌﾟﾚｲﾔｰの左側とﾌﾞﾛｯｸの右側
				{
					checkFlag = true;
				}
			}
		}

		if (checkFlag == true)
		{
			return true;
		}
		else if (checkFlag == false)
		{
			actQue.second.SetAct(ACT_ID::FALL);
		}
	}

	
	

	return false;
}

void FuncCheckHit::BLOCK(void)
{
}

void FuncCheckHit::SAW(void)
{
}
