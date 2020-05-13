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
	void RefKeyData(void);		// Œ»İ‚Ì·°ÃŞ°À‘‚«‚İ
	//void SetKeyConfig(void);	// ·°î•ñ‚Ì‘‚«Š·‚¦
	void (KeyState::*func)(void); // ŠÖ”Îß²İÀ

	int _buf[13];
	std::vector<int>  _KeyCon;
	std::vector<int>  _KeyConDef;

	INPUT_ID _confID;
	int modeKeyOld;

};
