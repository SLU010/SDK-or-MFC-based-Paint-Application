
// DrawApp_LSLView.cpp : CDrawApp_LSLView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "DrawApp_LSL.h"
#endif

#include "DrawApp_LSLDoc.h"
#include "DrawApp_LSLView.h"
#include"InputText.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include"Resource.h"
#include"MyLine.h"
#include"MyRect.h"
#include"MyEllipse.h"
#include"MyText.h"
#include"MyFree.h"
#include"MainFrm.h"
#include"AllTypeNum.h"
#include"ChooseColor.h"
#include"ChoosePenType.h"
#include"SetPenWidth.h"
// CDrawApp_LSLView
//#include"AllHead.h"

IMPLEMENT_DYNCREATE(CDrawApp_LSLView, CView)

BEGIN_MESSAGE_MAP(CDrawApp_LSLView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()

	ON_WM_RBUTTONDOWN()
	ON_WM_SETCURSOR()
//	ON_WM_CONTEXTMENU()
ON_COMMAND(IDM_FIX_BORDER_COLOR, &CDrawApp_LSLView::OnFixBorderColor)
ON_COMMAND(IDM_FIX_CHARACTER, &CDrawApp_LSLView::OnFixCharacter)
ON_COMMAND(IDM_FIX_FILL_COLOR, &CDrawApp_LSLView::OnFixFillColor)
ON_COMMAND(IDM_FIX_LINE_STYLE, &CDrawApp_LSLView::OnFixLineStyle)
ON_COMMAND(IDM_FIX_LINE_WIDTH, &CDrawApp_LSLView::OnFixLineWidth)
//ON_COMMAND(IDR_FIX_MENU, &CDrawApp_LSLView::OnIdrFixMenu)
ON_COMMAND(IDM_DELETE, &CDrawApp_LSLView::OnDelete)
ON_COMMAND(IDM_FIX_TEXT_COLOR, &CDrawApp_LSLView::OnFixTextColor)
ON_COMMAND(IDM_CLEAR, &CDrawApp_LSLView::OnClear)
//ON_WM_RBUTTONDBLCLK()
//ON_WM_RBUTTONUP()
//ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// CDrawApp_LSLView ����/����

CDrawApp_LSLView::CDrawApp_LSLView()
{
	// TODO: �ڴ˴���ӹ������
	m_bDrawFlag = FALSE;
	m_linenum = 0;
	m_rectnum = 0;
	m_ellipsenum = 0;
	m_textnum = 0;
	m_freenum = 0;
	m_selectnum = -1;

	m_logbrush.lbColor = RGB(255, 255, 255);
	m_logbrush.lbHatch = 0;
	m_logbrush.lbStyle = BS_SOLID;

	m_logpen.lopnColor = RGB(0, 0, 0);
	m_logpen.lopnStyle = PS_SOLID;
	m_logpen.lopnWidth.x = 1;

	m_eraser.lopnColor = RGB(255, 255, 255);
	m_eraser.lopnStyle = PS_SOLID;
	m_eraser.lopnWidth.x = 10;

	m_textcolor = RGB(0, 0, 0);
	memset(&m_logfont, 0, sizeof(LOGFONT));
	strcpy_s(m_logfont.lfFaceName, "����");
	m_logfont.lfWeight = 16;
	m_logfont.lfHeight = 16;

	m_tracker.m_nStyle = CRectTracker::resizeInside | CRectTracker::dottedLine;
	m_tracker.m_rect.SetRect(0, 0, 0, 0);
	m_tracker.m_nHandleSize = 5;

	pOld = NULL;
}

CDrawApp_LSLView::~CDrawApp_LSLView()
{
	//delete[] m_lines;
	//delete[] m_rects;
	//delete[] m_ellipses;
	//delete[] m_texts;
	//delete[] m_frees;
}

BOOL CDrawApp_LSLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CDrawApp_LSLView ����

void CDrawApp_LSLView::OnDraw(CDC* pDC)
{
	CDrawApp_LSLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
	//if (pMFram->m_ClearScreen)//������½�ʱ����
	//{
	//	clearScreen();
	//	pMFram->m_ClearScreen = FALSE;
	//	return;
	//}
	
	CDC pMDC ;
	CRect rect;
	CBitmap bitmap ;
	HBITMAP oldBitmap;////////
	CBrush brush;

	GetClientRect(rect);
	pMDC.CreateCompatibleDC(pDC);
	bitmap.CreateCompatibleBitmap(pDC, rect.right, rect.bottom);
	oldBitmap = (HBITMAP)pMDC.SelectObject(&bitmap);
	brush.CreateSolidBrush(RGB(255, 255, 255));
	pMDC.FillRect(rect, &brush);
	pDC->SetROP2(R2_COPYPEN);

	for (int i = 0; i < pDoc->m_Figures.GetSize(); i++)
	{
		if (pDoc->m_Figures[i]->getSelect())
		{
			pDoc->m_Figures[i]->setPtS(m_tracker.m_rect.TopLeft());
			pDoc->m_Figures[i]->setPtE(m_tracker.m_rect.BottomRight());
		}
		pDoc->m_Figures[i]->Draw(&pMDC);
		if (pDoc->m_Figures[i]->getSelect())
		{
			m_tracker.m_rect.SetRect(GetDocument()->m_Figures[i]->getPtS(), GetDocument()->m_Figures[i]->getPtE());
			m_tracker.Draw(&pMDC);
		}
	}
	pDoc->m_FigNumber = pDoc->m_Figures.GetSize();
	pDC->BitBlt(0, 0, rect.right, rect.bottom, &pMDC, 0, 0, SRCCOPY);
	pDC->SelectObject(oldBitmap);

	bitmap.DeleteObject();
	brush.DeleteObject();
	DeleteObject(oldBitmap);
	ReleaseDC(&pMDC);
	pMDC.DeleteDC();
	//delete pMDC;
	//delete bitmap;
	//delete brush;
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CDrawApp_LSLView ���

#ifdef _DEBUG
void CDrawApp_LSLView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawApp_LSLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawApp_LSLDoc* CDrawApp_LSLView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawApp_LSLDoc)));
	return (CDrawApp_LSLDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawApp_LSLView ��Ϣ�������


void CDrawApp_LSLView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CMainFrame *pMain = (CMainFrame *)AfxGetMainWnd();//���MainFrame��ָ��
	//int selectnum = selectWhichFig(point);
	
	BOOL flag = FALSE;
	if (pMain->m_DrawMode == DRAW_MODE_SELECT)
	{
		setSelectNum(selectWhichFig(point));
		if (m_selectnum != -1)
		{
			clearSelect(point);
			GetDocument()->m_Figures[m_selectnum]->setSelect(TRUE);
			m_tracker.m_rect.SetRect(GetDocument()->m_Figures[m_selectnum]->getPtS(), GetDocument()->m_Figures[m_selectnum]->getPtE());
			m_tracker.Track(this, point);
			Invalidate(FALSE);
		}
		else
			clearSelect(point);
	}
	else {
		//if (m_selectnum == -1)//û��ѡ���κ�ͼ��
		{
			//for (int i = 0; i<m_linenum; i++)
			//	if (m_lines[i].getSelect()&& m_tracker.m_rect.PtInRect(point))//�����ʱ��һ��ֱ�߱�ѡ�� �������λ���ڰ�צ���� ��ô�����ڱ߿��ﻭ ��֤��צ�������������
			//	{
			//		m_tracker.Track(this, point);
			//		Invalidate(FALSE);
			//		flag = TRUE;
			//		break;
			//	}
			//if (!flag)//�������λ�ò�������һ����ѡ�е�ֱ�߰�צ�㷶Χ�� �������滭
			//{
		clearSelect(point);
		Invalidate(FALSE);
		/*CMyLine *m_lines;
		CMyRect *m_rects;
		CMyEllipse *m_ellipses;
		CMyFree *m_frees;*/
		switch (pMain->m_DrawMode)
		{
		case DRAW_MODE_LINE:
			m_lines = new CMyLine;
			m_lines->setLogPen(m_logpen);
			m_lines->setPtS(point);
			m_lines->setPtE(point);
			break;
		case DRAW_MODE_RECT:
			m_rects = new CMyRect;
			m_rects->setLogPen(m_logpen);
			m_rects->setLogBrush(m_logbrush);
			m_rects->setPtS(point);
			m_rects->setPtE(point);
			break;
		case DRAW_MODE_ELLIPSE:
			m_ellipses = new CMyEllipse;
			m_ellipses->setLogPen(m_logpen);
			m_ellipses->setLogBrush(m_logbrush);
			m_ellipses->setPtS(point);
			m_ellipses->setPtE(point);
			break;
		case DRAW_MODE_FREE://���ɻ�
			//ptFree = point;
			m_frees = new CMyFree;
			m_frees->setLogPen(m_logpen);
			m_frees->m_pt.Add(point);
			break;
		case DRAW_MODE_ERASER:
			m_frees = new CMyFree;
			m_frees->setLogPen(m_eraser);
			m_frees->m_pt.Add(point);
			break;
		}
		m_bDrawFlag = TRUE;
			//}	
		}
	}
	
	/*else
	{
		
	}*/
	CView::OnLButtonDown(nFlags, point);
}


