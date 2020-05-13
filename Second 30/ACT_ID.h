#pragma once

enum class ACT_ID
{
	NON,
	STOP,
	LEFT,
	RIGHT,
	JUMP,
	MAX
};

ACT_ID begin(ACT_ID);
ACT_ID end(ACT_ID);
ACT_ID operator*(ACT_ID key);
ACT_ID operator++(ACT_ID& key);