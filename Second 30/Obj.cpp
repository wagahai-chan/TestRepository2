#include <DxLib.h>
#include "Obj.h"
#include <Scene\SceneMng.h>


Obj::Obj()
{
	_alive = true;
	_dead = false;
	hitFlag = false;
	_animFrame = 0;
	_animCount = 0;
	_rad = 0;
	_unitID = UNIT_ID::NON;
}

void Obj::Draw(void)
{
	if (_animMap.find(_state) == _animMap.end()) // 見つかったらｲﾃﾚｰﾀを返す　endまで来るということは、そのﾃﾞｰﾀが存在しないということ
	{
		return;
	}
	if (_animFrame < 0 || _animFrame >= _animMap[_state].size()) // 要素数を調べるとき、取得する時はsizeを使う
	{
		return;
	}

	// _animMap[_animKey].size() コマ数

	if (_animMap[_state][_animFrame].first >= 0)
	{
		if (_animCount >= _animMap[_state][_animFrame].second)
		{
			_animFrame++;
		}

		_animCount++;

		if (_animFrame >= _animMap[_state].size())
		{
			_animFrame = 0;
			_animCount = 0;
		}

		lpSceneMng.AddDrawQue({ _animMap[_state][_animFrame].first,_pos.x,_pos.y,0.0 });
	}
}

void Obj::Draw(int id)
{
	lpSceneMng.AddDrawQue({ id,_pos.x,_pos.y,_rad });
}

Obj::~Obj()
{
}

bool Obj::state(const STATE state)
{
	if (_animMap.find(state) == _animMap.end())
	{
		return false;
	}

	if (_state != state)
	{
		_animFrame = 0;
		_animCount = 0;
	}

	_state = state;
	return true;
}

const STATE Obj::state(void) const
{
	return _state;
}

const Vector2Dbl & Obj::pos(void) const
{
	return _pos;
}

const Vector2Dbl & Obj::size(void) const
{
	return _size;
}

const UNIT_ID & Obj::unitID() const
{
	return _unitID;
}

const ACT_ID & Obj::actID() const
{
	return _actID;
}

const OBJ_ID & Obj::objID() const
{
	return _objID;
}

const bool Obj::HitFlagRE() const
{
	return hitFlag;
}

bool Obj::SetAnim(const STATE state, AnimVector & data)
{
	return (_animMap.try_emplace(state, std::move(data))).second; // first iteratorが返る second bool値が返る　17以降しか使えない
					// emplace 新規にﾃﾞｰﾀを入力する tryしてほしいキー　トライした結果
}

bool Obj::SetAlive(bool alive)
{
	_alive = alive;
	if (!_alive)
	{
		state(STATE::GOAL);
	}
	else if (_alive)
	{
		state(STATE::DEATH);
	}
	else
	{
		// 無し
	}

	return true;
}

void Obj::SetAct(ACT_ID id)
{
	_actID = id;

	return;
}

bool Obj::isAnimEnd(void)
{
	// _animMap[_state][_animFrame].first >= 0
	if (_animMap.find(_state) == _animMap.end()) // 見つかったらｲﾃﾚｰﾀを返す　endまで来るということは、そのﾃﾞｰﾀが存在しないということ
	{
		return true;
	}
	if (_animFrame < 0 || _animFrame >= _animMap[_state].size()) // 要素数を調べるとき、取得する時はsizeを使う
	{
		return true;
	}


	if (_animMap[_state][_animFrame].first == -1)
	{
		return true;
	}
	else
	{
		return false;
	}

	return false;
}

bool Obj::HitFlag(bool flag)
{
	hitFlag = flag;

	return true;
}

bool Obj::DestroyProc(void)
{
	if (_alive)
	{
		return false;
	}
	if (isAnimEnd())
	{
		_dead = true;
	}

	return true;
}
