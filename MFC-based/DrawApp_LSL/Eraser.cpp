// Eraser.cpp : 实现文件
//

#include "stdafx.h"
#include "DrawApp_LSL.h"
#include "Eraser.h"
#include "afxdialogex.h"


// CEraser 对话框

IMPLEMENT_DYNAMIC(CEraser, CDialogEx)

CEraser::CEraser(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ERASER, pParent)
{

}

CEraser::~CEraser()
{
}

void CEraser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEraser, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO3, &CEraser::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO2, &CEraser::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO1, &CEraser::OnBnClickedRadio1)
END_MESSAGE_MAP()


// CEraser 消息处理程序


void CEraser::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_size = 10;
	CheckRadioButton(IDC_RADIO1, IDC_RADIO3, IDC_RADIO3);
}


void CEraser::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_size = 30;
	CheckRadioButton(IDC_RADIO1, IDC_RADIO3, IDC_RADIO2);
}


void CEraser::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_size = 50;
	CheckRadioButton(IDC_RADIO1, IDC_RADIO3, IDC_RADIO1);
}
