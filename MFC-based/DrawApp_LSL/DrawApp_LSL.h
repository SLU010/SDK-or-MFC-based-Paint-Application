
// DrawApp_LSL.h : DrawApp_LSL Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CDrawApp_LSLApp:
// �йش����ʵ�֣������ DrawApp_LSL.cpp
//

class CDrawApp_LSLApp : public CWinApp
{
public:
	CDrawApp_LSLApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDrawApp_LSLApp theApp;
