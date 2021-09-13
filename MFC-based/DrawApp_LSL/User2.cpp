// User2.cpp : 实现文件
//

#include "stdafx.h"
#include "DrawApp_LSL.h"
#include "User2.h"
#include "afxdialogex.h"


// CUser2 对话框

IMPLEMENT_DYNAMIC(CUser2, CPropertyPage)

CUser2::CUser2()
	: CPropertyPage(IDD_USER2)
{

}

CUser2::~CUser2()
{
}

void CUser2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUser2, CPropertyPage)
END_MESSAGE_MAP()


// CUser2 消息处理程序
