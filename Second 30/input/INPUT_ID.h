#pragma once

enum class INPUT_ID  // ϯ�߂̷�  ����̌^���w��ł���
{
	A,		// ���ړ�
	D,		// �E�ړ�
	W,		// ��ړ�
	S,		// ���ړ�
	LEFT,
	RIGHT,
	UP,
	DOWN,
	MAX
};

INPUT_ID begin(INPUT_ID);
INPUT_ID end(INPUT_ID);
INPUT_ID operator*(INPUT_ID key);
INPUT_ID operator++(INPUT_ID& key);

