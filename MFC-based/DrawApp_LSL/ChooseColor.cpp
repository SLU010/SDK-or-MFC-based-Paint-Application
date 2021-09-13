// ChooseColor.cpp : 实现文件
//

#include "stdafx.h"
#include "DrawApp_LSL.h"
#include "ChooseColor.h"
#include "afxdialogex.h"

#include"DrawApp_LSLDoc.h"
#include"MainFrm.h"
#include"DrawApp_LSLView.h"
// CChooseColor 对话框

IMPLEMENT_DYNAMIC(CChooseColor, CDialogEx)

CChooseColor::CChooseColor(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	m_color = RGB(0, 0, 0);
}

CChooseColor::~CChooseColor()
{
}

void CChooseColor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CChooseColor, CDialogEx)
	ON_BN_CLICKED(IDC_PEN_COLORCHOOSE, &CChooseColor::OnBnClickedPenColorchoose)
END_MESSAGE_MAP()


// CChooseColor 消息处理程序


void CChooseColor::OnBnClickedPenColorchoose()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog colorDlg(m_color);         // 构造颜色对话框，传入初始颜色值   
	if (IDOK == colorDlg.DoModal())       // 显示颜色对话框，并判断是否点击了“确定”   
	{
		m_color=colorDlg.GetColor();      // 获取颜色对话框中选择的颜色值   
		SetDlgItemInt(IDC_COLOR_EDIT, m_color);         // 在Color编辑框中显示所选颜色值   
		SetDlgItemInt(IDC_R_EDIT, GetRValue(m_color));  // 在R编辑框中显示所选颜色的R分量值   
		SetDlgItemInt(IDC_G_EDIT, GetGValue(m_color));  // 在G编辑框中显示所选颜色的G分量值   
		SetDlgItemInt(IDC_B_EDIT, GetBValue(m_color));  // 在B编辑框中显示所选颜色的B分量值   
	}
}
