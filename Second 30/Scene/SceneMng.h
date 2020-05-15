#pragma once
#include <memory>
#include <tuple> 
#include <common\Vector2.h>
#include <Scene\BaseScene.h>
#include <Scene/TitleScene.h>
#include <common\ImageMng.h>
#include <vector>
#include <map>

enum class DRAW_QUE // enumは型が曖昧 classをつけるとclass名＝名前空間だからXという名前が同じでも違うものになる 
{
	IMAGE,
	X,
	Y,
	RAD,
	ZORDER,		// ﾚｲﾔｰ内の描画順(数値内の低いほうが奥)
	LAYER,		// IDの小さいほうが奥に描画
	DRAW_MODE,	// 描画モード
	DRAW_NUM	// 描画モードに渡す値
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
		sInstance = nullptr; // ﾃﾞﾘｰﾄしてもｺﾞﾐがのこるからnullをいれる
	}

	void Run(void);
	bool AddDrawQue(DrawQueT dQue);
	bool AddActQue(ActQueT aQue);

	const Vector2 ScreenSize;
	const Vector2 ScreenCenter;			// ｽｸﾘｰﾝの中心

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
