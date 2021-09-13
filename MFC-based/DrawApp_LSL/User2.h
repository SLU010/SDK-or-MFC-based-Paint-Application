#pragma once


// CUser2 对话框

class CUser2 : public CPropertyPage
{
	DECLARE_DYNAMIC(CUser2)

public:
	CUser2();
	virtual ~CUser2();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USER2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
