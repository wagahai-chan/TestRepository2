#include <DxLib.h>
#include "FuncCheckHit.h"
#include <Obj.h>
#include <Scene/GameScene.h>


bool FuncCheckHit::operator()(ActQueT & actQue, void * scene)
{
	UNIT_ID unitID = (actQue.second.unitID() == UNIT_ID::PLAYER ? UNIT_ID::PLAYER : UNIT_ID::CRIMP);

	// ��ۯ��̓����蔻��
	if (actQue.second.actID() == ACT_ID::FALL)
	{
		for (auto data : ((GameScene*)scene)->_objList)
		{
			if ((*data).unitID() != unitID && (*data).objID() == OBJ_ID::BLOCK)
			{
				if (
					actQue.second.pos().y + actQue.second.size().y / 2.0 == (*data).pos().y - (*data).size().y / 2.0 &&
					actQue.second.pos().x + actQue.second.size().x / 2.0 >= (*data).pos().x - (*data).size().x / 2.0 &&	// ��ڲ԰�̉E������ۯ��̍���
					actQue.second.pos().x - actQue.second.size().x / 2.0 <= (*data).pos().x + (*data).size().x / 2.0)	// ��ڲ԰�̍�������ۯ��̉E��
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
	//			actQue.second.pos().x + actQue.second.size().x / 2.0 >= (*data).pos().x - (*data).size().x / 2.0 &&	// ��ڲ԰�̉E������ۯ��̍���
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

	// �͂ݏo������
	if (actQue.second.actID() == ACT_ID::STOP)
	{
		for (auto data : ((GameScene*)scene)->_objList)
		{
			if ((*data).unitID() != unitID)
			{
				if (actQue.second.pos().y + actQue.second.size().y / 2.0 == (*data).pos().y - (*data).size().y / 2.0 &&
					actQue.second.pos().x + actQue.second.size().x / 2.0 >= (*data).pos().x - (*data).size().x / 2.0 &&	// ��ڲ԰�̉E������ۯ��̍���
					actQue.second.pos().x - actQue.second.size().x / 2.0 <= (*data).pos().x + (*data).size().x / 2.0)	// ��ڲ԰�̍�������ۯ��̉E��
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