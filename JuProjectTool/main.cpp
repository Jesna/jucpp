/**
	���̴������ߣ�����һ�������Ĺ���ģ�棬�˹����ڿ�ִ���ļ�����һ��Ŀ¼
	����һ�������ļ��У����ſ���� lib �ļ������ڹ���ͬ��Ŀ¼��
*/
#include "../juwnd.h"
#pragma usexpstyle

class Main : public ju::Frame{
protected:
	ju::GroupBox	gBox;
	ju::Button		btnOk;
	ju::Edit		editName;
	ju::TopLayout	layout;
	void onCreate(ju::IWnd*){
		gBox.Param->Text = L"��д��������";
		gBox.Create(_Handle);
		//�� gBox �󶨵� layout �ϣ��Կ��Ը��������ڳߴ�仯��
		layout.SetControl(gBox);
		//���ñ߽磬ע�⣺��Ϊ layout �� TopLayout��SetParam �ĵ�һ�͵ڶ���������length��weight������Ч�ġ�
		//�������ֶ���TopLayout��һ�����������󶨵Ĵ��ڱ仯��
		layout.SetParam(0,1,10,10,10,10);

		ju::Layout* editLay = layout.Add();
		editName.Param->Text = L"";
		editName.Create(_Handle);
		editLay->SetControl(editName);
		editLay->SetParam(0,1,20,30,20,20);

		ju::Layout* btnLay = layout.Add();
		btnOk.Param->Text = L"��������";
		btnOk.Create(_Handle);
		btnLay->SetControl(btnOk);
		btnLay->SetParam(0,1,20,0,20,20);
	}
	void onCommand(WORD id,WORD type,ju::IWnd* wnd){
		if(wnd==&btnOk){//����˴�����ť
			ju::LocalString name;
			editName.GetText(name);
			if(name.Length()==0){
				alertError(L"��Ҫ���빤������");
				return;
			}
			if(createProject(name)){
				alertOk(L"�����ɹ�");
				Close();
			}
		}
	}
	void alertError(LPCWSTR msg){
		::MessageBox(_Handle,msg,L"Error",MB_ICONERROR);
	}
	void alertOk(LPCWSTR msg){
		::MessageBox(_Handle,msg,L"Error",MB_ICONINFORMATION);
	}
	bool createProject(LPCWSTR name){
		ju::FileStream fs;
		if(!fs.OpenExist(L"proj_temp.txt")){
			alertError(L"û���ҵ� proj_temp.txt �ļ�");
			return false;
		}
		ju::String proj;
		int len = fs.ReadString(proj);
		fs.Close();

		if(!len){
			alertError(L"proj_temp.txt ��ȡʧ��");
			return false;
		}
		ju::String rep = L"{proj}";
		int pos1 = proj.Find(rep);
		if(pos1<0){
			alertError(L"proj_temp.txt ��ʽ����");
			return false;
		}
		int pos2 = proj.Find(rep,pos1+5);
		if(pos2<0){
			alertError(L"proj_temp.txt ��ʽ����");
			return false;
		}
		proj.Replace(name,pos2,rep.Length());
		proj.Replace(name,pos1,rep.Length());

		ju::String new_proj;
		new_proj.Format(L"../%s",name);
		if(!ju::CreateFolder(new_proj)){
			alertError(L"�޷����������ļ���");
			return false;
		}
		ju::String proj_file;
		proj_file.Format(L"../%s/%s.vcproj",name,name);
		if(!fs.Create(proj_file,CREATE_NEW)){
			alertError(L"ͬ�������Ѿ����ڣ�������ѡһ�����ƻ���ɾ�����ڵĹ����ļ���");
			return false;
		}
		fs.WriteString(proj);
		fs.Close();

		proj_file.Format(L"../%s/main.cpp",name);
		if(!fs.Create(proj_file,CREATE_NEW)){
			alertError(L"�޷����� main.cpp�����ļ��Ѿ�����");
			return false;
		}
		LPCWSTR _main = L"\
#include \"../juwnd.h\"\r\n\
#pragma usexpstyle\r\n\
\r\n\
WINMAIN{\r\n\
	ju::Frame main;\r\n\
	main.Param->Text = \"%s\";\r\n\
	main.Create();\r\n\
	ju::MsgLoop::Start();\r\n\
}\r\n";
		ju::String main;
		main.Format(_main,name);
		fs.WriteString(main);
		return true;
	}
public:
	Main(){
		Param->Text = L"jucpp ���̴�������";		//���ڱ���
		ju::SetWndRememberPos(this,L"main_wnd");	//�����Զ����洰��λ��
		layout.SetContainer(this);					//���ô˴��ڵĲ��ֶ���
		ju::Font* font = ju::GetDefaultFont();		//�޸�ȱʡ����
		font->SetSize(20);
		font->Create();

		OnCreate.Add(this,&Main::onCreate);			//���� WM_CREATE �ص�
		OnCommand.Add(this,&Main::onCommand);		//���� WM_COMMAND �ص�
	}
};
WINMAIN{
	Main main;
	main.Create();
	ju::MsgLoop::Start();
};