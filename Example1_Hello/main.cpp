
//���� juwnd.h����Ϊ����Ҫ����һ�����ڳ���
#include "../juwnd.h"

//����һ���������࣬ju::Frame �������ڻ��࣬����һ���������ڣ�
//�����ڸ����������ڵ��Ӵ��ڿؼ���
class Main : public ju::Frame{
protected:
	void onCreate(ju::IWnd* wnd){
		// ��������д�����ӿؼ��ȴ��룬��ʱ�����Ѿ��������;
	}
public:
	Main(){
		//��ʱ���ڻ�û��������ʼ�������ڲ�����

		// ���ô����ı������⣩
		Param->Text = L"Hello jsuse!";
		//��� WM_CREATE ��Ϣ�ص�����������һ��������Ϣ������������һ�� OnCreate �����Ա��Delegate��
		//Delegate ֧����Ӷ���ص���������֧�������ĳ�Ա�������߾�̬������Ϊ�ص���
		OnCreate.Add(this,&Main::onCreate);
	}
};

//WINMAIN ���� WinMain �����ĺ꣬������ͨ������ں���
WINMAIN{
	Main m;
	//��������ʾ������
	m.Create();
	//������Ϣѭ��������ÿ�����ڳ���ı�׼���̡�
	return ju::MsgLoop::Start();
};