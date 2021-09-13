#pragma once


// CUser3 对话框

class CUser3 : public CPropertyPage
{
	DECLARE_DYNAMIC(CUser3)

public:
	CUser3();
	virtual ~CUser3();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USER3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
};
