// User3.cpp : 实现文件
//

#include "stdafx.h"
#include "DrawApp_LSL.h"
#include "User3.h"
#include "afxdialogex.h"


// CUser3 对话框

IMPLEMENT_DYNAMIC(CUser3, CPropertyPage)

CUser3::CUser3()
	: CPropertyPage(IDD_USER3)
{

}

CUser3::~CUser3()
{
}

void CUser3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUser3, CPropertyPage)
END_MESSAGE_MAP()


// CUser3 消息处理程序


BOOL CUser3::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
	// 获得父窗口，即属性表CPropertySheet类   
	CPropertySheet* psheet = (CPropertySheet*)GetParent();
	//设置属性表只有“完成”按钮   
	psheet->SetFinishText(_T("完成"));
	return CPropertyPage::OnSetActive();
}


BOOL CUser3::OnWizardFinish()
{
	// TODO: 在此添加专用代码和/或调用基类

	// 提示向导完成   
	MessageBox(_T("使用说明向导阅读完成！若要再次查看请点击使用向导！"));
	return CPropertyPage::OnWizardFinish();
}
