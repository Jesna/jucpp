#include "../juwnd.h"
#pragma usexpstyle
class A{
public:
	int func(int a,int b){
		ju::LogfI(L"���߳���ִ�� A::func(%d,%d); ���� %d",a,b,a+b);
		return a+b;
	}
};
int __stdcall func(int a,int b){
	ju::LogfI(L"���߳���ִ�� func(%d,%d); ���� %d",a,b,a-b);
	return a-b;
}
WINMAIN{
	ju::LogShowWindow();

	//����һ�� Thread ����
	ju::Thread th;

	A a;
	//�����߳�ִ����ĳ�Ա���������Ҵ��ݲ�����Thread֧����� 10 ���������Ͳ����ĺ���
	th.Call<int>(&a,&A::func,3,2);//��������ֵ������Ϊģ��������ݣ�����ʡ��
	//һ�� Thread ����һ����ִ�У��Ͱ�����һ���̵߳ľ����Close �����ͷ���������ʹ�������µ�һ����
	//�ⲻ�������ִ�е��߳����κ�Ӱ�졣�����ִ�� Close ����������� Call ���� CallStd ����ɹ�
	th.Close();
	//�����߳�ִ�о�̬����(__stdcall)�����Ҵ��ݲ�����Thread֧����� 10 ���������Ͳ����ĺ���
	th.CallStd<int>(&func,5,3);//��������ֵ������Ϊģ��������ݣ�����ʡ��
	//Wait �����ȴ�����ִ�е��̷߳��أ����� Close �����У��鿴Wait�ķ���ֵ�����������������
	th.Wait();
	ju::MsgLoop::Start();
}
