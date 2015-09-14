#pragma once
//��̬�������Ѿ�ɾ��
#ifndef JUWND_EXPORTS
	//�ⲿ����
	#ifdef USE_DYNAMIC_CONCISEUI
		#define JUWND_API __declspec(dllimport)
		#define USE_DYNAMIC_BASE	//ʹ�ö�̬base��
	#else
		#define JUWND_API
	#endif
#else
	//�����̵���
	#ifdef JUWND_STATIC
		#define JUWND_API
	#else
		#define USE_DYNAMIC_BASE	//ʹ�ö�̬base��
		#define JUWND_API __declspec(dllexport)
	#endif
#endif
#include "jubase.h"

#include "juwnd/window.h"
#include "juwnd/logwnd.h"
#include "juwnd/usermenu.h"
#include "juwnd/comdlg.h"
#include "juwnd/dlg.h"
#include "juwnd/ictrl.h"
#include "juwnd/ctrl.h"

#include "juwnd/Layout.h"
#include "juwnd/notifyicon.h"
#include "juwnd/wndPos.h"
//���ݰ�װĿ¼������·��.
#ifndef CONCISEUI_EXPORTS
	#ifdef _DEBUG
		#pragma comment(lib,"juwndD.lib")
	#else
		#pragma comment(lib,"juwnd.lib")
	#endif
#endif