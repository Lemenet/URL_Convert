
// URL_Convert.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CURL_ConvertApp: 
// �йش����ʵ�֣������ URL_Convert.cpp
//

class CURL_ConvertApp : public CWinApp
{
public:
	CURL_ConvertApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CURL_ConvertApp theApp;