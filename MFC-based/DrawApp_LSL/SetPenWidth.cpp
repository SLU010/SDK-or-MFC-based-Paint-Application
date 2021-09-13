// SetPenWidth.cpp : 实现文件
//

#include "stdafx.h"
#include "DrawApp_LSL.h"
#include "SetPenWidth.h"
#include "afxdialogex.h"

#include"MainFrm.h"
#include"DrawApp_LSLDoc.h"
#include"DrawApp_LSLView.h"

// CSetPenWidth 对话框

IMPLEMENT_DYNAMIC(CSetPenWidth, CDialogEx)

CSetPenWidth::CSetPenWidth(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PEN_WIDTH, pParent)
	, m_width(0)
{

}

CSetPenWidth::~CSetPenWidth()
{
}

void CSetPenWidth::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_WIDTH, m_width);
	DDV_MinMaxInt(pDX, m_width, 1, 50);
}


BEGIN_MESSAGE_MAP(CSetPenWidth, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSetPenWidth::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetPenWidth 消息处理程序


void CSetPenWidth::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CDialogEx::OnOK();
}


BOOL CSetPenWidth::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//得到主框架类指针
	CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
	// 获得View指针
	CDrawApp_LSLView *pView = (CDrawApp_LSLView *)pMFram->GetActiveView();
	m_width = pView->getLogPen().lopnWidth.x;
	// TODO:  在此添加额外的初始化
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