void CDrawApp_LSLView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CMainFrame *pMain = (CMainFrame *)AfxGetMainWnd();//���MainFrame��ָ��
	switch (pMain->m_DrawMode)
	{
	case DRAW_MODE_LINE:
		//memoryAllocation(m_lines, m_linenum);
		//GetDocument()->AddOneFigure(&m_lines[m_linenum]);
		m_linenum++;
		break;
	case DRAW_MODE_RECT:
		//GetDocument()->AddOneFigure(&m_rects[m_rectnum]);
		m_rectnum++;
		break; 
	case DRAW_MODE_ELLIPSE:
		//GetDocument()->AddOneFigure(&m_ellipses[m_ellipsenum]);
		m_ellipsenum++;
		break;
	case DRAW_MODE_FREE:
	case DRAW_MODE_ERASER:
		//GetDocument()->AddOneFigure(&m_frees[m_freenum]);
		//m_frees = (CMyFree *)memoryAllocationFree(m_frees, m_freenum);//��̬�ڴ����
		//m_frees->getMemoryTimes();
		m_freenum++;
		break;
	}
	Invalidate(FALSE);
	m_bDrawFlag = FALSE;
	GetDocument()->updateCount();
	

	CView::OnLButtonUp(nFlags, point);
}


void CDrawApp_LSLView::OnMouseMove(UINT nFlags, CPoint point)
{
	//CClientDC dc(this);
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_bDrawFlag)
	{
		CMainFrame *pMain = (CMainFrame *)AfxGetMainWnd();//���MainFrame��ָ��
		switch (pMain->m_DrawMode)
		{
		case DRAW_MODE_LINE:
			//m_lines = new CMyLine;
			m_lines->setPtE(point);
			//m_lines = (CMyLine *)memoryAllocation(m_lines, m_linenum);//����֮ǰ��̬�����ڴ�
			GetDocument()->AddOneFigure(m_lines);//���ڻ���ʱ���һ��ͼԪ ���޷���ʾ�켣
			Invalidate(FALSE);
			break;		
		case DRAW_MODE_RECT:
			//m_rects = new CMyRect;
			m_rects->setPtE(point);
			//m_rects = (CMyRect *)memoryAllocation(m_rects, m_rectnum);
			GetDocument()->AddOneFigure(m_rects);
			Invalidate(FALSE);
			break;
		case DRAW_MODE_ELLIPSE:
			//m_ellipses = new CMyEllipse;
			m_ellipses->setPtE(point);
			//m_ellipses = (CMyEllipse *)memoryAllocation(m_ellipses, m_ellipsenum);
			GetDocument()->AddOneFigure(m_ellipses);
			Invalidate(FALSE);
			break;
		case DRAW_MODE_FREE://���ֻ�
		case DRAW_MODE_ERASER://��Ƥ��
			/*dc.MoveTo(ptFree);
			dc.LineTo(point);*/
			//dc.SetPixel(point, RGB(0, 0, 0));
			//ptFree = point;
			//m_frees = new CMyFree;
			m_frees->m_pt.Add(point);			
			GetDocument()->AddOneFigure(m_frees);
			Invalidate(FALSE);
			break;
		}
	}
	CView::OnMouseMove(nFlags, point);
}


