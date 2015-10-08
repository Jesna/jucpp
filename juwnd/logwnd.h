#pragma once

namespace ju{
	//��ʾ Log ���ڣ�����ǵ�һ�ε��ã��ڲ��ᴴ������һ��Ӧ�ó���ֻ����һ�� Log ���ڣ�
	//�����������������������ͬһ��ʵ����
	JUBASE_API void LogShowWindow(bool exit = true);
	JUBASE_API void LogHideWindow();
	JUBASE_API void LogSetFontSize(int size);
	JUBASE_API void LogSetBkColor(int color);
	JUBASE_API void LogSetMaxLine(int count);
	JUBASE_API void LogSet(int color,LPCWSTR app = 0);
	JUBASE_API void Log(LPCWSTR str);
	JUBASE_API void Log(LPCSTR str);
	JUBASE_API void Log(LPCWSTR str,int color,LPCWSTR app = (LPCWSTR)INVALID_HANDLE_VALUE);
	JUBASE_API void Log(LPCSTR str,int color,LPCWSTR app = (LPCWSTR)INVALID_HANDLE_VALUE);
	JUBASE_API void LogFormat(LPCWSTR fms,...);
	JUBASE_API void LogFormat(LPCSTR fms,...);
	JUBASE_API void LogClear();
}