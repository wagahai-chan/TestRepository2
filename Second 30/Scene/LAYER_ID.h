#pragma once

enum class LAYER // debuglayer�͓Ɨ����Ă��邩�炢��Ȃ�
{
	BG,		// �w�i
	OBJ,	// ��޼ު��
	CHAR,	// ���
	UI,		// հ�ް����̪��
	EX,		// ������ʗp
	MAX
};

LAYER begin(LAYER);
LAYER end(LAYER);
LAYER operator*(LAYER key);
LAYER operator++(LAYER& key);