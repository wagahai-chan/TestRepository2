#pragma once
#include <vector>
#include <memory>
#include <map>
#include <common\Vector2.h>
#include <ACT_ID.h>
#include <OBJ_ID.h>
#include <Scene/LAYER_ID.h>

enum class STATE
{
	NORMAL,	// 通常
	RUN,
	JUMP,
	GOAL,
	ALIVE,
	DEATH,
	MAX
};

enum class CRIMP_ID
{
	NON,
	MOVEOBJECT,		// 自ｷｬﾗ
	CRIMP,		// 障害物
	MAX
};

enum class UNIT_ID
{
	CURSOR,
	PLAYER,
	DRUM,
	MAX
};



enum class MOVE_ID
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
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
	const CRIMP_ID& crimpID() const;
	const UNIT_ID& unitID() const;
	const ACT_ID& actID() const;
	const OBJ_ID& objID() const;
	const bool HitFlagRE() const;

	bool SetAnim(const STATE state, AnimVector& data);
	virtual void SetAlive(STATE stateID);
	virtual void SetAct(ACT_ID id);
	virtual void SetPos(Vector2Dbl pos);
	virtual bool SetMove(int i, bool move);
	STATE isAlive(void) { return _alive; }
	bool isDead(void) { return _dead; }
	bool isAnimEnd(void);	// ｱﾆﾒｰｼｮﾝが終了しているか
	bool HitFlag(bool flag);		// ｵﾌﾞｼﾞｪｸﾄに当たったか
	bool End(void);

private:
	std::map<STATE, AnimVector> _animMap;
	STATE _state;
	unsigned int _animFrame;	// ｱﾆﾒｰｼｮﾝﾌﾚｰﾑ　何ｺﾏ目か
	unsigned int _animCount;	// ｱﾆﾒｰｼｮﾝｶｳﾝﾄ　何回ﾙｰﾌﾟしたか

protected:
	bool DestroyProc(void);

	STATE _alive;		// 生きているか
	bool _dead;			// 死んでいるか
	bool hitFlag;		// 当たり判定
	bool _move[4];		// (0 上) (1 左) (2 右) (3 右)

	CRIMP_ID _crimpID;
	UNIT_ID _unitID;
	ACT_ID _actID;
	OBJ_ID _objID;

	Vector2Dbl _pos;
	Vector2Dbl _size;
	double _rate;
	double _rad;		// 角度
	LAYER _layer;
	bool _turn;			// 画像反転
};


