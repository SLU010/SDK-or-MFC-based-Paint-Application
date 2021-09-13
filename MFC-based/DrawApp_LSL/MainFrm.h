
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:
	UINT m_DrawMode;
	UINT m_PenMode;
	//BOOL m_ClearScreen;
// ����
public:
	VOID ClearBuffer();
// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnEllipseFig();
	afx_msg void OnUpdateEllipseFig(CCmdUI *pCmdUI);
	afx_msg void OnColorPen();
//	afx_msg void OnUpdateColorPen(CCmdUI *pCmdUI);
	afx_msg void OnLineFig();
	afx_msg void OnUpdateLineFig(CCmdUI *pCmdUI);
	afx_msg void OnRectFig();
	afx_msg void OnUpdateRectFig(CCmdUI *pCmdUI);
	afx_msg void OnTextFig();
	afx_msg void OnUpdateTextFig(CCmdUI *pCmdUI);
	afx_msg void OnTypePen();
//	afx_msg void OnUpdateTypePen(CCmdUI *pCmdUI);
	afx_msg void OnWidthPen();
//	afx_msg void OnUpdateWidthPen(CCmdUI *pCmdUI);
	afx_msg void OnColorBrush();
	afx_msg void OnTextColor();
	afx_msg void OnTextType();
//	afx_msg void OnFileOpen();
//	afx_msg void OnFileSave();
//	afx_msg void OnFileSaveAs();
//	afx_msg void OnFileSave1();
//	afx_msg void OnFixBorderColor();
//	afx_msg void OnFixCharacter();
//	afx_msg void OnFixFillColor();
//	afx_msg void OnFixLineStyle();
//	afx_msg void OnFixLineWidth();
//	afx_msg void OnIdrFixMenu();
//	afx_msg void OnDelete();
	afx_msg void OnUser();
	afx_msg void OnFreeFig();
	afx_msg void OnUpdateFreeFig(CCmdUI *pCmdUI);
	afx_msg void OnUndo();
	afx_msg void OnSelectFig();
	afx_msg void OnUpdateSelectFig(CCmdUI *pCmdUI);
	afx_msg void OnEraser();
	afx_msg void OnUpdateEraser(CCmdUI *pCmdUI);
	afx_msg void OnEraserSize();
};


