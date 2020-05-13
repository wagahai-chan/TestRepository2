#pragma once
#include <vector>
#include <memory>
#include <map>
#include <common\Vector2.h>
#include <ACT_ID.h>

enum class STATE
{
	NORMAL,	// �ʏ�
	GOAL,
	DEATH,
	MAX
};

enum class UNIT_ID
{
	NON,
	PLAYER,		// �����
	CRIMP,		// ��Q��
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
	bool isAnimEnd(void);	// ��Ұ��݂��I�����Ă��邩

private:
	std::map<STATE, AnimVector> _animMap;
	STATE _state;
	unsigned int _animFrame;	// ��Ұ����ڰс@���ϖڂ�
	unsigned int _animCount;	// ��Ұ��ݶ��ā@����ٰ�߂�����

protected:
	bool _alive;		// �����Ă��邩
	bool _dead;			// ����ł��邩

	UNIT_ID _unitID;
	Vector2Dbl _pos;
	Vector2Dbl _size;
	double _rad;		// �p�x
};


