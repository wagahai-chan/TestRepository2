#include <DxLib.h>
#include "FuncCheckHit.h"
#include <Obj.h>
#include <Scene/GameScene.h>


bool FuncCheckHit::operator()(ActQueT & actQue, void * scene)
{
	CRIMP_ID crimpID = (actQue.second.crimpID() == CRIMP_ID::MOVEOBJECT ? CRIMP_ID::MOVEOBJECT : CRIMP_ID::CRIMP);
	UNIT_ID unitID = (actQue.second.unitID() == UNIT_ID::PLAYER ? UNIT_ID::PLAYER : UNIT_ID::DRUM);

	// �㉺���E�̃u���b�N�̓����蔻��
	for (auto data : ((GameScene*)scene)->_objList)
	{
		if (((*data).unitID() != unitID || (*data).crimpID() != crimpID) &&
			((*data).objID() == OBJ_ID::BLOCK || (*data).objID() == OBJ_ID::TREE || (*data).objID() == OBJ_ID::DRUM || (*data).objID() == OBJ_ID::PLAYER))
		{
			// ��ڲ԰���ړ�
			if (actQue.second.pos().y + actQue.second.size().y / 2.0 > (*data).pos().y - (*data).size().y / 2.0 &&
				actQue.second.pos().y - actQue.second.size().y / 2.0 < (*data).pos().y + (*data).size().y / 2.0 &&	
				actQue.second.pos().x - actQue.second.size().x / 2.0 == (*data).pos().x + (*data).size().x / 2.0)	
			{
				lpSceneMng.check[static_cast<int>(actQue.second.unitID())][static_cast<int>(MOVE_ID::LEFT)] = true;
			}

			// ��ڲ԰�E�ړ�
			if (actQue.second.pos().y + actQue.second.size().y / 2.0 > (*data).pos().y - (*data).size().y / 2.0 &&
				actQue.second.pos().y - actQue.second.size().y / 2.0 < (*data).pos().y + (*data).size().y / 2.0 &&
				actQue.second.pos().x + actQue.second.size().x / 2.0 == (*data).pos().x - (*data).size().x / 2.0)
			{
				lpSceneMng.check[static_cast<int>(actQue.second.unitID())][static_cast<int>(MOVE_ID::RIGHT)] = true;
			}

			// ��ڲ԰�ެ��ߎ�
			if (actQue.second.pos().y - actQue.second.size().y / 2.0 == (*data).pos().y + (*data).size().y / 2.0 &&
				actQue.second.pos().x - actQue.second.size().x / 2.0 < (*data).pos().x + (*data).size().x / 2.0 &&
				actQue.second.pos().x + actQue.second.size().x / 2.0 > (*data).pos().x - (*data).size().x / 2.0)
			{
				lpSceneMng.check[static_cast<int>(actQue.second.unitID())][static_cast<int>(MOVE_ID::UP)] = true;
			}

			// ������
			if (actQue.second.pos().y + actQue.second.size().y / 2.0 == (*data).pos().y - (*data).size().y / 2.0 &&
				actQue.second.pos().x + actQue.second.size().x / 2.0 > (*data).pos().x - (*data).size().x / 2.0 &&	// ��ڲ԰�̉E������ۯ��̍���
				actQue.second.pos().x - actQue.second.size().x / 2.0 < (*data).pos().x + (*data).size().x / 2.0)	// ��ڲ԰�̍�������ۯ��̉E��
			{
				lpSceneMng.check[static_cast<int>(actQue.second.unitID())][static_cast<int>(MOVE_ID::DOWN)] = true;
			}
			
		}
	}

	for (int j = 0; j < static_cast<int>(MOVE_ID::MAX); j++)
	{
		if (lpSceneMng.check[static_cast<int>(actQue.second.unitID())][j] == true)
		{
			actQue.second.SetMove(j, true);
		}
		else
		{
			actQue.second.SetMove(j, false);
		}
	}
	
	
	return false;
}