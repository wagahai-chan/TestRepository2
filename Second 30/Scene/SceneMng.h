#pragma once
#include <memory>
#include <tuple> 
#include <common\Vector2.h>
#include <Scene\BaseScene.h>
#include <Scene/TitleScene.h>
#include <common\ImageMng.h>
#include <vector>
#include <map>

enum class DRAW_QUE // enum�͌^���B�� class�������class�������O��Ԃ�����X�Ƃ������O�������ł��Ⴄ���̂ɂȂ� 
{
	IMAGE,
	X,
	Y,
	RAD,
	ZORDER,		// ڲ԰���̕`�揇(���l���̒Ⴂ�ق�����)
	LAYER,		// ID�̏������ق������ɕ`��
	DRAW_MODE,	// �`�惂�[�h
	DRAW_NUM	// �`�惂�[�h�ɓn���l
};

#define lpSceneMng SceneMng::GetInstance()

using DrawQueT = std::tuple<int, double, double, double>;
						//  id    x        y     rad

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

	const Vector2 ScreenSize;
	const Vector2 ScreenCenter;			// ��ذ݂̒��S

	int pulas = 0.0;

private:
	static SceneMng* sInstance;

	unique_Base _activeScene;

	void Draw(void);

	std::vector<DrawQueT> _drawList;
	std::vector<ActQueT> _actList;

	~SceneMng();
	SceneMng();
	bool SysInit(void);
};
