#include <type_traits>  // enum classをｷｬｽﾄする時に使う
#include "INPUT_ID.h"

INPUT_ID begin(INPUT_ID)
{
	return INPUT_ID::LEFT;
}

INPUT_ID end(INPUT_ID)
{
	return INPUT_ID::MAX;
}

INPUT_ID operator*(INPUT_ID key)
{
	return key;
}

INPUT_ID operator++(INPUT_ID& key)
{
	return key = static_cast<INPUT_ID>(std::underlying_type<INPUT_ID>::type(key) + 1); // 渡したｵﾌﾞｼﾞｪｸﾄの既定の型を返す　
}
