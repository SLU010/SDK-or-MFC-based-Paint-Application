// ChoosePenType.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrawApp_LSL.h"
#include "ChoosePenType.h"
#include "afxdialogex.h"


// CChoosePenType �Ի���

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


// CChoosePenType ��Ϣ�������


void CChoosePenType::OnClickedDash()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	select = PS_DASH;
	CheckRadioButton(IDC_SOLID, IDC_DOT, IDC_DASH);
}


void CChoosePenType::OnClickedDashdot()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	select = PS_DASHDOT;
	CheckRadioButton(IDC_SOLID, IDC_DOT, IDC_DASHDOT);
}


void CChoosePenType::OnClickedDashdotdot()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	select = PS_DASHDOTDOT;
	CheckRadioButton(IDC_SOLID, IDC_DOT, IDC_DASHDOTDOT);
}


void CChoosePenType::OnClickedDot()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	select = PS_DOT;
	CheckRadioButton(IDC_SOLID, IDC_DOT, IDC_DOT);
}


void CChoosePenType::OnClickedSolid()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	select = PS_SOLID;
	CheckRadioButton(IDC_SOLID, IDC_DOT, IDC_SOLID);
}
