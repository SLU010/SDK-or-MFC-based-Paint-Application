
// DrawApp_LSLDoc.h : CDrawApp_LSLDoc 类的接口
//


#pragma once
#include"Fig.h"
#include"AllTypeNum.h"
class CDrawApp_LSLDoc : public CDocument
{
protected: // 仅从序列化创建
	CDrawApp_LSLDoc();
	DECLARE_DYNCREATE(CDrawApp_LSLDoc)

// 特性
public:
	CArray<CFig*, CFig*> m_Figures;
	UINT m_FigNumber;
	VOID updateCount() { m_count = 0; }
	//CFig *pFig[MAX_FIG_NUM];
private:
	UINT m_count;
	COLORREF m_color;
// 操作
public:
	BOOL AddOneFigure(CFig* p);
	VOID FreeAllFigureData();
	COLORREF getColor() { return m_color; }
	VOID setColor(COLORREF color) { m_color = color; }
// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CDrawApp_LSLDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
