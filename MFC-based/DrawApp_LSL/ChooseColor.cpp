// ChooseColor.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrawApp_LSL.h"
#include "ChooseColor.h"
#include "afxdialogex.h"

#include"DrawApp_LSLDoc.h"
#include"MainFrm.h"
#include"DrawApp_LSLView.h"
// CChooseColor �Ի���

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


// CChooseColor ��Ϣ�������


void CChooseColor::OnBnClickedPenColorchoose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CColorDialog colorDlg(m_color);         // ������ɫ�Ի��򣬴����ʼ��ɫֵ   
	if (IDOK == colorDlg.DoModal())       // ��ʾ��ɫ�Ի��򣬲��ж��Ƿ����ˡ�ȷ����   
	{
		m_color=colorDlg.GetColor();      // ��ȡ��ɫ�Ի�����ѡ�����ɫֵ   
		SetDlgItemInt(IDC_COLOR_EDIT, m_color);         // ��Color�༭������ʾ��ѡ��ɫֵ   
		SetDlgItemInt(IDC_R_EDIT, GetRValue(m_color));  // ��R�༭������ʾ��ѡ��ɫ��R����ֵ   
		SetDlgItemInt(IDC_G_EDIT, GetGValue(m_color));  // ��G�༭������ʾ��ѡ��ɫ��G����ֵ   
		SetDlgItemInt(IDC_B_EDIT, GetBValue(m_color));  // ��B�༭������ʾ��ѡ��ɫ��B����ֵ   
	}
}
