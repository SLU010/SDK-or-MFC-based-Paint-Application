#pragma once


// CEraser 对话框

class CEraser : public CDialogEx
{
	DECLARE_DYNAMIC(CEraser)

public:
	CEraser(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEraser();
	
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ERASER };
#endif
public:
	UINT m_size;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio1();
};
