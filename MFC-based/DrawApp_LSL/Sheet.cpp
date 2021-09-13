// Sheet.cpp : 实现文件
//

#include "stdafx.h"
#include "DrawApp_LSL.h"
#include "Sheet.h"


// CSheet

IMPLEMENT_DYNAMIC(CSheet, CPropertySheet)

CSheet::CSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_user1);
	AddPage(&m_user2);
	AddPage(&m_user3);
}

CSheet::CSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_user1);
	AddPage(&m_user2);
	AddPage(&m_user3);
}

CSheet::~CSheet()
{
}


BEGIN_MESSAGE_MAP(CSheet, CPropertySheet)
END_MESSAGE_MAP()


// CSheet 消息处理程序
