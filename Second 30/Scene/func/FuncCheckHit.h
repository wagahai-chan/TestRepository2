#pragma once
#include <Scene/BaseScene.h>
#include <_debug/_DebugConOut.h>
#include <_debug/_DebugDispOut.h>


struct FuncCheckHit
{
	bool operator()(ActQueT& actQue, void* scene);
	bool checkFlag = false;		// ��ۯ��̓����蔻��@�͂ݏo������ɒʂ�Ȃ������ꍇtrue
	int count = 0;				// ���ݎ���ׂ�����Ă�����ۯ��̐�
};

