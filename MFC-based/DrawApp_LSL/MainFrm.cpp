
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "DrawApp_LSL.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//using namespace std;//����ǰ
#include"AllTypeNum.h"
#include"ChooseColor.h"
#include"ChoosePenType.h"
#include"SetPenWidth.h"
#include"DrawApp_LSLDoc.h"
#include"DrawApp_LSLView.h"
#include"Sheet.h"
#include"Eraser.h"
//#include <vector>
//#include"AllHead.h"


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(IDM_ELLIPSE_FIG, &CMainFrame::OnEllipseFig)
	ON_UPDATE_COMMAND_UI(IDM_ELLIPSE_FIG, &CMainFrame::OnUpdateEllipseFig)
	ON_COMMAND(IDM_COLOR_PEN, &CMainFrame::OnColorPen)
//	ON_UPDATE_COMMAND_UI(IDM_COLOR_PEN, &CMainFrame::OnUpdateColorPen)
	ON_COMMAND(IDM_LINE_FIG, &CMainFrame::OnLineFig)
	ON_UPDATE_COMMAND_UI(IDM_LINE_FIG, &CMainFrame::OnUpdateLineFig)
	ON_COMMAND(IDM_RECT_FIG, &CMainFrame::OnRectFig)
	ON_UPDATE_COMMAND_UI(IDM_RECT_FIG, &CMainFrame::OnUpdateRectFig)
	ON_COMMAND(IDM_TEXT_FIG, &CMainFrame::OnTextFig)
	ON_UPDATE_COMMAND_UI(IDM_TEXT_FIG, &CMainFrame::OnUpdateTextFig)
	ON_COMMAND(IDM_TYPE_PEN, &CMainFrame::OnTypePen)
//	ON_UPDATE_COMMAND_UI(IDM_TYPE_PEN, &CMainFrame::OnUpdateTypePen)
	ON_COMMAND(IDM_WIDTH_PEN, &CMainFrame::OnWidthPen)
//	ON_UPDATE_COMMAND_UI(IDM_WIDTH_PEN, &CMainFrame::OnUpdateWidthPen)
ON_COMMAND(IDM_COLOR_BRUSH, &CMainFrame::OnColorBrush)
ON_COMMAND(IDM_TEXT_COLOR, &CMainFrame::OnTextColor)
ON_COMMAND(IDM_TEXT_TYPE, &CMainFrame::OnTextType)
//ON_COMMAND(ID_FILE_OPEN, &CMainFrame::OnFileOpen)
//ON_COMMAND(ID_FILE_SAVE1, &CMainFrame::OnFileSave1)
ON_COMMAND(IDM_USER, &CMainFrame::OnUser)
ON_COMMAND(IDM_FREE_FIG, &CMainFrame::OnFreeFig)
ON_UPDATE_COMMAND_UI(IDM_FREE_FIG, &CMainFrame::OnUpdateFreeFig)
ON_COMMAND(IDM_UNDO, &CMainFrame::OnUndo)
ON_COMMAND(IDM_SELECT_FIG, &CMainFrame::OnSelectFig)
ON_UPDATE_COMMAND_UI(IDM_SELECT_FIG, &CMainFrame::OnUpdateSelectFig)
ON_COMMAND(IDM_ERASER, &CMainFrame::OnEraser)
ON_UPDATE_COMMAND_UI(IDM_ERASER, &CMainFrame::OnUpdateEraser)
ON_COMMAND(IDM_ERASER_SIZE, &CMainFrame::OnEraserSize)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	m_DrawMode = DRAW_MODE_FREE;
	m_PenMode = PEN_MODE_SELECT;
	//m_ClearScreen = FALSE;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: �������Ҫ��ͣ������������ɾ��������
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	//���ñ�������ͼ��

	HICON m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������



void CMainFrame::OnEllipseFig()
{
	// TODO: �ڴ���������������
	m_DrawMode = DRAW_MODE_ELLIPSE;
}


void CMainFrame::OnUpdateEllipseFig(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_DrawMode == DRAW_MODE_ELLIPSE);
}


void CMainFrame::OnColorPen()
{
	// TODO: �ڴ���������������
	m_PenMode = PEN_MODE_COLOR;
	CChooseColor choosecolor;
	if (choosecolor.DoModal() == IDOK)
	{
		//�õ��������ָ��
		CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
		// ���Viewָ��
		CDrawApp_LSLView *pView = (CDrawApp_LSLView *)pMFram->GetActiveView();
		pView->setLogPenColor(choosecolor.getColor());
	}
}

