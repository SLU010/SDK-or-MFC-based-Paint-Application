
// DrawApp_LSLView.h : CDrawApp_LSLView 类的接口
//

#pragma once

#include"MyLine.h"
#include"MyRect.h"
#include"MyEllipse.h"
#include"MyText.h"
#include"MyFree.h"
#include"AllTypeNum.h"

class CDrawApp_LSLView : public CView
{
protected: // 仅从序列化创建
	CDrawApp_LSLView();
	DECLARE_DYNCREATE(CDrawApp_LSLView)

// 特性
public:
	CDrawApp_LSLDoc *GetDocument() const;
	CRectTracker m_tracker;
	CFig *pOld;
private:
	BOOL m_bDrawFlag;
	UINT m_linenum, m_rectnum, m_ellipsenum, m_textnum, m_freenum;
	//CMyLine *m_lines = new CMyLine[MAX_FIG_NUM];//只分配两个 需要时再动态分配内存
	//CMyRect *m_rects = new CMyRect[MAX_FIG_NUM];
	//CMyEllipse *m_ellipses = new CMyEllipse[MAX_FIG_NUM];
	//CMyText *m_texts = new CMyText[MAX_FIG_NUM];
	//CMyFree *m_frees = new CMyFree[MAX_FIG_NUM];
	CMyLine *m_lines;
	CMyRect *m_rects;
	CMyEllipse *m_ellipses;
	CMyFree *m_frees;
	
	LOGPEN m_logpen, m_eraser;
	LOGBRUSH m_logbrush;
	COLORREF m_textcolor;
	LOGFONT m_logfont;

	int m_selectnum;
	CPoint ptFree;

	CPoint ptS, ptE;
	//CMyLine *m_pLine = new CMyLine;
	//CMyRect *m_pRect = new CMyRect;
// 操作
public:
	VOID setLogPen(LOGPEN logpen) { m_logpen = logpen; }
	VOID setLogBrush(LOGBRUSH logbrush) { m_logbrush = logbrush; }
	VOID setLogPenColor(COLORREF color) { m_logpen.lopnColor = color; }
	VOID setLogPenWidth(UINT x) { m_logpen.lopnWidth.x = x; }
	VOID setLogPenType(UINT type) { m_logpen.lopnStyle = type; }
	VOID setLogBrushColor(COLORREF color) { m_logbrush.lbColor = color; }
	VOID setLogFont(LOGFONT logfont) { m_logfont = logfont; }
	VOID setColorText(COLORREF color) { m_textcolor = color; }
	VOID setSelectNum(int x) { m_selectnum = x; }
	VOID setEraserSize(int x) { m_eraser.lopnWidth.x = x; }
	int getSelectNum() { return m_selectnum; }
	LOGFONT getLogFont() { return m_logfont; }
	LOGPEN getLogPen() { return m_logpen; }
	LOGBRUSH getLogBrush() { return m_logbrush; }
	COLORREF getColorText() { return m_textcolor; }
	COLORREF getPenColor() { return m_logpen.lopnColor; }
	COLORREF getBrushColor() { return m_logbrush.lbColor; }
	int selectWhichFig(CPoint pt);
	BOOL clearSelect(CPoint pt);
	VOID clearScreen();
	//CFig* memoryAllocation(CFig* pFig, int num);//动态内存分配
	//CMyFree* memoryAllocationFree(CMyFree* pFig, int num);
	//void setFigInSelect();
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CDrawApp_LSLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
//	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnFixBorderColor();
	afx_msg void OnFixCharacter();
	afx_msg void OnFixFillColor();
	afx_msg void OnFixLineStyle();
	afx_msg void OnFixLineWidth();
//	afx_msg void OnIdrFixMenu();
	afx_msg void OnDelete();
	afx_msg void OnFixTextColor();
	afx_msg void OnClear();
//	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
//	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // DrawApp_LSLView.cpp 中的调试版本
inline CDrawApp_LSLDoc* CDrawApp_LSLView::GetDocument() const
   { return reinterpret_cast<CDrawApp_LSLDoc*>(m_pDocument); }
#endif

