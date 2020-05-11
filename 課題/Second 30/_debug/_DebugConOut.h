#pragma once
#ifdef _DEBUG
#include <Windows.h>
#include <memory>


// ���ޯ��ү���ޗp��`
#define AST() {\
    CHAR ast_mes[256];\
    wsprintf(ast_mes, "%s %d�s��\0", __FILE__, __LINE__);\
    MessageBox(0, ast_mes, "���ĕ\��", MB_OK);\
    }

#define TRACE(fmt, ...) printf(fmt, __VA_ARGS__); //fmt�́h�h�̒��g ...�́��Ȃǂ̉ώ�

class _DebugConOut
{
public:
	static _DebugConOut& GetInstance(void)
	{
		return *sInstance;
	}

private:
	struct _DebugConOutDeleter
	{
		void operator()(_DebugConOut* _debugConOut) const // ��ځ@�I�[�o�[���[�h�������@��ځ@�E�ӎ�������ذĂ����������E���ɏ���
		{
			delete _debugConOut;
		}
	};

	_DebugConOut();
	~_DebugConOut();

	FILE* _debugFp = nullptr;

	static std::unique_ptr<_DebugConOut, _DebugConOutDeleter> sInstance;
};

#else	//_DEBUG
#define AST()
#define TRACE(fmt, ...)

#endif //_DEBUG

