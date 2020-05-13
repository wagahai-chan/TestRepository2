#include <DxLib.h>
#include "KeyState.h"
#include "InputState.h"
#include <_debug\_DebugConOut.h>



KeyState::KeyState()
{
	_KeyConDef.reserve(static_cast<size_t>(end(INPUT_ID()))); // メモリの再配置を避けるため、あらかじめ必要分確保するreserveを使用する
	_KeyConDef.emplace_back(PAD_INPUT_LEFT);
	_KeyConDef.emplace_back(PAD_INPUT_RIGHT);
	_KeyConDef.emplace_back(PAD_INPUT_UP);
	_KeyConDef.emplace_back(PAD_INPUT_DOWN);
	_KeyConDef.emplace_back(PAD_INPUT_1);
	_KeyConDef.emplace_back(PAD_INPUT_4);
	_KeyConDef.emplace_back(PAD_INPUT_2);
	_KeyConDef.emplace_back(PAD_INPUT_3);

	FILE *file;
	fopen_s(&file, "data/key.data", "rb");
	if (file == nullptr)
	{
		_KeyCon = _KeyConDef; // 中身のｺﾋﾟｰ
	}
	else
	{
		//_keyConには値が入っていないから要素(INPUT_ID分)のサイズを確保しないといけない
		_KeyCon.resize(static_cast<int>(end(INPUT_ID())));
		fread(
			_KeyCon.data(),
			sizeof(_KeyCon[0]),
			_KeyCon.size(),
			file);
		fclose(file);
	}

	modeKeyOld = 1;	// F1のｵｰﾙﾄﾞｷｰ
}


KeyState::~KeyState()
{
}

void KeyState::Update(void)
{
	SetOld();
	modeKeyOld = _buf[KEY_INPUT_F1];
	//GetHitKeyStateAll(_buf); // _bufはすべてのﾎﾞﾀﾝの押下状態をとる
	//GetJoypadInputState(_buf);
	RefKeyData();
	/*(this->*func)();*/ // 自分自身のﾎﾟｲﾝﾀｰはthis
}

void KeyState::RefKeyData(void)
{
	// _bufに入っている inputIDのｷｰ(enumclass)の情報をstateのsetを使っていれる _buf　inputID分の情報をsetを使って　範囲for文を使う　_keyconを使ってsetする　f1キーを押したらfuncの内容をsetConFigに変える　f1keyを押した瞬間refKeyDataの呼び出しにもどす　トレースで切り替わったら変わったことを表示する
	for (auto id : INPUT_ID())
	{
		state(id, GetJoypadInputState(DX_INPUT_PAD1) & _KeyCon[static_cast<int>(id)]);	// <size_t>でも可
	}
}

