#pragma once
#include <memory>
#include <tuple> 
#include <_debug/_DebugConOut.h>
#include <common\Vector2.h>
#include <Scene\BaseScene.h>
#include <Scene/TitleScene.h>
#include <common\ImageMng.h>
#include "LAYER_ID.h"
#include <vector>
#include <map>

enum class DRAW_QUE // enum�͌^���B�� class�������class�������O��Ԃ�����X�Ƃ������O�������ł��Ⴄ���̂ɂȂ� 
{
	IMAGE,
	X,
	Y,
	RATE,
	RAD,
	ZORDER,		// ڲ԰���̕`�揇(���l���̒Ⴂ�ق�����)
	LAYER,		// ID�̏������ق������ɕ`��
	DRAW_MODE,	// �`�惂�[�h
	DRAW_NUM	// �`�惂�[�h�ɓn���l
};

#define lpSceneMng SceneMng::GetInstance()

using DrawQueT = std::tuple<int, double, double,double, double,LAYER,bool>;
						//  id    x        y    �g�嗦   rad   ����

class SceneMng
{
public:
	static SceneMng &GetInstance(void)
	{
		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new SceneMng();
		}
	}

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr; // ��ذĂ��Ă��Ђ��̂��邩��null�������
	}

	void Run(void);
	bool AddDrawQue(DrawQueT dQue);
	bool AddActQue(ActQueT aQue);
	bool AddMakeQue(MakeQueT mQue);
	bool AddDeleteQue(DeleteQueT dQue);

	const Vector2 ScreenSize;
	const Vector2 ScreenCenter;			// ��ذ݂̒��S

	double PX;		// ��ڲ԰�Ɖ�ʒ����Ƃ̍���
	double Pos[3];
	bool check[static_cast<int>(UNIT_ID::MAX)][4];		// �ǂꂩ��ł��������Ă����true�ɂ��ē������~�߂�
	
	bool makeFlag = false;	// true:MakeScene  false:GameScene

	std::vector<sharedObj> _saveList;

private:
	static SceneMng* sInstance;

	unique_Base _activeScene;

	void Draw(void);

	std::vector<DrawQueT> _drawList;
	std::vector<ActQueT>  _actList;
	std::vector<MakeQueT> _makeList;
	std::vector<DeleteQueT> _deleteList;

	~SceneMng();
	SceneMng();
	bool SysInit(void);
};
