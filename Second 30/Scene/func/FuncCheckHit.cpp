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
			}	
		}
	}

	//for (auto data : ((GameScene*)scene)->_objList)
	//{
	//	if ((*data).unitID() != unitID && (*data).objID() == OBJ_ID::BLOCK)
	//	{
	//		if (actQue.second.pos().y + actQue.second.size().y / 2.0 == (*data).pos().y - (*data).size().y / 2.0 &&
	//			actQue.second.pos().x + actQue.second.size().x / 2.0 >= (*data).pos().x - (*data).size().x / 2.0 &&	// ﾌﾟﾚｲﾔｰの右側とﾌﾞﾛｯｸの左側
	//			actQue.second.pos().x - actQue.second.size().x / 2.0 <= (*data).pos().x + (*data).size().x / 2.0)
	//		{
	//			actQue.second.SetMove(1, true);
	//		}
	//		else if (actQue.second.pos().y + actQue.second.size().y / 2.0 != (*data).pos().y - (*data).size().y / 2.0&&
	//			     actQue.second.pos().x + actQue.second.size().x / 2.0 >= (*data).pos().x - (*data).size().x / 2.0 &&
	//			     actQue.second.pos().x - actQue.second.size().x / 2.0 <= (*data).pos().x + (*data).size().x / 2.0)
	//		{
	//			actQue.second.SetMove(1, false);
	//		}
	//	}
	//}

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

	for (auto data : ((GameScene*)scene)->_objList)
	{
		if ((*data).unitID() != unitID && (*data).objID() == OBJ_ID::TREE)
		{

		}
	}

	
	

	return false;
}