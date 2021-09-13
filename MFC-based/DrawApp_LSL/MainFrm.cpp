
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "DrawApp_LSL.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//using namespace std;//放在前
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
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
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
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	//设置标题栏的图标

	HICON m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

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


// CMainFrame 消息处理程序



void CMainFrame::OnEllipseFig()
{
	// TODO: 在此添加命令处理程序代码
	m_DrawMode = DRAW_MODE_ELLIPSE;
}


void CMainFrame::OnUpdateEllipseFig(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_DrawMode == DRAW_MODE_ELLIPSE);
}


void CMainFrame::OnColorPen()
{
	// TODO: 在此添加命令处理程序代码
	m_PenMode = PEN_MODE_COLOR;
	CChooseColor choosecolor;
	if (choosecolor.DoModal() == IDOK)
	{
		//得到主框架类指针
		CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
		// 获得View指针
		CDrawApp_LSLView *pView = (CDrawApp_LSLView *)pMFram->GetActiveView();
		pView->setLogPenColor(choosecolor.getColor());
	}
}

void CMainFrame::OnLineFig()
{
	// TODO: 在此添加命令处理程序代码
	m_DrawMode = DRAW_MODE_LINE;
}


void CMainFrame::OnUpdateLineFig(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_DrawMode == DRAW_MODE_LINE);
}


void CMainFrame::OnRectFig()
{
	// TODO: 在此添加命令处理程序代码
	m_DrawMode = DRAW_MODE_RECT;
}


void CMainFrame::OnUpdateRectFig(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_DrawMode == DRAW_MODE_RECT);
}


void CMainFrame::OnTextFig()
{
	// TODO: 在此添加命令处理程序代码
	m_DrawMode = DRAW_MODE_TEXT;
}


void CMainFrame::OnUpdateTextFig(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_DrawMode == DRAW_MODE_TEXT);
}


void CMainFrame::OnTypePen()
{
	// TODO: 在此添加命令处理程序代码
	m_PenMode = PEN_MODE_TYPE;
	CChoosePenType ct;
	ct.InitDialog();
	if (ct.DoModal() == IDOK)
	{
		//得到主框架类指针
		CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
		// 获得View指针
		CDrawApp_LSLView *pView = (CDrawApp_LSLView *)pMFram->GetActiveView();
		pView->setLogPenType(ct.getType());
	}
}


void CMainFrame::OnWidthPen()
{
	// TODO: 在此添加命令处理程序代码
	m_PenMode = PEN_MODE_WIDTH;
	CSetPenWidth sw;
	if (sw.DoModal() == IDOK)
	{
		//得到主框架类指针
		CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
		// 获得View指针
		CDrawApp_LSLView *pView = (CDrawApp_LSLView *)pMFram->GetActiveView();
		pView->setLogPenWidth(sw.getWidth());
	}
}

void CMainFrame::OnColorBrush()
{
	// TODO: 在此添加命令处理程序代码
	CChooseColor choosecolor;
	if (choosecolor.DoModal() == IDOK)
	{
		//得到主框架类指针
		CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
		// 获得View指针
		CDrawApp_LSLView *pView = (CDrawApp_LSLView *)pMFram->GetActiveView();
		pView->setLogBrushColor(choosecolor.getColor());
	}
}


void CMainFrame::OnTextColor()
{
	// TODO: 在此添加命令处理程序代码
	CChooseColor cc;
	if (cc.DoModal() == IDOK)
	{
		//得到主框架类指针
		CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
		// 获得View指针
		CDrawApp_LSLView *pView = (CDrawApp_LSLView *)pMFram->GetActiveView();
		pView->setColorText(cc.getColor());
	}
}


void CMainFrame::OnTextType()
{
	// TODO: 在此添加命令处理程序代码
	//得到主框架类指针
	CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
	// 获得View指针
	CDrawApp_LSLView *pView = (CDrawApp_LSLView *)pMFram->GetActiveView();

	CFontDialog fontDlg(&pView->getLogFont());
	if (IDOK == fontDlg.DoModal())     // 显示字体对话框 
	{
		pView->setLogFont(*fontDlg.m_cf.lpLogFont);
	}
}


