#pragma once


// CChooseColor 对话框

class CChooseColor : public CDialogEx
{
	DECLARE_DYNAMIC(CChooseColor)

public:
	CChooseColor(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChooseColor();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

private:
	COLORREF m_color;
public:
	COLORREF getColor() { return m_color; }
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPenColorchoose();
};
