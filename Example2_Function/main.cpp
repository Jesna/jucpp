/* �������ã�
	���������ԡ�-->����������-->�����桱-->�����ӿ�Ŀ¼�� ��� ��../lib��
	���������ԡ�-->��C/C++��-->���������ɡ�-->�����п⡱ ѡ�� �����̵߳���(/MTd)����
	Release �汾ѡ�����߳�(/MT)��
*/
//���� juwnd.h����Ϊʹ���� Log ����
#include "../juwnd.h"
#pragma usexpstyle	//���� XP �ؼ���񣬷����Ƿǳ��ѿ��� Win98 ��ʽ

class A{
public:
	int func2(LPCWSTR str,int n){
		ju::LogfI(L"A::func2 ���� 1: %s,���� 2: %d",str,n);
		return ju::WcsLength(str);
	}
};
int __stdcall stdfunc(LPCWSTR str,int n){
	ju::LogfI(L"stdfunc ���� 1: %s,���� 2: %d",str,n);
	return ju::WcsLength(str);
}
//WINMAIN ���� WinMain �����ĺ꣬������ͨ������ں���d
WINMAIN{
	//��������ڣ�Log������и������ʽ���ƣ����ǺͿ���̨��ͬ���ǣ�����������
	ju::LogShowWindow(true);

	A a;
	ju::Function<int,LPCWSTR,int> func2;

	int r = a.func2(L"��ֱ�ӵ���",3);
	ju::LogfI(L"��������: %d",r);

	func2.Bind(&a,&A::func2);
	r = func2(L"�󶨻ص���������",6);
	ju::LogfI(L"��������: %d",r);

	func2.BindStd(&stdfunc);
	r = func2(L"�󶨾�̬�ص���������",9);
	ju::LogfI(L"��������: %d",r);
	//������Ϣѭ��������ÿ�����ڳ���ı�׼���̡�
	return ju::MsgLoop::Start();
};