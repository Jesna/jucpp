/**
APIHook ���쳣ǿ������� Winddows API �Ĺ��ܣ�����ʹ�÷ǳ��򵥡�
ϵͳ API ���ػ���һ����Ҫ���������κ���ԭ���� API �����⣬APIHook
�����Ľ����������⡣
*/
#include "../juwnd.h"
#pragma usexpstyle
//����һ�� MessageBox �������ͣ���Ϊ������Ҫʹ��������͵ĺ���ָ�롣
typedef int (__stdcall * MSGBOX)(HWND,LPCWSTR,LPCWSTR,int);
//���������Ϊ����ȫ��ʹ�� hook ������������㡣
ju::APIHook hook;
//����һ�������Լ��ĺ������������Ҫ���ص� API ������ȫ��ͬ�ĸ�ʽ��
//���������ͷ���ֵ���Լ������� __stdcall��������һ����ĳ�Ա������
int __stdcall alert(HWND hWnd,LPCWSTR msg,LPCWSTR title,int option){
	//��ʾ����
	ju::LogfI(L"alert--hWnd:%d,msg:%s,title:%s,option:%d",hWnd,msg,title,option);
	//��ȡϵͳԭ���� API ָ�룬��ʱ������� API �����������ᱻָ�����
	MSGBOX org = (MSGBOX)hook.OrgFunc();
	ju::LocalString str;
	str.Format(L"alert: %s",msg);
	//����ϵͳԭ���ĺ���
	return org(hWnd,str,title,option);
}
//��������ĳ�Ա������
class A{
public:
	int alert(HWND hWnd,LPCWSTR msg,LPCWSTR title,int option){
		//��ʾ����
		ju::LogfI(L"A::alert--hWnd:%d,msg:%s,title:%s,option:%d",hWnd,msg,title,option);
		//��ȡϵͳԭ���� API ָ�룬��ʱ������� API �����������ᱻָ�����
		MSGBOX org = (MSGBOX)hook.OrgFunc();
		ju::LocalString str;
		str.Format(L"A::alert: %s",msg);
		//����ϵͳԭ���ĺ���
		return org(hWnd,str,title,option);
	}
};
WINMAIN{
	ju::LogShowWindow();

	//������������ API ���������Ĵ�С�ܺͣ���Ϊֻ�Ǵ�����һ������ָ�룬�ڲ��޷�
	//�ж������ĸ�ʽ��16 �ļ��㷽ʽ�ǣ�MessageBox ������ 4 ��������ÿ���Ĵ�С��
	//�� 4 �ֽڣ���Ҫע����ǣ����� API �������� 4 �ֽڲ��������ܱ�����Ϊ char 
	//֮��ģ�������� 4 �ֽڣ����� 8 �ֽڡ�12 �ֽڵȵȡ�
	if(hook.SetHook(&MessageBox,&alert,16)){
		::MessageBox(0,L"Hello",L"OK",MB_ICONINFORMATION);
	}else{
		ju::LogfE(L"�󶨺���ʧ�ܣ����������Ƿ���ȷ��");
	}
	//�ָ�ϵͳ API���������ô���������İ󶨾ͻ�����⣬�ᶪʧϵͳ API �ĵ�ַ
	hook.UnHook();

	A a;
	//Ϊ�˰���ĳ�Ա����������һ�� Function ����һ����˵ Function �������
	//��Ȼ���ܱ����У��ǲ����ͷŵģ���������� func ֻ��һ���������ݵ����ã�ֻҪ
	//hookû�б����٣����þͻ�һ��������
	ju::Function<int,HWND,LPCWSTR,LPCWSTR,int> func;
	//�� thiscall ������
	func.Bind(&a,&A::alert);
	//�Ѻ�����Ϊ hook ���� API��
	if(hook.SetHook(&MessageBox,func)){
		::MessageBox(0,L"Hello",L"OK",MB_ICONINFORMATION);
	}else{
		ju::LogfE(L"�󶨺���ʧ�ܣ����������Ƿ���ȷ��");
	}
	ju::MsgLoop::Start();
	//����û�е��� UnHook������Ϊ�������ֻ�ڵ�ǰ������Ч����ϵͳû���κ�Ӱ��
	//���Ҫȫ������ API������Ҫ�Ѵ���д��һ�� dll ��̬���ӿ��
	//��Ȼ����ǰ����һ���ǲ���Ҫ����ϵͳ API �ģ���Ϊ���붼���Լ�д�ġ�����Ҳ
	//��һ������������һ����Ŀ��ʹ���� WebBrowser �ؼ������뿴�����������󣬾�
	//ʹ���˽��̼��� API ���� socket ���� send��recv ֮�ࡣ
}
