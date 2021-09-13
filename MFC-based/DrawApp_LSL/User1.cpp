// User1.cpp : 实现文件
//

#include "stdafx.h"
#include "DrawApp_LSL.h"
#include "User1.h"
#include "afxdialogex.h"


// CUser1 对话框

IMPLEMENT_DYNAMIC(CUser1, CPropertyPage)

CUser1::CUser1()
	: CPropertyPage(IDD_USER1)
{

}

CUser1::~CUser1()
{
}

void CUser1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUser1, CPropertyPage)
END_MESSAGE_MAP()


// CUser1 消息处理程序


BOOL CUser1::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
	// 获得父窗口，即属性表CPropertySheet类   
	CPropertySheet* psheet = (CPropertySheet*)GetParent();
	// 设置属性表只有“下一步”按钮   
	psheet->SetWizardButtons(PSWIZB_NEXT);
	//psheet->SetWizardButtons(PSWIZB_CANCEL);
	return CPropertyPage::OnSetActive();
}
