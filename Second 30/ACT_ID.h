#pragma once

enum class ACT_ID
{
	NON,
	STOP,		// 待機状態
	FALL,		// 落下中
	LEFT,		// 左移動中
	RIGHT,		// 右移動中
	JUMP,		// ｼﾞｬﾝﾌﾟ中
	MAX		
};

ACT_ID begin(ACT_ID);
ACT_ID end(ACT_ID);
ACT_ID operator*(ACT_ID key);
ACT_ID operator++(ACT_ID& key);