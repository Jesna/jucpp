
/**TaskPool ��һ���������̳߳صĹ��ߣ�����ʹ���������߳���ִ��ָ���ĺ�����
�߳�ִ��������󲻻��˳������ǵȴ������ÿ�����������ʱ�����������
���̣߳��Ͳ����������̣߳�����ʹ�������߳���ִ������*/

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
	//����һ�� TaskPool ���󣬺� Thread ��ͬ��TaskPool ��Ҫ����ָ����������
	//������Ϊ TaskPool ��ʵ�����ڴ�����һ��ִ�еĽṹ������ṹһ������
	//�ǲ��ܸı�ģ�Ҳ����˵�������������ĺ������������ͬ�ĸ�ʽ��
	ju::TaskPool<int,int,int> tp;
	A a;
	tp.StartTask(&a,&A::func,6,3);
	tp.StartStdTask(&func,6,3);
	ju::MsgLoop::Start();
	//��ʹ������Ϣѭ������ֹ�����˳���TaskPool ����������ʱҲ��ȴ����е���
	//��ִ����ɣ����������ִ�е��̣߳�����һֱ�ȴ������������ǿ�ƽ�����
	//���̣߳�����ʹ�� Close ����������ָ��һ����ȴ�ʱ�䡣
	tp.Close(1000);
}
