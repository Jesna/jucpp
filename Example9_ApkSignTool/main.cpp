#include "../juwnd.h"
#pragma usexpstyle

class Main : public ju::Frame{
protected:
	ju::TopLayout topLay;
	ju::Button butSign,butKeystore,butApk,butSignApk;
	ju::Edit editSign,editKeystore,editApk,editSignApk;
	ju::LogView editOutput;
	ju::Label	labKeystore,labApk,labSignApk,labOutput;
	void initLayout(){
		createLine(labKeystore,L"ǩ����Կ",editKeystore,butKeystore,L"ѡ��ǩ����Կ");
		createLine(labApk,L"Դ APK",editApk,butApk,L"ѡ��Ҫǩ���� APK");
		createLine(labSignApk,L"ǩ�� APK",editSignApk,butSignApk,L"ѡ�񱣴�λ��");
		createOutput();
	}
	void createOutput(){
		ju::Layout* lay = topLay.Add();
		lay->SetParam(0,1,0,20,0,0,true);

		ju::Layout* labLay = lay->Add();
		labLay->SetParam(80,0,0,6);
		labLay = labLay->Add();
		labLay->SetParam(20,0);
		labOutput.Param->Text = L"���:";
		labOutput.Create(_Handle);
		labLay->SetControl(labOutput);

		ju::Layout* editLay = lay->Add();
		HWND hwnd = editOutput.Create(_Handle);
		editLay->SetControl(hwnd);

		ju::Layout* butLay = lay->Add();
		butLay->SetParam(160,0,10);
		butLay = butLay->Add();
		butLay->SetParam(50,0);
		butSign.Param->Text = L"ǩ��";
		butSign.Create(_Handle);
		butLay->SetControl(butSign);
	}
	void createLine(ju::Label& lab,LPCWSTR strLab,ju::Edit& edit,ju::Button& but,LPCWSTR strBut){
		ju::Layout* lay = topLay.Add();
		lay->SetParam(30,0,0,10,0,10,true);
		
		ju::Layout* labLay = lay->Add();
		labLay->SetParam(80,0,0,6);
		lab.Param->Text = strLab;
		lab.Create(_Handle);
		labLay->SetControl(lab);
		
		ju::Layout* editLay = lay->Add();
		edit.Create(_Handle);
		editLay->SetControl(edit);

		ju::Layout* butLay = lay->Add();
		butLay->SetParam(160,0,10);
		but.Param->Text = strBut;
		but.Create(_Handle);
		butLay->SetControl(but);
	}
	void onCreate(ju::IWnd*){
		ju::SetWndIcon(_Handle,1);
		initLayout();
		loadConfig();
	}
	void onCommand(WORD id,WORD type,ju::IWnd* ctrl){
		if(ctrl==&butKeystore){
			ju::FileDialog fd;
			fd.AddFilter(L"androidǩ����Կ�ļ�",L"*.keystore");
			fd.Title = L"ѡ��Ҫǩ���� APK �ļ�";
			if(fd.ShowOpen(_Handle)){
				editKeystore.SetText(fd.GetFileName());
			}
		}else if(ctrl==&butApk){
			ju::FileDialog fd;
			fd.AddFilter(L"APK",L"*.apk");
			fd.Title = L"ѡ��Ҫǩ���� APK �ļ�";
			if(fd.ShowOpen(_Handle)){
				editApk.SetText(fd.GetFileName());
			}
		}else if(ctrl==&butSignApk){
			ju::FileDialog fd;
			fd.AddFilter(L"APK",L"*.apk");
			fd.Title = L"ѡ��ǩ���ļ�����λ��";
			fd.DefaultExt = L"apk";
			fd.DefaultFile = L"signed.apk";
			if(fd.ShowSave(_Handle)){
				editSignApk.SetText(fd.GetFileName());
			}
		}else if(ctrl==&butSign){
			ju::LocalString keystrore,src,dst;
			editKeystore.GetText(keystrore);
			editApk.GetText(src);
			editSignApk.GetText(dst);
			editOutput.Clear();
			if(ju::FileExist(dst)){
				ju::FileSystem fs;
				fs.Initialize(dst);
				fs.Delete();
				ju::String fn = dst;
				ju::FPToFileName(fn);
				editOutput.Logf(0xff,L"ɾ�� %s",fn.Handle());
			}
			ExecDosCmd(keystrore,src,dst);
		}
	}
	BOOL ExecDosCmd(LPCWSTR keystore,LPCWSTR src,LPCWSTR dst){
		SECURITY_ATTRIBUTES sa; 
		HANDLE hRead,hWrite;

		sa.nLength = sizeof(SECURITY_ATTRIBUTES); 
		sa.lpSecurityDescriptor = NULL; 
		sa.bInheritHandle = TRUE; 
		if (!CreatePipe(&hRead,&hWrite,&sa,0)){ 
			return FALSE; 
		}
		ju::String command;
		command.Format(L"jarsigner.exe -verbose -keystore \"%s\" -storepass android -signedjar \"%s\" -digestalg SHA1 -sigalg MD5withRSA -tsa https://timestamp.geotrust.com/tsa \"%s\" androiddebugkey",
			keystore,dst,src);

		STARTUPINFO si; 
		PROCESS_INFORMATION pi; 
		si.cb = sizeof(STARTUPINFO); 
		GetStartupInfo(&si); 
		si.hStdError = hWrite;            //�Ѵ������̵ı�׼��������ض��򵽹ܵ����� 
		si.hStdOutput = hWrite;           //�Ѵ������̵ı�׼����ض��򵽹ܵ����� 
		si.wShowWindow = SW_HIDE; 
		si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
		//�ؼ����裬CreateProcess�����������������MSDN 
		if (!CreateProcess(NULL,command,NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi)) {
			int errn = GetLastError();
			ju::String err;
			int len = ju::GetSystemMessage(err,errn);
			CloseHandle(hWrite); 
			CloseHandle(hRead);
			if(errn==2) err = L"�޷��ҵ� jarsigner.exe��ǩ����Ҫ��װ Java ����ʱ";
			editOutput.Log(err.Handle(),0xff0000);
			return FALSE; 
		} 
		CloseHandle(hWrite);

		char buffer[4096] = {0};          //��4K�Ŀռ����洢��������ݣ�ֻҪ������ʾ�ļ����ݣ�һ��������ǹ����ˡ� 
		DWORD bytesRead;
		ju::String output;
		while (true) { 
			if (ReadFile(hRead,buffer,4095,&bytesRead,NULL) == NULL) 
				break;
			buffer[bytesRead] = 0;
			outputInfo(buffer);
		} 
		CloseHandle(hRead);
		editOutput.Log(L"ǩ������",0xff00);
		return TRUE; 
	}
	void outputInfo(char* buffer){
		ju::LocalString ls = buffer;
		ju::StringList sl;
		sl.SplitString(ls,L"\n");
		for(uint i=0;i<sl.Count();i++){
			ju::String& str = sl.Element(i);
			if(str.Find(L"����ǩ��: assets/libbaiduprotect_x86.so")!=-1){
				int j = 0;
			}
			str.Trim();
			if(str.Length()>0)
				editOutput.Log(str);
		}
	}
	void loadConfig(){
		ju::Config cfg(0);
		ju::Json* json = cfg.Lock();
		LPCWSTR str;
		if(json->GetPropertyStr(L"keystore",str)){
			editKeystore.SetText(str);
		}
		if(json->GetPropertyStr(L"src_apk",str)){
			editApk.SetText(str);
		}
		if(json->GetPropertyStr(L"dst_apk",str)){
			editSignApk.SetText(str);
		}
	}
	void saveConfig(){
		ju::Config cfg(0);
		ju::Json* json = cfg.Lock();
		ju::LocalString str;
		editKeystore.GetText(str);
		json->SetPropertyStr(L"keystore",str);
		editApk.GetText(str);
		json->SetPropertyStr(L"src_apk",str);
		editSignApk.GetText(str);
		json->SetPropertyStr(L"dst_apk",str);
	}
	void onClose(bool& cancel,ju::IWnd*){
		saveConfig();
	}
public:
	Main(){
		ju::SetWndRememberPos(this,L"main_wnd");
		Param->Text = "ApkSignTool 1.0";
		topLay.SetContainer(this);
		ju::Font* font = ju::GetDefaultFont();
		font->SetSize(16);
		font->Create();
		OnCreate.Add(this,&Main::onCreate);
		OnCommand.Add(this,&Main::onCommand);
		OnClose.Add(this,&Main::onClose);
	}
};
WINMAIN{
	Main main;
	main.Create();
	ju::MsgLoop::Start();
}
