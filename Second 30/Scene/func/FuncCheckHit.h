#pragma once
#include <Scene/BaseScene.h>
#include <_debug/_DebugConOut.h>
#include <_debug/_DebugDispOut.h>


struct FuncCheckHit
{
	bool operator()(ActQueT& actQue, void* scene);
	bool checkFlag = false;		// ﾌﾞﾛｯｸの当たり判定　はみ出し判定に通らなかった場合true
	int count = 0;				// 現在自ｷｬﾗが乗っているﾌﾞﾛｯｸの数
};

