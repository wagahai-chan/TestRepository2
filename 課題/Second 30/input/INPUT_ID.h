#pragma once

enum class INPUT_ID  // ﾏｯﾌﾟのｷｰ  既定の型を指定できる
{
	A,		// 左移動
	D,		// 右移動
	W,		// 上移動
	S,		// 下移動
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

