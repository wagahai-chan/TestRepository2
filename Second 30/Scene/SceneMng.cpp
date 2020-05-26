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
	_activeScene = std::make_unique<GameScene>();


	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		_drawList.clear();	// 前ﾌﾚｰﾑの描画する画像を削除する

		
		_activeScene = (*_activeScene).Update(std::move(_activeScene));	// moveを使うことでコピーを作らずに所有権の譲渡ができる
		// スマートポインタとしてわかりやすいのが上　_activeScene->Update();
		(*_activeScene).RunActQue(std::move(_actList));
		(*_activeScene).RunMakeQue(std::move(_makeList));
		(*_activeScene).RunDeleteQue(std::move(_deleteList));

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

bool SceneMng::AddMakeQue(MakeQueT mQue)
{
	_makeList.emplace_back(mQue);

	return true;
}

bool SceneMng::AddDeleteQue(DeleteQueT dQue)
{
	_deleteList.emplace_back(dQue);

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
	lpImageMng.GetID("ｾﾚｸﾄ", "image/select.png");
	lpImageMng.GetID("white", "image/white.png");
	lpImageMng.GetID("縦", "image/line.png");
	lpImageMng.GetID("横", "image/line2.png");

	lpImageMng.GetID("ｷｬﾗ", "image/kyara2.png", { 50,50 }, { 1,1 });
	lpImageMng.GetID("ｷｬﾗrun", "image/kyara6.png", { 50,50 }, { 20,1 });
	lpImageMng.GetID("ﾌﾞﾛｯｸ", "image/block2.png", { 50,50 }, { 1,1 });
	lpImageMng.GetID("鋸", "image/saw.png", { 50,50 }, { 1,1 });
	lpImageMng.GetID("ｹﾞｰﾄ", "image/gate.png", { 48,80 }, { 2,1 });
	lpImageMng.GetID("ｽｲｯﾁ", "image/button.png", { 14,50 }, { 2,1 });
	lpImageMng.GetID("ﾄﾞﾗﾑ", "image/drum.png", { 50,50 }, { 1,1 });
	lpImageMng.GetID("ﾄﾞﾗﾑ2", "image/drum2.png", { 50,50 }, { 1,1 });
	lpImageMng.GetID("木", "image/tree2.png", { 300,300 }, { 1,1 });
	lpImageMng.GetID("PL爆発", "image/pl_blast.png", { 64,64 }, { 4,1 });


	return false;
}

