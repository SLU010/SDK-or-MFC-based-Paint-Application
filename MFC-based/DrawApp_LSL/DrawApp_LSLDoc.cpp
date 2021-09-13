
// DrawApp_LSLDoc.cpp : CDrawApp_LSLDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DrawApp_LSL.h"
#endif
#include"AllTypeNum.h"
#include"MyLine.h"
#include"MyRect.h"
#include"MyEllipse.h"
#include"MyText.h"
#include"MyFree.h"
#include "DrawApp_LSLDoc.h"

#include <propkey.h>


//#include"MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDrawApp_LSLDoc

IMPLEMENT_DYNCREATE(CDrawApp_LSLDoc, CDocument)

BEGIN_MESSAGE_MAP(CDrawApp_LSLDoc, CDocument)
END_MESSAGE_MAP()


// CDrawApp_LSLDoc 构造/析构

CDrawApp_LSLDoc::CDrawApp_LSLDoc()
{
	// TODO: 在此添加一次性构造代码
	m_count = 0;
	m_FigNumber = 0;
	m_color = RGB(0, 0, 0);
}

CDrawApp_LSLDoc::~CDrawApp_LSLDoc()
{
	FreeAllFigureData();
	
}

BOOL CDrawApp_LSLDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	//删除所有图元数据
	FreeAllFigureData();
	SetTitle(_T("绘图软件 卢仕霖"));
	return TRUE;
}

VOID CDrawApp_LSLDoc::FreeAllFigureData()
{
	for (int i = 0; i < m_Figures.GetSize(); i++)
	{
		delete m_Figures[i];
	}
	m_Figures.RemoveAll();
}


// CDrawApp_LSLDoc 序列化

void CDrawApp_LSLDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
		int iCount = m_Figures.GetSize();
		ar << iCount;
		for (int i = 0; i < iCount; i++)
		{
			//存入当前图元的类型
			ar << m_Figures[i]->getFigType();
			//存入当前图元的数据
			m_Figures[i]->Save(ar);
		}
	}
	else
	{
		// TODO: 在此添加加载代码
		int iCount = 0;
		ar >> iCount;
		for (int i = 0; i < iCount; i++)
		{
			UINT uType = 0;
			ar >> uType;
			CFig *pFig = NULL;
			//根据不同类型，创建图元，然后载入数据
			switch (uType)
			{
			case DRAW_MODE_LINE:
				pFig = new CMyLine();
				break;
			case DRAW_MODE_TEXT:
				pFig = new CMyText();
				break;
			case DRAW_MODE_RECT:
				pFig = new CMyRect();
				break;
			case DRAW_MODE_ELLIPSE:
				pFig = new CMyEllipse();
				break;
			case DRAW_MODE_FREE:
				pFig = new CMyFree();
				break;
			default:
				break;
			}
			if (pFig)
			{
				SetModifiedFlag();
				pFig->Load(ar);
				m_Figures.Add(pFig);
				
			}
		}
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CDrawApp_LSLDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CDrawApp_LSLDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CDrawApp_LSLDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CDrawApp_LSLDoc 诊断

#ifdef _DEBUG
void CDrawApp_LSLDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDrawApp_LSLDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDrawApp_LSLDoc 命令
BOOL CDrawApp_LSLDoc:: AddOneFigure(CFig* p)
{
	if (m_count == 0)
	{
		m_Figures.Add(p);
		SetModifiedFlag();
		m_count++;
	}
	return TRUE;
}