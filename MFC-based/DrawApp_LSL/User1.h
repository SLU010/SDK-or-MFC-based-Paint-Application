#pragma once


// CUser1 �Ի���

class CUser1 : public CPropertyPage
{
	DECLARE_DYNAMIC(CUser1)

public:
	CUser1();
	virtual ~CUser1();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USER1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
};
