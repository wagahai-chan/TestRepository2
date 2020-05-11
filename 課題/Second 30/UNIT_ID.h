#pragma once

enum class UNIT_ID
{
	NON,
	STOP,
	LEFT,
	RIGHT,
	JUMP,
	MAX
};

UNIT_ID begin(UNIT_ID);
UNIT_ID end(UNIT_ID);
UNIT_ID operator*(UNIT_ID key);
UNIT_ID operator++(UNIT_ID& key);