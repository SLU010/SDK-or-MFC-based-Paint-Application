#pragma once


// CUser3 �Ի���

class CUser3 : public CPropertyPage
{
	DECLARE_DYNAMIC(CUser3)

public:
	CUser3();
	virtual ~CUser3();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USER3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
};
