#include <DxLib.h>
#include "SceneMng.h"
#include <Scene/GameScene.h>


SceneMng*  SceneMng::sInstance = nullptr;

SceneMng::SceneMng() :ScreenSize{ 800,600 } // ｺﾝｽﾄﾗｸﾀが走った瞬間、ﾛｯｸがかかる。
{

}

void SceneMng::Draw(void)
{
	ClsDrawScreen();

	for (auto dQue : _drawList)
	{
		double x, y, rad;
		int id;

		std::tie(id, x, y, rad) = dQue;

		DrawRotaGraph(
			static_cast<int>(x),
			static_cast<int>(y),
			1.0,
			rad,
			id,
			true);
	}

	ScreenFlip();
}

SceneMng::~SceneMng()
{

}

void SceneMng::Run(void)
{
	SysInit();
	_activeScene = std::make_unique<GameScene>();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		_activeScene = (*_activeScene).Update(std::move(_activeScene));	// moveを使うことでコピーを作らずに所有権の譲渡ができる
		// スマートポインタとしてわかりやすいのが上　_activeScene->Update();
	}

}

bool SceneMng::AddDrawQue(DrawQueT dQue)
{
	if (std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dQue) <= 0) 	// std::get<何番目>で取り出す
	{
		// 画像IDが不正なので、追加しない
		return false;
	}

	_drawList.emplace_back(dQue);
	return true;
}

bool SceneMng::SysInit(void)
{
	//ｼｽﾃﾑ処理
	SetWindowText("Second 30");
	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);				// 800*600ﾄﾞｯﾄ、65536色ﾓｰﾄﾞに設定
	ChangeWindowMode(true);										// true:window  false:ﾌﾙｽｸﾘｰﾝ
	if (DxLib_Init() == -1)										// DXﾗｲﾌﾞﾗﾘの初期化
	{
		return false;												// DxLibﾗｲﾌﾞﾗﾘ初期化処理
	}

	SetDrawScreen(DX_SCREEN_BACK);	// 描画先をﾊﾞｯｸﾊﾞｯﾌｧに設定
	return false;
}
