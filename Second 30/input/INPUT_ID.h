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
	L1,
	R1,
	L2,
	R2,
	L3,
	R3,
	SELECT,
	START,
	MAX
};

INPUT_ID begin(INPUT_ID);
INPUT_ID end(INPUT_ID);
INPUT_ID operator*(INPUT_ID key);
INPUT_ID operator++(INPUT_ID& key);

