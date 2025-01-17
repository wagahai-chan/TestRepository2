#include <type_traits>
#include "LAYER_ID.h"


LAYER begin(LAYER)
{
	return LAYER::BG;
}

LAYER end(LAYER)
{
	return LAYER::MAX;
}


LAYER operator*(LAYER key)
{
	return key;
}

LAYER operator++(LAYER & key)
{
	return key = static_cast<LAYER>(std::underlying_type<LAYER>::type(key) + 1); // 渡したｵﾌﾞｼﾞｪｸﾄの既定の型を返す　
}
