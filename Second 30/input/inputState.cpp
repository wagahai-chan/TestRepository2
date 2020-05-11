#include <_debug\_DebugConOut.h>
#include "InputState.h"




InputState::InputState()
{
	for (auto id : INPUT_ID()) // enum class ��bigin�֐���end�֐����Ȃ����߁A���̏�ō��@��������Δ͈�for��������
	{
		_state.try_emplace(INPUT_ID::A, KeyPair{ 0,1 }); // try_emplace ���̏���ް������
	}
}


InputState::~InputState()
{
}

const KeyMap & InputState::state(void) const
{
	return _state;
}

const KeyPair & InputState::state(INPUT_ID id) const // �������݂Ɋւ��邱�Ƃ��ł��Ȃ��@_state�̌^��map�ō���Ă���@id�ɊY������L�[��map�̒��ɂȂ��Ƃ��V����make���Ă��܂��B���̍s�ׂ�const�Ɉ���������@������find���g��
{
	static KeyPair defData = { 0,0 }; // &�ŎQ�Ƃ��Ă��邩��static�̓������g���@�ŏ����炱�̃f�[�^�͑��݂��邩����S
	try
	{
		return _state.at(id); // �Ȃ���i��O�j�������u�ԗ�����ꂽ�獢��
	}
	catch (...) // �S�װ
	{
		AST();
		return defData;
	}
}

bool InputState::state(INPUT_ID id, int data)
{
	if (_state.find(id) != _state.end())
	{
		_state[id].first = data;
		return true;
	}

	return false;
}

void InputState::SetOld(void)
{
	for (auto id : INPUT_ID())
	{
		try
		{
			_state[id].second = _state[id].first;
		}
		catch (...)
		{
			AST();
			_state.emplace(id, KeyPair{ 0,1 }); // emplace���g��
		}
	}
}