void CMainFrame::OnLineFig()
{
	// TODO: �ڴ���������������
	m_DrawMode = DRAW_MODE_LINE;
}


void CMainFrame::OnUpdateLineFig(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_DrawMode == DRAW_MODE_LINE);
}


void CMainFrame::OnRectFig()
{
	// TODO: �ڴ���������������
	m_DrawMode = DRAW_MODE_RECT;
}


void CMainFrame::OnUpdateRectFig(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_DrawMode == DRAW_MODE_RECT);
}


void CMainFrame::OnTextFig()
{
	// TODO: �ڴ���������������
	m_DrawMode = DRAW_MODE_TEXT;
}


void CMainFrame::OnUpdateTextFig(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_DrawMode == DRAW_MODE_TEXT);
}


void CMainFrame::OnTypePen()
{
	// TODO: �ڴ���������������
	m_PenMode = PEN_MODE_TYPE;
	CChoosePenType ct;
	ct.InitDialog();
	if (ct.DoModal() == IDOK)
	{
		//�õ��������ָ��
		CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
		// ���Viewָ��
		CDrawApp_LSLView *pView = (CDrawApp_LSLView *)pMFram->GetActiveView();
		pView->setLogPenType(ct.getType());
	}
}


void CMainFrame::OnWidthPen()
{
	// TODO: �ڴ���������������
	m_PenMode = PEN_MODE_WIDTH;
	CSetPenWidth sw;
	if (sw.DoModal() == IDOK)
	{
		//�õ��������ָ��
		CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
		// ���Viewָ��
		CDrawApp_LSLView *pView = (CDrawApp_LSLView *)pMFram->GetActiveView();
		pView->setLogPenWidth(sw.getWidth());
	}
}

void CMainFrame::OnColorBrush()
{
	// TODO: �ڴ���������������
	CChooseColor choosecolor;
	if (choosecolor.DoModal() == IDOK)
	{
		//�õ��������ָ��
		CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
		// ���Viewָ��
		CDrawApp_LSLView *pView = (CDrawApp_LSLView *)pMFram->GetActiveView();
		pView->setLogBrushColor(choosecolor.getColor());
	}
}


void CMainFrame::OnTextColor()
{
	// TODO: �ڴ���������������
	CChooseColor cc;
	if (cc.DoModal() == IDOK)
	{
		//�õ��������ָ��
		CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
		// ���Viewָ��
		CDrawApp_LSLView *pView = (CDrawApp_LSLView *)pMFram->GetActiveView();
		pView->setColorText(cc.getColor());
	}
}


void CMainFrame::OnTextType()
{
	// TODO: �ڴ���������������
	//�õ��������ָ��
	CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
	// ���Viewָ��
	CDrawApp_LSLView *pView = (CDrawApp_LSLView *)pMFram->GetActiveView();

	CFontDialog fontDlg(&pView->getLogFont());
	if (IDOK == fontDlg.DoModal())     // ��ʾ����Ի��� 
	{
		pView->setLogFont(*fontDlg.m_cf.lpLogFont);
	}
}


//void CMainFrame::OnFileOpen()
//{
//	// TODO: �ڴ���������������
//	//// ���ù�����   
//	TCHAR szFilter[] = TEXT("Fig Files (*.fig)\0*.fig\0") \
//		TEXT("All Files (*.*)\0*.*\0\0");
//	//// ������ļ��Ի���   
//	//CFileDialog fileDlg(TRUE, _T("fig"), NULL, 0, szFilter, this);
//	//CFile file;
//	//CString strFilePath;
//	//�õ��������ָ��
//	CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
//	//�õ��ĵ���ָ��
//	CDrawApp_LSLDoc* pDoc = (CDrawApp_LSLDoc*)pMFram->GetActiveDocument();
//	//// ��ʾ���ļ��Ի���   
//	//m_ClearScreen = TRUE;
//	//Invalidate();
//	//ClearBuffer();
//	//if (IDOK == fileDlg.DoModal())
//	//{
//	//	strFilePath = fileDlg.GetPathName();
//	//	file.Open(strFilePath, CFile::modeRead);
//	//	file.Read(&pDoc->m_FigNumber, sizeof(UINT));
//	//	if (pDoc->m_FigNumber <= 2000)//��ʱ����Ϊ2000
//	//	{
//	//		file.Read(&pDoc->m_Figures, pDoc->m_FigNumber * sizeof(CFig));
//	//	}
//	//	file.Close();
//	//}
//
//	CFile file;
//	CFileException ex;
//	CFileDialog fileDlg(TRUE);
//	fileDlg.m_ofn.lpstrTitle = "Open File";
//	fileDlg.m_ofn.lpstrFilter = TEXT("Fig Files (*.fig)\0*.fig\0") \
//		TEXT("All Files (*.*)\0*.*\0\0");
//	if (IDOK == fileDlg.DoModal())
//	{		
//		file.Read(&pDoc->m_Figures,100);
//			
//		if (file.Open(fileDlg.GetPathName(), CFile::modeRead,&ex))
//		{
//			if (ex.m_cause == CFileException::endOfFile)
//			{
//				//file.Close();
//				//�ļ���β
//				MessageBox(".");
//			}
//			else
//				file.Read(&pDoc->m_Figures, 100);
//		}
//		file.Close();
//	}
//}

