#pragma once
#include <vector>
#include <memory>
#include <map>
#include <common\Vector2.h>
#include <ACT_ID.h>

enum class STATE
{
	NORMAL,	// 通常
	GOAL,
	DEATH,
	MAX
};

enum class UNIT_ID
{
	NON,
	PLAYER,		// 自ｷｬﾗ
	CRIMP,		// 障害物
	MAX
};

class Obj;

using AnimVector = std::vector<std::pair<int, unsigned int>>;
using sharedObj = std::shared_ptr<Obj>;

class Obj
{
public:
	Obj();
	virtual void Update(void) = 0;
	void Draw(void);
	void Draw(int id);
	~Obj();

	bool state(const STATE state);
	const STATE state(void) const;

	const Vector2Dbl& pos(void) const;
	const Vector2Dbl& size(void) const;
	const UNIT_ID& unitID() const;

	bool SetAnim(const STATE state, AnimVector& data);
	virtual bool SetAlive(bool alive);
	bool isAlive(void) { return _alive; }
	bool isDead(void) { return _dead; }
	bool isAnimEnd(void);	// ｱﾆﾒｰｼｮﾝが終了しているか

private:
	std::map<STATE, AnimVector> _animMap;
	STATE _state;
	unsigned int _animFrame;	// ｱﾆﾒｰｼｮﾝﾌﾚｰﾑ　何ｺﾏ目か
	unsigned int _animCount;	// ｱﾆﾒｰｼｮﾝｶｳﾝﾄ　何回ﾙｰﾌﾟしたか

protected:
	bool _alive;		// 生きているか
	bool _dead;			// 死んでいるか

	UNIT_ID _unitID;
	Vector2Dbl _pos;
	Vector2Dbl _size;
	double _rad;		// 角度
};


