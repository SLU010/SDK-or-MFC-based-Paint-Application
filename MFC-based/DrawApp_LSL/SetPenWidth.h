#pragma once


// CSetPenWidth 对话框

class CSetPenWidth : public CDialogEx
{
	DECLARE_DYNAMIC(CSetPenWidth)

public:
	CSetPenWidth(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetPenWidth();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PEN_WIDTH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	// 最好小于5
	UINT m_width;
public:
	UINT getWidth() { return m_width; }
	VOID setWidth(int x) { m_width = x; }
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
