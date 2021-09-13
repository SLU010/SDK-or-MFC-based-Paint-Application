// ChoosePenType.cpp : 实现文件
//

#include "stdafx.h"
#include "DrawApp_LSL.h"
#include "ChoosePenType.h"
#include "afxdialogex.h"


// CChoosePenType 对话框

IMPLEMENT_DYNAMIC(CChoosePenType, CDialogEx)

CChoosePenType::CChoosePenType(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PEN_TYPE, pParent)
{
	//select = PS_SOLID;
	//CheckRadioButton(IDC_SOLID, IDC_DOT, IDC_SOLID);
}

CChoosePenType::~CChoosePenType()
{
}

void CChoosePenType::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CChoosePenType, CDialogEx)
	ON_BN_CLICKED(IDC_DASH, &CChoosePenType::OnClickedDash)
	ON_BN_CLICKED(IDC_DASHDOT, &CChoosePenType::OnClickedDashdot)
	ON_BN_CLICKED(IDC_DASHDOTDOT, &CChoosePenType::OnClickedDashdotdot)
	ON_BN_CLICKED(IDC_DOT, &CChoosePenType::OnClickedDot)
	ON_BN_CLICKED(IDC_SOLID, &CChoosePenType::OnClickedSolid)
END_MESSAGE_MAP()


// CChoosePenType 消息处理程序


void CChoosePenType::OnClickedDash()
{
	// TODO: 在此添加控件通知处理程序代码
	select = PS_DASH;
	CheckRadioButton(IDC_SOLID, IDC_DOT, IDC_DASH);
}


void CChoosePenType::OnClickedDashdot()
{
	// TODO: 在此添加控件通知处理程序代码
	select = PS_DASHDOT;
	CheckRadioButton(IDC_SOLID, IDC_DOT, IDC_DASHDOT);
}


void CChoosePenType::OnClickedDashdotdot()
{
	// TODO: 在此添加控件通知处理程序代码
	select = PS_DASHDOTDOT;
	CheckRadioButton(IDC_SOLID, IDC_DOT, IDC_DASHDOTDOT);
}


void CChoosePenType::OnClickedDot()
{
	// TODO: 在此添加控件通知处理程序代码
	select = PS_DOT;
	CheckRadioButton(IDC_SOLID, IDC_DOT, IDC_DOT);
}


void CChoosePenType::OnClickedSolid()
{
	// TODO: 在此添加控件通知处理程序代码
	select = PS_SOLID;
	CheckRadioButton(IDC_SOLID, IDC_DOT, IDC_SOLID);
}
