#pragma once

enum class INPUT_ID  // Ï¯Ìß‚Ì·°  Šù’è‚ÌŒ^‚ğw’è‚Å‚«‚é
{
	A,		// ¶ˆÚ“®
	D,		// ‰EˆÚ“®
	W,		// ãˆÚ“®
	S,		// ‰ºˆÚ“®
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

