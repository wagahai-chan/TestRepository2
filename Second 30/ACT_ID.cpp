#include <type_traits>  // enum class�𷬽Ă��鎞�Ɏg��
#include "ACT_ID.h"

ACT_ID begin(ACT_ID)
{
	return ACT_ID::STOP;
}

ACT_ID end(ACT_ID)
{
	return ACT_ID::MAX;
}

ACT_ID operator*(ACT_ID key)
{
	return key;
}

ACT_ID operator++(ACT_ID& key)
{
	return key = static_cast<ACT_ID>(std::underlying_type<ACT_ID>::type(key) + 1); // �n������޼ު�Ă̊���̌^��Ԃ��@
}