#pragma once
#include <windows.h>
#include <windowsx.h>
#include "resource.h"
#include <atlstr.h>//与显示浮点数相关

#define SIMPLE_GRA_LINE 1
#define SIMPLE_GRA_RECT 2
#define SIMPLE_GRA_ELLIPSE 3
#define SIMPLE_GRA_TEXT 4

#define MAX_GRA_ONETYPE 1024

#define UNTITLED  TEXT ("无标题")

#define LINES 100
#define RECTS 101
#define ELLIPSES 102
#define TEXTS 103

typedef struct tagDRAWDATA
{
	int		iSelectionFunc;
	int		iSelectionPen;
	int		iSelectionBrush;
	HPEN	hRedDashdotPen;
	HPEN	hBlueSolidPen;
	int		cxBeginPoint;
	int		cyBeginPoint;
	int		cxCurrPoint;
	int		cyCurrPoint;
	BOOL	bDrawing;
}DRAWDATA;

typedef struct tagDrawContext {
	LOGPEN logPen;
	LOGBRUSH logBrush;
	LOGFONT logFont;
	COLORREF colorText;
}DRAWCONTEXT;

typedef struct tagMyOutLine {
	POINT ptStart;
	POINT ptEnd;
	LOGPEN logPen;
}MYOUTLINE, *PMYOUTLINE;

typedef struct tagMyLine :public MYOUTLINE {
}MYLINE, *PMYLINE;

typedef struct tagMyRect :public MYOUTLINE {
	LOGBRUSH logBrush;
}MYRECT, *PMYRECT;

typedef struct tagMyEllipse :public MYOUTLINE {
	LOGBRUSH logBrush;
}MYELLIPSE, *PMYELLIPSE;

typedef struct tagMyText
{
	POINT pt;
	COLORREF color;
	LOGFONT logFont;
	TCHAR pBuffer[1024];		// 指针方式文本缓冲区，根据输入文本长度申请内存
}MYTEXT, *PMYTEXT;

//变量声明
extern DRAWCONTEXT gContext;   //图形绘制的整体设置
extern DRAWDATA gData;
extern UINT gLineCount;
extern UINT gRectCount;
extern UINT gEllipseCount;
extern UINT gTextCount;
extern MYLINE gLines[MAX_GRA_ONETYPE];
extern MYRECT gRects[MAX_GRA_ONETYPE];
extern MYELLIPSE gEllipses[MAX_GRA_ONETYPE];
extern MYTEXT gTexts[MAX_GRA_ONETYPE];

extern BOOL   bFileChange;
extern TCHAR  szFileFilter[];
extern TCHAR  szFileName[MAX_PATH], szFileTitle[MAX_PATH];
extern TCHAR g_EditInput[1024];
extern UINT LineWidth;
extern HFONT  hFont;
extern LOGFONT logFont;
extern UINT iCurrentLine;
extern TCHAR NUM1[256], NUM2[256];
extern UINT iCurRule;

//函数声明
VOID InitContext();
VOID ClearBuffer();

VOID DrawAllLines(HDC hdc);
VOID DrawOneLine(HDC hdc, UINT left, UINT top, UINT right, UINT bottom, LOGPEN logPen);
VOID DrawAllRects(HDC hdc);
VOID DrawAllEllipses(HDC hdc);
VOID DrawAllTexts(HDC hdc);

VOID DeleteOneRect(UINT index);
VOID DeleteOneLine(UINT index);
VOID DeleteOneEllipse(UINT index);
VOID DeleteOneText(UINT index);

BOOL AddOneLine(POINT ptS, POINT ptE, LOGPEN hPen);
BOOL AddOneRect(POINT ptS, POINT ptE, LOGPEN hPen, LOGBRUSH logBrush);
BOOL AddOneEllipse(POINT ptS, POINT ptE, LOGPEN hPen, LOGBRUSH logBrush);
BOOL AddOneText(POINT ptS, TCHAR pBuffer[1024], LOGFONT logFont, COLORREF colorText);

BOOL ChangeOneRectLocation(UINT left, UINT top, UINT right, UINT bottom, UINT index);
BOOL ChangeOneEllipseLocation(UINT left, UINT top, UINT right, UINT bottom, UINT index);
BOOL ChangeOneLineLocation(UINT left, UINT top, UINT right, UINT bottom, UINT index);
BOOL ChangeOneTextLocation(UINT left, UINT top, UINT right, UINT bottom, UINT index);

BOOL ChangeOneRectSize(UINT left, UINT top, UINT right, UINT bottom, UINT index);
BOOL ChangeOneEllipseSize(UINT left, UINT top, UINT right, UINT bottom, UINT index);
BOOL ChangeOneLineSize(UINT left, UINT top, UINT right, UINT bottom, UINT index);

LOGFONT MyChooseFont(HWND hWnd);
COLORREF MyChooseColor(HWND hWnd);

VOID AssignOFN(OPENFILENAME *ofn, HWND hWnd);
BOOL OpenAndReadFigures(HWND hWnd);
BOOL SaveFigures(HWND hWnd);
UINT QuerySaveFile(HWND hWnd, TCHAR * szTitleName);

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK InputDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK InputLineProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ComputeProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

UINT SelectImag(POINT ptEnd);
UINT ReturnFigIndex(UINT type, POINT ptEnd);