void CDrawApp_LSLView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CMainFrame *pMain = (CMainFrame *)AfxGetMainWnd();//���MainFrame��ָ��
	if (pMain->m_DrawMode == DRAW_MODE_TEXT)
	{
		CInputText text;
		
		if (text.DoModal() == IDOK)
		{
			CMyText *m_texts = new CMyText;;			//m_texts = (CMyText *)memoryAllocation(m_texts, m_textnum);//��̬�ڴ����
			m_texts->setPtS(point);
			m_texts->setTextColor(getColorText());
			m_texts->setTextFont(getLogFont());
			m_texts->setText(text.m_inputText);
			GetDocument()->AddOneFigure(m_texts);
			GetDocument()->updateCount();
			m_textnum++;
			Invalidate();
		}
	}
	else
	{
		if (selectWhichFig(point) != -1)
		{
			clearSelect(point);
			GetDocument()->m_Figures[selectWhichFig(point)]->setSelect(TRUE);
			m_tracker.m_rect.SetRect(GetDocument()->m_Figures[selectWhichFig(point)]->getPtS(), GetDocument()->m_Figures[selectWhichFig(point)]->getPtE());
			Invalidate(FALSE);

			//ClientToScreen(&point);������ı�point���ᵼ��ͼԪѡ�з�������
			CMenu m_Menu;
			m_Menu.LoadMenu(IDR_FIX_MENU);//�༭�õĲ˵���Դ
			CMenu *m_SubMenu = m_Menu.GetSubMenu(0);
			switch (GetDocument()->m_Figures[selectWhichFig(point)]->getFigType())
			{
			case DRAW_MODE_LINE:
				m_SubMenu->EnableMenuItem(IDM_FIX_FILL_COLOR, MF_GRAYED);
				m_SubMenu->EnableMenuItem(IDM_FIX_TEXT_COLOR, MF_GRAYED);
				m_SubMenu->EnableMenuItem(IDM_FIX_CHARACTER, MF_GRAYED);
				break;
			case DRAW_MODE_RECT:
			case DRAW_MODE_ELLIPSE:
				m_SubMenu->EnableMenuItem(IDM_FIX_TEXT_COLOR, MF_GRAYED);
				m_SubMenu->EnableMenuItem(IDM_FIX_CHARACTER, MF_GRAYED);
				break;
			case DRAW_MODE_TEXT:
				m_SubMenu->EnableMenuItem(IDM_FIX_FILL_COLOR, MF_GRAYED);
				m_SubMenu->EnableMenuItem(IDM_FIX_BORDER_COLOR, MF_GRAYED);
				m_SubMenu->EnableMenuItem(IDM_FIX_LINE_STYLE, MF_GRAYED);
				m_SubMenu->EnableMenuItem(IDM_FIX_LINE_WIDTH, MF_GRAYED);
				break;
			}
			ClientToScreen(&point);
			m_SubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
		}
		else
		{
			CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
			pMFram->m_DrawMode = DRAW_MODE_SELECT;//�Ҽ��հ״� �����л�ģʽ
		}
	}
	CView::OnRButtonDown(nFlags, point);
}

