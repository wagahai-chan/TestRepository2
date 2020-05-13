#pragma once

enum class INPUT_ID  // ϯ�߂̷�  ����̌^���w��ł���
{
	LEFT,			// ���ړ�
	RIGHT,			// �E�ړ�
	UP,				// ��ړ�
	DOWN,			// ���ړ�
	LEFTBUTTON,		// ���{�^��
	RIGHTBUTTON,	// �E�{�^��
	UPBUTTON,		// ��{�^��
	DOWNBUTTON,		// ���{�^��
	MAX
};

INPUT_ID begin(INPUT_ID);
INPUT_ID end(INPUT_ID);
INPUT_ID operator*(INPUT_ID key);
INPUT_ID operator++(INPUT_ID& key);