//void CMainFrame::OnFileOpen()
//{
//	// TODO: 在此添加命令处理程序代码
//	//// 设置过滤器   
//	TCHAR szFilter[] = TEXT("Fig Files (*.fig)\0*.fig\0") \
//		TEXT("All Files (*.*)\0*.*\0\0");
//	//// 构造打开文件对话框   
//	//CFileDialog fileDlg(TRUE, _T("fig"), NULL, 0, szFilter, this);
//	//CFile file;
//	//CString strFilePath;
//	//得到主框架类指针
//	CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
//	//得到文档类指针
//	CDrawApp_LSLDoc* pDoc = (CDrawApp_LSLDoc*)pMFram->GetActiveDocument();
//	//// 显示打开文件对话框   
//	//m_ClearScreen = TRUE;
//	//Invalidate();
//	//ClearBuffer();
//	//if (IDOK == fileDlg.DoModal())
//	//{
//	//	strFilePath = fileDlg.GetPathName();
//	//	file.Open(strFilePath, CFile::modeRead);
//	//	file.Read(&pDoc->m_FigNumber, sizeof(UINT));
//	//	if (pDoc->m_FigNumber <= 2000)//暂时假设为2000
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
//				//文件结尾
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
	//得到主框架类指针
	CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
	//得到文档类指针
	CDrawApp_LSLDoc* pDoc = (CDrawApp_LSLDoc*)pMFram->GetActiveDocument();
	memset(&pDoc->m_Figures, 0, sizeof(pDoc->m_Figures));
	pDoc->m_FigNumber = 0;
}


//void CMainFrame::OnFileSave1()
//{
//	// TODO: 在此添加命令处理程序代码
//	//得到主框架类指针
//	CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
//	//得到文档类指针
//	CDrawApp_LSLDoc* pDoc = (CDrawApp_LSLDoc*)pMFram->GetActiveDocument();
//	// 设置过滤器   
//	CFile file;
//	TCHAR szFilter[] = TEXT("Fig Files (*.fig)\0*.fig\0")  \
//		TEXT("All Files (*.*)\0*.*\0\0");
//	// 构造保存文件对话框   
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
//		//写入文件内容,不包含/0  
//		//File.Write(szBufData, strlen(szBufData));
//		File.Write(&pDoc->m_Figures, pDoc->m_Figures.GetSize());
//		//立即写入，不缓冲  
//		File.Flush();
//		//文件操作结束关闭  
//		File.Close();
//	}
//	
//}


void CMainFrame::OnUser()
{
	// TODO: 在此添加命令处理程序代码
	// 创建属性表对象   
	CSheet sheet(_T(""));
	// 设置属性对话框为向导对话框   
	sheet.SetWizardMode();
	// 打开模态向导对话框   
	sheet.DoModal();
}


void CMainFrame::OnFreeFig()
{
	// TODO: 在此添加命令处理程序代码
	m_DrawMode = DRAW_MODE_FREE;
}


void CMainFrame::OnUpdateFreeFig(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_DrawMode == DRAW_MODE_FREE);
}


void CMainFrame::OnUndo()
{
	// TODO: 在此添加命令处理程序代码
	//得到主框架类指针
	CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
	//得到文档类指针
	CDrawApp_LSLDoc* pDoc = (CDrawApp_LSLDoc*)pMFram->GetActiveDocument();
	if (pDoc->m_Figures.GetSize() != 0)
	{
		pDoc->m_Figures.RemoveAt(pDoc->m_Figures.GetSize() - 1);
		Invalidate(FALSE);
	}
}


void CMainFrame::OnSelectFig()
{
	// TODO: 在此添加命令处理程序代码
	m_DrawMode = DRAW_MODE_SELECT;
}


void CMainFrame::OnUpdateSelectFig(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_DrawMode == DRAW_MODE_SELECT);
}


void CMainFrame::OnEraser()
{
	// TODO: 在此添加命令处理程序代码
	m_DrawMode = DRAW_MODE_ERASER;
}


void CMainFrame::OnUpdateEraser(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_DrawMode == DRAW_MODE_ERASER);
}


void CMainFrame::OnEraserSize()
{
	// TODO: 在此添加命令处理程序代码
	CEraser er;
	//得到主框架类指针
	CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
	// 获得View指针
	CDrawApp_LSLView *pView = (CDrawApp_LSLView *)pMFram->GetActiveView();
	if (er.DoModal() == IDOK)
	{
		pView->setEraserSize(er.m_size);
	}
}
