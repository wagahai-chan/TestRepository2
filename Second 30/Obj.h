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

enum class OBJ_ID	// 障害物ｵﾌﾞｼﾞｪｸﾄ
{
	BLOCK,		// ﾌﾞﾛｯｸ
	SAW,		// 鋸
	GATE,		// ｺﾞｰﾙの門
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
	const ACT_ID& actID() const;
	const OBJ_ID& objID() const;
	const bool HitFlagRE() const;

	bool SetAnim(const STATE state, AnimVector& data);
	virtual bool SetAlive(bool alive);
	virtual void SetAct(ACT_ID id);
	bool isAlive(void) { return _alive; }
	bool isDead(void) { return _dead; }
	bool isAnimEnd(void);	// ｱﾆﾒｰｼｮﾝが終了しているか
	bool HitFlag(bool flag);		// ｵﾌﾞｼﾞｪｸﾄに当たったか

private:
	std::map<STATE, AnimVector> _animMap;
	STATE _state;
	unsigned int _animFrame;	// ｱﾆﾒｰｼｮﾝﾌﾚｰﾑ　何ｺﾏ目か
	unsigned int _animCount;	// ｱﾆﾒｰｼｮﾝｶｳﾝﾄ　何回ﾙｰﾌﾟしたか

protected:
	bool DestroyProc(void);

	bool _alive;		// 生きているか
	bool _dead;			// 死んでいるか
	bool hitFlag;		// 当たり判定

	UNIT_ID _unitID;
	ACT_ID _actID;
	OBJ_ID _objID;

	Vector2Dbl _pos;
	Vector2Dbl _size;
	double _rad;		// 角度
};


