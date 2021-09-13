// SetPenWidth.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrawApp_LSL.h"
#include "SetPenWidth.h"
#include "afxdialogex.h"

#include"MainFrm.h"
#include"DrawApp_LSLDoc.h"
#include"DrawApp_LSLView.h"

// CSetPenWidth �Ի���

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


// CSetPenWidth ��Ϣ�������


void CSetPenWidth::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CDialogEx::OnOK();
}


BOOL CSetPenWidth::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//�õ��������ָ��
	CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
	// ���Viewָ��
	CDrawApp_LSLView *pView = (CDrawApp_LSLView *)pMFram->GetActiveView();
	m_width = pView->getLogPen().lopnWidth.x;
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
