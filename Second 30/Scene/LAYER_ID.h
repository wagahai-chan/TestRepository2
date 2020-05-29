#pragma once

enum class LAYER // debuglayerは独立しているからいれない
{
	BG,		// 背景
	OBJ,	// ｵﾌﾞｼﾞｪｸﾄ
	CHAR,	// ｷｬﾗ
	UI,		// ﾕｰｻﾞｰｲﾝﾀｰﾌｪｰｽ
	EX,		// 特殊効果用
	MAX
};

LAYER begin(LAYER);
LAYER end(LAYER);
LAYER operator*(LAYER key);
LAYER operator++(LAYER& key);