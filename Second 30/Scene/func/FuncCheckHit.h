#pragma once
#include <Scene/BaseScene.h>
#include <_debug/_DebugConOut.h>
#include <_debug/_DebugDispOut.h>


struct FuncCheckHit
{
	bool operator()(ActQueT& actQue, void* scene);
	bool checkFlag = false;		// МЮЫЇё‚М“–‚Ѕ‚и”»’иЃ@‚Н‚ЭЏo‚µ”»’и‚Й’К‚з‚И‚©‚Б‚ЅЏкЌ‡true
	int count = 0;				// Њ»ЌЭЋ©·¬Ч‚ЄЏж‚Б‚Д‚ў‚йМЮЫЇё‚Мђ”
};

