// User1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrawApp_LSL.h"
#include "User1.h"
#include "afxdialogex.h"


// CUser1 �Ի���

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


// CUser1 ��Ϣ�������


BOOL CUser1::OnSetActive()
{
	// TODO: �ڴ����ר�ô����/����û���
	// ��ø����ڣ������Ա�CPropertySheet��   
	CPropertySheet* psheet = (CPropertySheet*)GetParent();
	// �������Ա�ֻ�С���һ������ť   
	psheet->SetWizardButtons(PSWIZB_NEXT);
	//psheet->SetWizardButtons(PSWIZB_CANCEL);
	return CPropertyPage::OnSetActive();
}
