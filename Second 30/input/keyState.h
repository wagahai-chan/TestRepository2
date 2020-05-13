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
	void RefKeyData(void);		// ���̷݂��ް���������
	//void SetKeyConfig(void);	// �����̏�������
	void (KeyState::*func)(void); // �֐��߲��

	int _buf[13];
	std::vector<int>  _KeyCon;
	std::vector<int>  _KeyConDef;

	INPUT_ID _confID;
	int modeKeyOld;

};
