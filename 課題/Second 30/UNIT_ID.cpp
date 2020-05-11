#include <type_traits>  // enum class‚ğ·¬½Ä‚·‚é‚Ég‚¤
#include "UNIT_ID.h"

UNIT_ID begin(UNIT_ID)
{
	return UNIT_ID::STOP;
}

UNIT_ID end(UNIT_ID)
{
	return UNIT_ID::MAX;
}

UNIT_ID operator*(UNIT_ID key)
{
	return key;
}

UNIT_ID operator++(UNIT_ID& key)
{
	return key = static_cast<UNIT_ID>(std::underlying_type<UNIT_ID>::type(key) + 1); // “n‚µ‚½µÌŞ¼Şª¸Ä‚ÌŠù’è‚ÌŒ^‚ğ•Ô‚·@
}