
#include "../juwnd.h"
#pragma usexpstyle

class A{
public:
	void func(ju::String& str,int i){
		ju::LogfI(L"call A::func(%s,%d)",str.Handle(),i);
	}
};
void __stdcall stdfunc(ju::String& str,int i){
	ju::LogfI(L"call stdfunc(%s,%d)",str.Handle(),i);
}
WINMAIN{
	ju::LogShowWindow();

	//���� Delegate �������������������ֱ��� ju::String& �� int ���ͣ�����ֵ�� void
	//���� Delegate �Ļص������������Ƿ��� void����Ϊ Delegate ��󶨶���ص�������
	//�����޷����÷���ֵ��
	ju::Delegate<ju::String&,int> dg;

	ju::String str = L"hello";
	//��������ص���������� Delegate ����
	A a;
	dg.Add(&a,&A::func);
	dg.Add(&stdfunc);
	//ִ�� Delegate��������ӵ�����������ִ�С�
	dg.Call(str,3);

	ju::MsgLoop::Start();
};