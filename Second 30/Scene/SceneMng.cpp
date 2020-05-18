#include <DxLib.h>
#include "SceneMng.h"
#include <Scene/GameScene.h>


SceneMng*  SceneMng::sInstance = nullptr;

SceneMng::SceneMng() :ScreenSize{ 800,600 } // �ݽ�׸����������u�ԁAۯ���������B
{
	
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
			static_cast<int>(x),
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

		AddDrawQue({ IMAGE_ID("�w�i")[0],400.0,300.0,0,false });
		_activeScene = (*_activeScene).Update(std::move(_activeScene));	// move���g�����ƂŃR�s�[����炸�ɏ��L���̏��n���ł���
		// �X�}�[�g�|�C���^�Ƃ��Ă킩��₷���̂���@_activeScene->Update();
		(*_activeScene).RunActQue(std::move(_actList));

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

	return false;
}
