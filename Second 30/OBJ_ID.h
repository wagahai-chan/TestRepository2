#pragma once

enum class OBJ_ID	// ��Q����޼ު��
{
	NON,		// �����Ȃ�
	BLOCK,		// ��ۯ�
	PLAYER,
	SAW,		// ��
	GATE,		// �ްق̖�
	BUTTON,		// �ްق��J������
	DRUM,		// ���ъʁ@���̂�R�₷�̂Ɏg�p
	TREE,		// ��
	MAX
};

enum class GAME_ID
{
	MAKE,
	PLAY
};

OBJ_ID begin(OBJ_ID);
OBJ_ID end(OBJ_ID);
OBJ_ID operator*(OBJ_ID key);
OBJ_ID operator++(OBJ_ID& key);
