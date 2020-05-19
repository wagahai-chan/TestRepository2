#pragma once
#include <memory>
#include <Obj.h>

class BaseScene;		// ﾌﾟﾛﾄﾀｲﾌﾟ宣言

enum class ACT_QUE
{
	NON,
	CHECK_HIT,		// ﾌﾞﾛｯｸ等の動かないｵﾌﾞｼﾞｪｸﾄとの当たり判定
	CHECK_DEATH,	// 当たるとゲームオーバーになる判定
	CHECK_MOVE,		// 当たると何かしらの動きがある判定
	MAX
};

using unique_Base = std::unique_ptr<BaseScene>;
using ActQueT = std::pair<ACT_QUE, Obj&>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual unique_Base Update(unique_Base own) = 0;
	virtual void RunActQue(std::vector<ActQueT> actList);
};
