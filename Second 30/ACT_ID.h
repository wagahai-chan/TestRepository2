#pragma once

enum class ACT_ID
{
	NON,
	STOP,		// �ҋ@���
	FALL,		// ������
	LEFT,		// ���ړ���
	RIGHT,		// �E�ړ���
	JUMP,		// �ެ��ߒ�
	MAX		
};

ACT_ID begin(ACT_ID);
ACT_ID end(ACT_ID);
ACT_ID operator*(ACT_ID key);
ACT_ID operator++(ACT_ID& key);