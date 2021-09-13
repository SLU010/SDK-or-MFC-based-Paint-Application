#pragma once


// CInputText 对话框

class CInputText : public CDialogEx
{
	DECLARE_DYNAMIC(CInputText)

public:
	CInputText(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInputText();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INPUT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedOk();
	CString m_inputText;
};
