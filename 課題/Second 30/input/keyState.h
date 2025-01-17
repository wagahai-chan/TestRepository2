#pragma once
#include <vector>
#include "InputState.h"

class KeyState :
	public InputState
{
public:
	KeyState();
	~KeyState();
	void Update(void) override;
private:
	void RefKeyData(void);		// 現在のｷｰﾃﾞｰﾀ書き込み
	void SetKeyConfig(void);	// ｷｰ情報の書き換え
	void (KeyState::*func)(void); // 関数ﾎﾟｲﾝﾀ

	char _buf[256];
	std::vector<int>  _KeyCon;
	std::vector<int>  _KeyConDef;

	INPUT_ID _confID;
	int modeKeyOld;

};
