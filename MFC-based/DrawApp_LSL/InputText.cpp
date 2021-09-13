// InputText.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrawApp_LSL.h"
#include "InputText.h"
#include "afxdialogex.h"


// CInputText �Ի���

IMPLEMENT_DYNAMIC(CInputText, CDialogEx)

CInputText::CInputText(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_INPUT_DIALOG, pParent)
	, m_inputText(_T(""))
{

}

CInputText::~CInputText()
{
}

void CInputText::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_INPUT_EDIT, m_inputText);
}


BEGIN_MESSAGE_MAP(CInputText, CDialogEx)
	ON_BN_CLICKED(IDOK, &CInputText::OnBnClickedOk)
END_MESSAGE_MAP()


// CInputText ��Ϣ�������

void CInputText::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CDialogEx::OnOK();
}
