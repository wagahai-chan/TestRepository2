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
		_activeScene = (*_activeScene).Update(std::move(_activeScene));	// move���g�����ƂŃR�s�[����炸�ɏ��L���̏��n���ł���
		// �X�}�[�g�|�C���^�Ƃ��Ă킩��₷���̂���@_activeScene->Update();
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
	return false;
}
