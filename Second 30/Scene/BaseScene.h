#pragma once
#include <memory>
#include <Obj.h>

class BaseScene;		// �������ߐ錾

enum class ACT_QUE
{
	NON,
	CHECK_HIT,		// ��ۯ����̓����Ȃ���޼ު�ĂƂ̓����蔻��
	CHECK_DEATH,	// ������ƃQ�[���I�[�o�[�ɂȂ锻��
	CHECK_MOVE,		// ������Ɖ�������̓��������锻��
	MAX
};

enum class MAKE_QUE
{
	NON,
	CHECK_HIT,
};

using unique_Base = std::unique_ptr<BaseScene>;
using ActQueT = std::pair<ACT_QUE, Obj&>;
using MakeQueT = std::pair<OBJ_ID, Obj&>;
using DeleteQueT = std::pair<OBJ_ID,Obj&>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual unique_Base Update(unique_Base own) = 0;
	virtual void RunActQue(std::vector<ActQueT> actList);
	virtual void RunMakeQue(std::vector<MakeQueT> makeList);
	virtual void RunDeleteQue(std::vector<DeleteQueT> deleteList);
};
