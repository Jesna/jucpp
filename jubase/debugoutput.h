#pragma once
/* �ڴ����������Ϣ���Զ�ͬ��������Ҳ�Ϳ��ܴ����������⡣
*/
namespace ju{
#define WM_LOGPRINTTEXT	(WM_USER+0x137)
	enum{OUTPUT_DEVICE_CONSOLE,OUTPUT_DEVICE_OUTPUT};
	JUBASE_API void SetOutputDevice(int device = OUTPUT_DEVICE_OUTPUT);
	//����������ڵľ����������ڽ�����յ� WM_COPYDATA/WM_LOGPRINTTEXT ��Ϣ��
	JUBASE_API inline void SetOutputDevice(HWND wnd){SetOutputDevice((int)(UINT_PTR)wnd);}
	//��ӡ��ʽ����Ϣ��consol��print��ͬ
	JUBASE_API void Print(LPCWSTR inf,...);
	//��ӡ��ʽ����Ϣ��consol��print��ͬ
	JUBASE_API void Print(LPCSTR inf,...);
	//��ӡGetLastError��������Ϣ��
	JUBASE_API void PrintLastError();
	//��ӡWSAGetLastError����GetLastError��������Ϣ
	JUBASE_API void PrintLastError(DWORD code);
	//��ӡGetLastError��������Ϣ��
	JUBASE_API void PrintLastError(LPCWSTR fms);
	//��ӡWSAGetLastError����GetLastError��������Ϣ
	JUBASE_API void PrintLastError(LPCWSTR fms,DWORD code);
#ifdef _DEBUG
#define PrintD Print
#define PrintLastErrorD PrintLastError
#else
#define PrintD(inf,...){((void)0);}
#define PrintLastErrorD(fms){((void)0);}
#endif
	//����һ����Ϣ��ʾ����,��ʾcode�����ϵͳ������Ϣ.֧��GetLastError,WSAGetLastError�Ⱥ���.titleΪ�Ի�����⡣
	JUBASE_API void Warning(LPCWSTR title,int code);
	//����һ����Ϣ��ʾ����,��ʾ����ΪGetLastError��������
	inline JUBASE_API void Warning(LPCWSTR title){Warning(title,GetLastError());}
}