
// DrawApp_LSLDoc.h : CDrawApp_LSLDoc ��Ľӿ�
//


#pragma once
#include"Fig.h"
#include"AllTypeNum.h"
class CDrawApp_LSLDoc : public CDocument
{
protected: // �������л�����
	CDrawApp_LSLDoc();
	DECLARE_DYNCREATE(CDrawApp_LSLDoc)

// ����
public:
	CArray<CFig*, CFig*> m_Figures;
	UINT m_FigNumber;
	VOID updateCount() { m_count = 0; }
	//CFig *pFig[MAX_FIG_NUM];
private:
	UINT m_count;
	COLORREF m_color;
// ����
public:
	BOOL AddOneFigure(CFig* p);
	VOID FreeAllFigureData();
	COLORREF getColor() { return m_color; }
	VOID setColor(COLORREF color) { m_color = color; }
// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CDrawApp_LSLDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
