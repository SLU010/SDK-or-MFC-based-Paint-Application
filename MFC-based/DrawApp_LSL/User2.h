#pragma once


// CUser2 �Ի���

class CUser2 : public CPropertyPage
{
	DECLARE_DYNAMIC(CUser2)

public:
	CUser2();
	virtual ~CUser2();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USER2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
