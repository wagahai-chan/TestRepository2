#pragma once

enum class OBJ_ID	// 障害物ｵﾌﾞｼﾞｪｸﾄ
{
	NON,		// 何もなし
	BLOCK,		// ﾌﾞﾛｯｸ
	SAW,		// 鋸
	GATE,		// ｺﾞｰﾙの門
	BUTTON,		// ｺﾞｰﾙを開くﾎﾞﾀﾝ
	DRUM,		// ﾄﾞﾗﾑ缶　ものを燃やすのに使用
	TREE,		// 木
	MAX
};

OBJ_ID begin(OBJ_ID);
OBJ_ID end(OBJ_ID);
OBJ_ID operator*(OBJ_ID key);
OBJ_ID operator++(OBJ_ID& key);