int CDrawApp_LSLView::selectWhichFig(CPoint pt)
{
	CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
	CArray<int, int&> num;
	CRect rect1;
	int max_num = -1;
	int xmin, xmax, ymin, ymax;
	for (int i = 0; i < GetDocument()->m_Figures.GetSize(); i++)
	{
		if (pMFram->m_DrawMode != DRAW_MODE_FREE)
		{
			
			/*if (GetDocument()->m_Figures[i]->getFigType() == DRAW_MODE_LINE)
			{
				if ((Dis_p2line(GetDocument()->m_Figures[i]->getPtS(), GetDocument()->m_Figures[i]->getPtE(), pt)) <= GetDocument()->m_Figures[i]->getLogPen().lopnWidth.x + 5)
					num.Add(i);
			}
			else*/
			{
				xmin = min(GetDocument()->m_Figures[i]->getPtS().x, GetDocument()->m_Figures[i]->getPtE().x);
				xmax = max(GetDocument()->m_Figures[i]->getPtS().x, GetDocument()->m_Figures[i]->getPtE().x);
				ymin = min(GetDocument()->m_Figures[i]->getPtS().y, GetDocument()->m_Figures[i]->getPtE().y);
				ymax = max(GetDocument()->m_Figures[i]->getPtS().y, GetDocument()->m_Figures[i]->getPtE().y);
				rect1.SetRect(xmin, ymin, xmax, ymax);
				if (rect1.PtInRect(pt))
					num.Add(i);
			}
		}
	}
	if(num.GetSize()==1)
		max_num = num.GetAt(0);
	for (int i = 1; i < num.GetSize(); i++)//ѡ������ Ҳ�����������
	{
		max_num = num.GetAt(0);
		if(num.GetAt(i)>max_num)
			max_num = num.GetAt(i);
	}
	return max_num;
}

