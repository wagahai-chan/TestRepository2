#pragma once
#include <memory>
#include <map>
#include <vector>
#include <common\Vector2.h>

using VecInt = std::vector<int>;

#define lpImageMng imageMng::GetInstance()
#define IMAGE_ID(KEY) (imageMng::GetInstance().GetID(KEY))

class imageMng
{
public:
	static imageMng &GetInstance(void)
	{
		return *sInstance;
	}

	const VecInt& GetID(const std::string& key); // �Q�Ɠn��
	const VecInt& GetID(const std::string& key, const std::string& fileName);
	const VecInt& GetID(const std::string& key, const std::string& fileName, const Vector2& divSize, const Vector2& divCnt);

private:
	struct imageMngDeleter
	{
		void operator()(imageMng* imageMng) const // ��ځ@�I�[�o�[���[�h�������@��ځ@�E�ӎ�������ذĂ����������E���ɏ���
		{
			delete imageMng;
		}
	};

	imageMng();
	~imageMng();
	static std::unique_ptr<imageMng, imageMngDeleter> sInstance;
	//�f�t�H���g��ذ���~imageMng();
	//������ذ���@�������������ذ��

	std::map<std::string, VecInt> imgMap;
};


