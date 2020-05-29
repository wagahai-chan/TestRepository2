#pragma once

enum class LAYER // debuglayer‚Í“Æ—§‚µ‚Ä‚¢‚é‚©‚ç‚¢‚ê‚È‚¢
{
	BG,		// ”wŒi
	OBJ,	// µÌÞ¼Þª¸Ä
	CHAR,	// ·¬×
	UI,		// Õ°»Þ°²ÝÀ°Ìª°½
	EX,		// “ÁŽêŒø‰Ê—p
	MAX
};

LAYER begin(LAYER);
LAYER end(LAYER);
LAYER operator*(LAYER key);
LAYER operator++(LAYER& key);