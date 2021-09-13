
// DrawApp_LSLDoc.cpp : CDrawApp_LSLDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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


// CDrawApp_LSLDoc ����/����

CDrawApp_LSLDoc::CDrawApp_LSLDoc()
{
	// TODO: �ڴ����һ���Թ������
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

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	//ɾ������ͼԪ����
	FreeAllFigureData();
	SetTitle(_T("��ͼ��� ¬����"));
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


// CDrawApp_LSLDoc ���л�

void CDrawApp_LSLDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
		int iCount = m_Figures.GetSize();
		ar << iCount;
		for (int i = 0; i < iCount; i++)
		{
			//���뵱ǰͼԪ������
			ar << m_Figures[i]->getFigType();
			//���뵱ǰͼԪ������
			m_Figures[i]->Save(ar);
		}
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
		int iCount = 0;
		ar >> iCount;
		for (int i = 0; i < iCount; i++)
		{
			UINT uType = 0;
			ar >> uType;
			CFig *pFig = NULL;
			//���ݲ�ͬ���ͣ�����ͼԪ��Ȼ����������
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

// ����ͼ��֧��
void CDrawApp_LSLDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CDrawApp_LSLDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
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

// CDrawApp_LSLDoc ���

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


// CDrawApp_LSLDoc ����
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