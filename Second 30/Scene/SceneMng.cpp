#include <DxLib.h>
#include "SceneMng.h"
#include <Scene/GameScene.h>
#include <Scene/MakeScene.h>


SceneMng*  SceneMng::sInstance = nullptr;

SceneMng::SceneMng() :ScreenSize{ 1000,750 }, ScreenCenter{ScreenSize / 2} // �ݽ�׸����������u�ԁAۯ���������B
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
		_drawList.clear();	// �O�ڰт̕`�悷��摜���폜����

		
		_activeScene = (*_activeScene).Update(std::move(_activeScene));	// move���g�����ƂŃR�s�[����炸�ɏ��L���̏��n���ł���
		// �X�}�[�g�|�C���^�Ƃ��Ă킩��₷���̂���@_activeScene->Update();
		(*_activeScene).RunActQue(std::move(_actList));
		(*_activeScene).RunMakeQue(std::move(_makeList));
		(*_activeScene).RunDeleteQue(std::move(_deleteList));

		Draw();
	}
}

bool SceneMng::AddDrawQue(DrawQueT dQue)
{
	if (std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dQue) <= 0) 	// std::get<���Ԗ�>�Ŏ��o��
	{
		// �摜ID���s���Ȃ̂ŁA�ǉ����Ȃ�
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
	//���я���
	SetWindowText("Second 30");
	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);				// 800*600�ޯāA65536�FӰ�ނɐݒ�
	ChangeWindowMode(true);										// true:window  false:�ٽ�ذ�
	if (DxLib_Init() == -1)										// DXײ���؂̏�����
	{
		return false;												// DxLibײ���؏���������
	}

	SetDrawScreen(DX_SCREEN_BACK);	// �`�����ޯ��ޯ̧�ɐݒ�

	lpImageMng.GetID("�w�i", "image/haikei.png");
	lpImageMng.GetID("����", "image/title.png");
	lpImageMng.GetID("�ڸ�", "image/select.png");
	lpImageMng.GetID("white", "image/white.png");
	lpImageMng.GetID("�c", "image/line.png");
	lpImageMng.GetID("��", "image/line2.png");

	lpImageMng.GetID("���", "image/kyara2.png", { 50,50 }, { 1,1 });
	lpImageMng.GetID("���run", "image/kyara6.png", { 50,50 }, { 20,1 });
	lpImageMng.GetID("��ۯ�", "image/block2.png", { 50,50 }, { 1,1 });
	lpImageMng.GetID("��", "image/saw.png", { 50,50 }, { 1,1 });
	lpImageMng.GetID("�ް�", "image/gate.png", { 48,80 }, { 2,1 });
	lpImageMng.GetID("����", "image/button.png", { 14,50 }, { 2,1 });
	lpImageMng.GetID("����", "image/drum.png", { 50,50 }, { 1,1 });
	lpImageMng.GetID("����2", "image/drum2.png", { 50,50 }, { 1,1 });
	lpImageMng.GetID("��", "image/tree2.png", { 300,300 }, { 1,1 });
	lpImageMng.GetID("PL����", "image/pl_blast.png", { 64,64 }, { 4,1 });


	return false;
}

