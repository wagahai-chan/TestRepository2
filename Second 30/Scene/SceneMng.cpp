#include <DxLib.h>
#include "SceneMng.h"
#include <Scene/GameScene.h>
#include <Scene/MakeScene.h>


SceneMng*  SceneMng::sInstance = nullptr;

SceneMng::SceneMng() :ScreenSize{ 1000,750 }, ScreenCenter{ScreenSize / 2} // ｺﾝｽﾄﾗｸﾀが走った瞬間、ﾛｯｸがかかる。
{
	PX = 0.0;
	Pos[0] = 400.0;
	Pos[1] = 1200.0;

	for (int x = 0; x < static_cast<int>(UNIT_ID::MAX); x++)
	{
		for (int j = 0; j < static_cast<int>(MOVE_ID::MAX); j++)
		{
			check[x][j] = false;
		}
	}
}
void SceneMng::Draw(void)
{
	ClsDrawScreen();

	for (auto dQue : _drawList)
	{
		double x, y, rad;
		int id;
		bool turn;

		std::tie(id, x, y, rad,turn) = dQue;

		DrawRotaGraph(
			static_cast<int>(x) + (PX),
			static_cast<int>(y),
			1.0,
			rad,
			id,
			true,
			turn);
	}
	

	ScreenFlip();
}

SceneMng::~SceneMng()
{

}

void SceneMng::Run(void)
{
	SysInit();
	_activeScene = std::make_unique<MakeScene>();


	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		_drawList.clear();	// 前ﾌﾚｰﾑの描画する画像を削除する

		
		_activeScene = (*_activeScene).Update(std::move(_activeScene));	// moveを使うことでコピーを作らずに所有権の譲渡ができる
		// スマートポインタとしてわかりやすいのが上　_activeScene->Update();
		(*_activeScene).RunActQue(std::move(_actList));

		Draw();
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

bool SceneMng::AddActQue(ActQueT aQue)
{
	_actList.emplace_back(aQue);

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

	lpImageMng.GetID("背景", "image/haikei.png");
	lpImageMng.GetID("ﾀｲﾄﾙ", "image/title.png");
	lpImageMng.GetID("white", "image/white.png");
	lpImageMng.GetID("縦", "image/line.png");
	lpImageMng.GetID("横", "image/line2.png");

	return false;
}

