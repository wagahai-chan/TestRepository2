#pragma once

enum class ACT_ID
{
	NON,
	STOP,		// ‘Т‹@Џу‘Ф
	FALL,		// —Ћ‰є’†
	LEFT,		// Ќ¶€Ъ“®’†
	RIGHT,		// ‰E€Ъ“®’†
	JUMP,		// јЮ¬ЭМЯ’†
	MAX		
};

ACT_ID begin(ACT_ID);
ACT_ID end(ACT_ID);
ACT_ID operator*(ACT_ID key);
ACT_ID operator++(ACT_ID& key);