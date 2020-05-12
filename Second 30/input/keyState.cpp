#include <DxLib.h>
#include "KeyState.h"
#include "InputState.h"
#include <_debug\_DebugConOut.h>



KeyState::KeyState()
{
	_KeyConDef.reserve(static_cast<size_t>(end(INPUT_ID()))); // �������̍Ĕz�u������邽�߁A���炩���ߕK�v���m�ۂ���reserve���g�p����
	_KeyConDef.emplace_back(KEY_INPUT_A);
	_KeyConDef.emplace_back(KEY_INPUT_D);
	_KeyConDef.emplace_back(KEY_INPUT_W);
	_KeyConDef.emplace_back(KEY_INPUT_S);
	_KeyConDef.emplace_back(KEY_INPUT_LEFT);
	_KeyConDef.emplace_back(KEY_INPUT_RIGHT);
	_KeyConDef.emplace_back(KEY_INPUT_UP);
	_KeyConDef.emplace_back(KEY_INPUT_DOWN);

	FILE *file;
	fopen_s(&file, "data/key.data", "rb");
	if (file == nullptr)
	{
		_KeyCon = _KeyConDef; // ���g�̺�߰
	}
	else
	{
		//_keyCon�ɂ͒l�������Ă��Ȃ�����v�f(INPUT_ID��)�̃T�C�Y���m�ۂ��Ȃ��Ƃ����Ȃ�
		_KeyCon.resize(static_cast<int>(end(INPUT_ID())));
		fread(
			_KeyCon.data(),
			sizeof(_KeyCon[0]),
			_KeyCon.size(),
			file);
		fclose(file);
	}

	modeKeyOld = 1;	// F1�̵���޷�
}


KeyState::~KeyState()
{
}

void KeyState::Update(void)
{
	SetOld();
	modeKeyOld = _buf[KEY_INPUT_F1];
	GetHitKeyStateAll(_buf); // _buf�͂��ׂĂ����݂̉�����Ԃ��Ƃ�
	RefKeyData();
	/*(this->*func)();*/ // �������g���߲�����this
}

void KeyState::RefKeyData(void)
{
	// _buf�ɓ����Ă��� inputID�̷�(enumclass)�̏���state��set���g���Ă���� _buf�@inputID���̏���set���g���ā@�͈�for�����g���@_keycon���g����set����@f1�L�[����������func�̓��e��setConFig�ɕς���@f1key���������u��refKeyData�̌Ăяo���ɂ��ǂ��@�g���[�X�Ő؂�ւ������ς�������Ƃ�\������
	for (auto id : INPUT_ID())
	{
		state(id, _buf[_KeyCon[static_cast<int>(id)]]);	// <size_t>�ł���
	}
}

