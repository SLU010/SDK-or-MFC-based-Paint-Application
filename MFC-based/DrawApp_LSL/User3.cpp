// User3.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrawApp_LSL.h"
#include "User3.h"
#include "afxdialogex.h"


// CUser3 �Ի���

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


// CUser3 ��Ϣ�������


BOOL CUser3::OnSetActive()
{
	// TODO: �ڴ����ר�ô����/����û���
	// ��ø����ڣ������Ա�CPropertySheet��   
	CPropertySheet* psheet = (CPropertySheet*)GetParent();
	//�������Ա�ֻ�С���ɡ���ť   
	psheet->SetFinishText(_T("���"));
	return CPropertyPage::OnSetActive();
}


BOOL CUser3::OnWizardFinish()
{
	// TODO: �ڴ����ר�ô����/����û���

	// ��ʾ�����   
	MessageBox(_T("ʹ��˵�����Ķ���ɣ���Ҫ�ٴβ鿴����ʹ���򵼣�"));
	return CPropertyPage::OnWizardFinish();
}