VOID CMainFrame::ClearBuffer()
{
	//�õ��������ָ��
	CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
	//�õ��ĵ���ָ��
	CDrawApp_LSLDoc* pDoc = (CDrawApp_LSLDoc*)pMFram->GetActiveDocument();
	memset(&pDoc->m_Figures, 0, sizeof(pDoc->m_Figures));
	pDoc->m_FigNumber = 0;
}


//void CMainFrame::OnFileSave1()
//{
//	// TODO: �ڴ���������������
//	//�õ��������ָ��
//	CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
//	//�õ��ĵ���ָ��
//	CDrawApp_LSLDoc* pDoc = (CDrawApp_LSLDoc*)pMFram->GetActiveDocument();
//	// ���ù�����   
//	CFile file;
//	TCHAR szFilter[] = TEXT("Fig Files (*.fig)\0*.fig\0")  \
//		TEXT("All Files (*.*)\0*.*\0\0");
//	// ���챣���ļ��Ի���   
//	CFileDialog fileDlg(FALSE, _T("fig"), _T("my"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
//
//
//	CFileDialog FileDlg(FALSE, "Fig", _T("MyFigure"));
//	//FileDlg.m_ofn.lpstrTitle = "Save File";
//	FileDlg.m_ofn.lpstrFilter = TEXT("Fig Files (*.fig)\0*.fig\0")  \
//		TEXT("All Files (*.*)\0*.*\0\0");
//	if (IDOK == FileDlg.DoModal())
//	{
//		CFile File(FileDlg.GetPathName(), CFile::modeCreate | CFile::modeReadWrite);
//		//char szBufData[100] = { "hello word!" };
//		//д���ļ�����,������/0  
//		//File.Write(szBufData, strlen(szBufData));
//		File.Write(&pDoc->m_Figures, pDoc->m_Figures.GetSize());
//		//����д�룬������  
//		File.Flush();
//		//�ļ����������ر�  
//		File.Close();
//	}
//	
//}


void CMainFrame::OnUser()
{
	// TODO: �ڴ���������������
	// �������Ա����   
	CSheet sheet(_T(""));
	// �������ԶԻ���Ϊ�򵼶Ի���   
	sheet.SetWizardMode();
	// ��ģ̬�򵼶Ի���   
	sheet.DoModal();
}


void CMainFrame::OnFreeFig()
{
	// TODO: �ڴ���������������
	m_DrawMode = DRAW_MODE_FREE;
}


void CMainFrame::OnUpdateFreeFig(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_DrawMode == DRAW_MODE_FREE);
}


void CMainFrame::OnUndo()
{
	// TODO: �ڴ���������������
	//�õ��������ָ��
	CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
	//�õ��ĵ���ָ��
	CDrawApp_LSLDoc* pDoc = (CDrawApp_LSLDoc*)pMFram->GetActiveDocument();
	if (pDoc->m_Figures.GetSize() != 0)
	{
		pDoc->m_Figures.RemoveAt(pDoc->m_Figures.GetSize() - 1);
		Invalidate(FALSE);
	}
}


void CMainFrame::OnSelectFig()
{
	// TODO: �ڴ���������������
	m_DrawMode = DRAW_MODE_SELECT;
}


void CMainFrame::OnUpdateSelectFig(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_DrawMode == DRAW_MODE_SELECT);
}


void CMainFrame::OnEraser()
{
	// TODO: �ڴ���������������
	m_DrawMode = DRAW_MODE_ERASER;
}


void CMainFrame::OnUpdateEraser(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_DrawMode == DRAW_MODE_ERASER);
}


void CMainFrame::OnEraserSize()
{
	// TODO: �ڴ���������������
	CEraser er;
	//�õ��������ָ��
	CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
	// ���Viewָ��
	CDrawApp_LSLView *pView = (CDrawApp_LSLView *)pMFram->GetActiveView();
	if (er.DoModal() == IDOK)
	{
		pView->setEraserSize(er.m_size);
	}
}
