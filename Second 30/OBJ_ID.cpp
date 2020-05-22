#include <type_traits>  // enum class‚ğ·¬½Ä‚·‚é‚Ég‚¤
#include "OBJ_ID.h"


OBJ_ID begin(OBJ_ID)
{
	return OBJ_ID::BLOCK;
}

OBJ_ID end(OBJ_ID)
{
	return OBJ_ID::MAX;
}

OBJ_ID operator*(OBJ_ID key)
{
	return key;
}

OBJ_ID operator++(OBJ_ID& key)
{
	return key = static_cast<OBJ_ID>(std::underlying_type<OBJ_ID>::type(key) + 1); // “n‚µ‚½µÌŞ¼Şª¸Ä‚ÌŠù’è‚ÌŒ^‚ğ•Ô‚·@
}