BOOL CDrawApp_LSLView::clearSelect(CPoint pt)
{
	for (int i = 0; i < GetDocument()->m_Figures.GetSize(); i++)
	{
		GetDocument()->m_Figures[i]->setSelect(FALSE);
	}
	return TRUE;
}

BOOL CDrawApp_LSLView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_tracker.SetCursor(pWnd, nHitTest))
		return true;
	else
	{
		CMainFrame *pMain = (CMainFrame *)AfxGetMainWnd();//���MainFrame��ָ��
		switch (pMain->m_DrawMode)
		{
		case DRAW_MODE_LINE:
			::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR1));
			return true;
		case DRAW_MODE_RECT:
			::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR2));
			return true;
		case DRAW_MODE_ELLIPSE:
			::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR3));
			return true;
		case DRAW_MODE_TEXT:
			::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR4));
			return true;
		case DRAW_MODE_FREE:
			::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR5));
			return true;
		case DRAW_MODE_ERASER:
			::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR6));
			return true;
		default:
			SetCursor(LoadCursor(NULL, IDC_ARROW));
		}
	}
	return CView::OnSetCursor(pWnd, nHitTest, message);
}



void CDrawApp_LSLView::OnFixBorderColor()
{
	// TODO: �ڴ���������������
	int i = 0;
	for (i = 0; i < GetDocument()->m_Figures.GetSize(); i++)
		if (GetDocument()->m_Figures[i]->getSelect())
			break;

	CChooseColor cc;
	if (cc.DoModal() == IDOK)
	{
		//�õ��������ָ��
		CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
		// ���Viewָ��
		CDrawApp_LSLView *pView = (CDrawApp_LSLView *)pMFram->GetActiveView();
		GetDocument()->m_Figures[i]->setPenColor(cc.getColor());
		Invalidate(FALSE);
	}
}


void CDrawApp_LSLView::OnFixCharacter()
{
	// TODO: �ڴ���������������
	int i = 0;
	for (i = 0; i < GetDocument()->m_Figures.GetSize(); i++)
		if (GetDocument()->m_Figures[i]->getFigType() == DRAW_MODE_TEXT)
			if (GetDocument()->m_Figures[i]->getSelect())
				break;
	CFontDialog fontDlg(&getLogFont());
	if (IDOK == fontDlg.DoModal())     // ��ʾ����Ի��� 
	{
		GetDocument()->m_Figures[i]->setTextFont(*fontDlg.m_cf.lpLogFont);
		Invalidate(FALSE);
	}
}


void CDrawApp_LSLView::OnFixFillColor()
{
	// TODO: �ڴ���������������
	int i = 0;
	for (i = 0; i < GetDocument()->m_Figures.GetSize(); i++)
		if (GetDocument()->m_Figures[i]->getSelect())
			break;

	CChooseColor cc;
	if (cc.DoModal() == IDOK)
	{
		//�õ��������ָ��
		CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
		// ���Viewָ��
		CDrawApp_LSLView *pView = (CDrawApp_LSLView *)pMFram->GetActiveView();
		GetDocument()->m_Figures[i]->setBrushColor(cc.getColor());
		Invalidate(FALSE);
	}
}


void CDrawApp_LSLView::OnFixLineStyle()
{
	// TODO: �ڴ���������������
	int i = 0;
	for (i = 0; i < GetDocument()->m_Figures.GetSize(); i++)
		if (GetDocument()->m_Figures[i]->getSelect())
			break;
	CChoosePenType cpt;
	if(cpt.DoModal()==IDOK)
	{
		GetDocument()->m_Figures[i]->setLineType(cpt.getType());
		Invalidate();
	}
}


void CDrawApp_LSLView::OnFixLineWidth()
{
	// TODO: �ڴ���������������
	int i = 0;
	for (i = 0; i < GetDocument()->m_Figures.GetSize(); i++)
		if (GetDocument()->m_Figures[i]->getSelect())
			break;
	CSetPenWidth csw;
	if (csw.DoModal() == IDOK)
	{
		GetDocument()->m_Figures[i]->setLineWidth(csw.getWidth());
		Invalidate();
	}
}


