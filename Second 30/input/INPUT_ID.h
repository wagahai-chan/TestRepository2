#pragma once

enum class INPUT_ID  // ﾏｯﾌﾟのｷｰ  既定の型を指定できる
{
	LEFT,			// 左移動
	RIGHT,			// 右移動
	UP,				// 上移動
	DOWN,			// 下移動
	LEFTBUTTON,		// 左ボタン
	RIGHTBUTTON,	// 右ボタン
	UPBUTTON,		// 上ボタン
	DOWNBUTTON,		// 下ボタン
	MAX
};

INPUT_ID begin(INPUT_ID);
INPUT_ID end(INPUT_ID);
INPUT_ID operator*(INPUT_ID key);
INPUT_ID operator++(INPUT_ID& key);