void CDrawApp_LSLView::OnDelete()
{
	// TODO: �ڴ���������������
	for (int i = 0; i < GetDocument()->m_Figures.GetSize(); i++)
		if (GetDocument()->m_Figures[i]->getSelect())
		{
			GetDocument()->m_Figures.RemoveAt(i);
			break;
		}
	Invalidate(FALSE);
}


void CDrawApp_LSLView::OnFixTextColor()
{
	// TODO: �ڴ���������������
	int i = 0;
	for (i = 0; i < GetDocument()->m_Figures.GetSize(); i++)
		if (GetDocument()->m_Figures[i]->getFigType() == DRAW_MODE_TEXT)
			if (GetDocument()->m_Figures[i]->getSelect())
				break;
	CChooseColor cc;
	if (cc.DoModal() == IDOK)
	{
		GetDocument()->m_Figures[i]->setTextColor(cc.getColor());
		Invalidate(FALSE);
	}
}


VOID CDrawApp_LSLView::clearScreen()
{
	CClientDC dc(this);
	CRect rect;
	CBrush *brush = new CBrush;
	brush->CreateSolidBrush(RGB(255, 255, 255));
	GetClientRect(rect);
	dc.FillRect(rect, brush);
	delete brush;
}

void CDrawApp_LSLView::OnClear()
{
	// TODO: �ڴ���������������
	//clearScreen();
	GetDocument()->m_Figures.RemoveAll();
	Invalidate();
}

//CFig* CDrawApp_LSLView::memoryAllocation(CFig* pFig, int num)
//{
//	CFig *pNew = NULL;
//
//	if (num + 1 == pFig->getMemoryTimes()*MAX_FIG_NUM)//�ٻ�һ�ξͳ���
//	{
//		pFig->setMemoryTimes(pFig->getMemoryTimes() + 1);
//		switch (pFig->getFigType())
//		{
//		case DRAW_MODE_LINE:
//			pNew = new CMyLine[pFig->getMemoryTimes()*MAX_FIG_NUM];
//			break;
//		case DRAW_MODE_RECT:
//			pNew = new CMyRect[pFig->getMemoryTimes()*MAX_FIG_NUM];
//			break;
//		case DRAW_MODE_ELLIPSE:
//			pNew = new CMyEllipse[pFig->getMemoryTimes()*MAX_FIG_NUM];
//			break;
//		case DRAW_MODE_TEXT:
//			pNew = new CMyText[pFig->getMemoryTimes()*MAX_FIG_NUM];
//			break;
//		}
//
//		for (int i = 0; i < (pFig->getMemoryTimes() - 1)*MAX_FIG_NUM; i++)//��ԭ�ڴ���Ķ����ᵽ���ڴ���
//		{
//			*(pNew + i) = *(pFig + i);
//		}
//	}
//	else
//		pNew = pFig;
//
//	return pNew;
//}
//
//CMyFree* CDrawApp_LSLView::memoryAllocationFree(CMyFree* pFig, int num)
//{
//	CMyFree *pNew = NULL;
//	//int n = pFig->getMemoryTimes();
//
//	if (num + 1 == pFig->getMemoryTimes()*MAX_FIG_NUM)//�ٻ�һ�ξͳ���
//	{
//		//n = pFig->getMemoryTimes();
//		pFig->setMemoryTimes(pFig->getMemoryTimes() + 1);
//		//n = pFig->getMemoryTimes();
//		switch (pFig->getFigType())
//		{
//		case DRAW_MODE_FREE:
//			pNew = new CMyFree[pFig->getMemoryTimes()*MAX_FIG_NUM];
//			break;
//		}
//
//		for (int i = 0; i < (pFig->getMemoryTimes() - 1)*MAX_FIG_NUM; i++)//��ԭ�ڴ���Ķ����ᵽ���ڴ���
//		{
//			//*(pNew + i) = *(pFig + i);
//			//pNew->m_pt.Copy(pFig->m_pt);
//			(pNew + i)->m_pt.Copy((pFig + i)->m_pt);
//			(pNew + i)->setMemoryTimes((pFig + i)->getMemoryTimes());//!!!!
//		}
//	}
//	else
//		pNew = pFig;
//	//n = pFig->getMemoryTimes();
//	return pNew;
//}