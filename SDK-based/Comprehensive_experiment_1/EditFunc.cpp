#include "EditFig.h"

DRAWCONTEXT gContext;   //图形绘制的整体设置
DRAWDATA gData;
UINT gLineCount = 0;
UINT gRectCount = 0;
UINT gEllipseCount = 0;
UINT gTextCount = 0;
MYLINE gLines[MAX_GRA_ONETYPE];
MYRECT gRects[MAX_GRA_ONETYPE];
MYELLIPSE gEllipses[MAX_GRA_ONETYPE];
MYTEXT gTexts[MAX_GRA_ONETYPE];
HFONT  hFont;
LOGFONT logFont;
UINT iCurrentLine = IDC_SOLID;
UINT LineWidth;
UINT iCurRule = IDC_ADD;
TCHAR NUM1[256], NUM2[256];

VOID InitContext()
{
	gContext.colorText = RGB(0, 0, 0);

	gContext.logPen.lopnColor = RGB(0, 0, 0);
	gContext.logPen.lopnStyle = PS_SOLID;
	gContext.logPen.lopnWidth.x = 1;

	gContext.logBrush.lbColor = RGB(255, 255, 255);
	gContext.logBrush.lbStyle = BS_SOLID;
	gContext.logBrush.lbHatch = 0;

	memset(&gContext.logFont, 0, sizeof(LOGFONT));
	strcpy_s(gContext.logFont.lfFaceName, "宋体");
	gContext.logFont.lfWeight = 16;
	gContext.logFont.lfHeight = 16;
}

VOID AssignOFN(OPENFILENAME *ofn, HWND hWnd)
{
	ofn->lStructSize = sizeof(OPENFILENAME);
	ofn->hwndOwner = hWnd;
	ofn->hInstance = NULL;
	ofn->lpstrFilter = szFileFilter;
	ofn->lpstrCustomFilter = NULL;
	ofn->nMaxCustFilter = 0;
	ofn->nFilterIndex = 0;
	ofn->lpstrFile = NULL;     //调用 GetOpenFileName 函数前设置        
	ofn->nMaxFile = MAX_PATH;
	ofn->lpstrFileTitle = NULL;     //调用 GetOpenFileName 函数前设置
	ofn->nMaxFileTitle = MAX_PATH;
	ofn->lpstrInitialDir = NULL;
	ofn->lpstrTitle = NULL;
	ofn->Flags = 0;        //调用 GetOpenFileName 函数前设置
	ofn->nFileOffset = 0;
	ofn->nFileExtension = 0;
	ofn->lpstrDefExt = TEXT("fig");
	ofn->lCustData = 0L;
	ofn->lpfnHook = NULL;
}

BOOL OpenAndReadFigures(HWND hWnd)
{
	//通过文件对话框选择一个图形文件，并读入数据
	BOOL			bRet;
	OPENFILENAME	ofn;

	AssignOFN(&ofn, hWnd);
	//设置对话框结构变量ofn
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = szFileName;
	ofn.lpstrFileTitle = szFileTitle;
	ofn.Flags = OFN_HIDEREADONLY | OFN_CREATEPROMPT;

	SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(255, 255, 255)));
	InvalidateRect(hWnd, NULL, TRUE);//清屏后再读文件
	ClearBuffer();
	//显示“打开”对话框
	if (GetOpenFileName(&ofn))
	{
		//打开指定文件
		HANDLE hFile = CreateFile(szFileName, GENERIC_READ, FILE_SHARE_READ,
			NULL, OPEN_EXISTING, 0, NULL);
		if (hFile != INVALID_HANDLE_VALUE)
		{
			DWORD dwRead1 = 0;
			DWORD dwRead2 = 0;
			DWORD dwRead3 = 0;
			DWORD dwRead4 = 0;
			//line
			ReadFile(hFile, &gLineCount, sizeof(UINT), &dwRead1, NULL);
			if (gLineCount <= MAX_GRA_ONETYPE)//图形个数越界
				ReadFile(hFile, &gLines, gLineCount * sizeof(MYLINE), &dwRead1, NULL);
			else
				bRet = FALSE;
			//rect
			ReadFile(hFile, &gRectCount, sizeof(UINT), &dwRead2, NULL);
			if (gRectCount <= MAX_GRA_ONETYPE)//图形个数越界
				ReadFile(hFile, &gRects, gRectCount * sizeof(MYRECT), &dwRead2, NULL);
			else
				bRet = FALSE;
			//ellipse
			ReadFile(hFile, &gEllipseCount, sizeof(UINT), &dwRead3, NULL);
			if (gEllipseCount <= MAX_GRA_ONETYPE)//图形个数越界
				ReadFile(hFile, &gEllipses, gEllipseCount * sizeof(MYELLIPSE), &dwRead3, NULL);
			else
				bRet = FALSE;
			//text
			ReadFile(hFile, &gTextCount, sizeof(UINT), &dwRead4, NULL);
			if (gTextCount <= MAX_GRA_ONETYPE)//图形个数越界
				ReadFile(hFile, &gTexts, gTextCount * sizeof(MYTEXT), &dwRead4, NULL);
			else
				bRet = FALSE;

			bFileChange = FALSE;
			CloseHandle(hFile);
		}
		else
		{
			MessageBox(hWnd, TEXT("打开指定文件操作失败"),
				TEXT("文件操作演示程序"), MB_OK | MB_ICONERROR);
			szFileName[0] = '\0';
			szFileTitle[0] = '\0';
			return FALSE;
		}
	}
	return TRUE;
}

BOOL SaveFigures(HWND hWnd)
{
	OPENFILENAME  ofn;
	AssignOFN(&ofn, hWnd);
	//通过文件对话框选择一个图形文件，将图形数据保存到该文件
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = szFileName;
	ofn.lpstrFileTitle = szFileTitle;
	ofn.Flags = OFN_OVERWRITEPROMPT;

	//显示“另存为”对话框
	if (GetSaveFileName(&ofn))
	{
		//打开指定文件
		HANDLE hFile = CreateFile(szFileName, GENERIC_WRITE, 0,
			NULL, CREATE_ALWAYS, 0, NULL);
		if (hFile != INVALID_HANDLE_VALUE)
		{
			DWORD dwWriten1 = 0;
			DWORD dwWriten2 = 0;
			DWORD dwWriten3 = 0;
			DWORD dwWriten4 = 0;
			//line
			WriteFile(hFile, &gLineCount, sizeof(UINT), &dwWriten1, NULL);
			WriteFile(hFile, &gLines, gLineCount * sizeof(MYLINE), &dwWriten1, NULL);
			//rect
			WriteFile(hFile, &gRectCount, sizeof(UINT), &dwWriten2, NULL);
			WriteFile(hFile, &gRects, gRectCount * sizeof(MYRECT), &dwWriten2, NULL);
			//ellipse
			WriteFile(hFile, &gEllipseCount, sizeof(UINT), &dwWriten3, NULL);
			WriteFile(hFile, &gEllipses, gEllipseCount * sizeof(MYELLIPSE), &dwWriten3, NULL);
			//text
			WriteFile(hFile, &gTextCount, sizeof(UINT), &dwWriten4, NULL);
			WriteFile(hFile, &gTexts, gTextCount * sizeof(MYTEXT), &dwWriten4, NULL);

			CloseHandle(hFile);
		}
		else
		{
			MessageBox(hWnd, TEXT("打开指定文件操作失败"),
				TEXT("文件操作演示程序"), MB_OK | MB_ICONERROR);
			szFileName[0] = '\0';
			szFileTitle[0] = '\0';
		}
	}
	bFileChange = FALSE;
	return TRUE;
}

UINT QuerySaveFile(HWND hWnd, TCHAR * szTitleName)
{
	TCHAR szBuffer[MAX_PATH];
	int iResponse;

	wsprintf(szBuffer, TEXT("文件 %s 的内容已经更改，是否需要保存?"),
		szTitleName[0] ? szTitleName : UNTITLED);

	iResponse = MessageBox(hWnd, szBuffer, TEXT("文件操作演示程序"),
		MB_YESNOCANCEL | MB_ICONQUESTION);

	if (iResponse == IDYES)
		if (!SendMessage(hWnd, WM_COMMAND, IDM_SAVE, 0))
			iResponse = IDCANCEL;

	return (iResponse);
}

BOOL AddOneLine(POINT ptS, POINT ptE, LOGPEN hPen)
{
	MYLINE l;
	l.ptStart = ptS;
	l.ptEnd = ptE;
	l.logPen = hPen;
	if (gLineCount < MAX_GRA_ONETYPE)
	{
		gLines[gLineCount++] = l;
		return TRUE;
	}
	return FALSE;
}

VOID DrawAllLines(HDC hdc)
{
	if (gLineCount != 0)
		for (UINT i = 0; i < gLineCount; i++)
		{
			DrawOneLine(hdc, gLines[i].ptStart.x, gLines[i].ptStart.y, gLines[i].ptEnd.x, gLines[i].ptEnd.y, gLines[i].logPen);
		}
}
VOID DrawOneLine(HDC hdc, UINT left, UINT top, UINT right, UINT bottom, LOGPEN logPen)
{
	HPEN hPen = NULL, hPenOld = NULL;
	hPen = CreatePenIndirect(&logPen);
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	MoveToEx(hdc, left, top, NULL);
	LineTo(hdc, right, bottom);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}


BOOL AddOneRect(POINT ptS, POINT ptE, LOGPEN hPen, LOGBRUSH logBrush)
{
	MYRECT r;
	r.ptStart = ptS;
	r.ptEnd = ptE;
	r.logPen =hPen;
	r.logBrush = logBrush;
	if (gRectCount < MAX_GRA_ONETYPE)
	{
		gRects[gRectCount++] = r;
		return TRUE;
	}
	return FALSE;
}
BOOL ChangeOneRectLocation(UINT left, UINT top, UINT right, UINT bottom, UINT index)
{
	gRects[index].ptStart.x = left;
	gRects[index].ptStart.y = top;
	gRects[index].ptEnd.x = right;
	gRects[index].ptEnd.y = bottom;
	return TRUE;
}
BOOL ChangeOneEllipseLocation(UINT left, UINT top, UINT right, UINT bottom, UINT index)
{
	gEllipses[index].ptStart.x = left;
	gEllipses[index].ptStart.y = top;
	gEllipses[index].ptEnd.x = right;
	gEllipses[index].ptEnd.y = bottom;
	return TRUE;
}
BOOL ChangeOneLineLocation(UINT left, UINT top, UINT right, UINT bottom,  UINT index)
{
	gLines[index].ptStart.x = left;
	gLines[index].ptStart.y = top;
	gLines[index].ptEnd.x = right;
	gLines[index].ptEnd.y = bottom;
	return TRUE;
}
BOOL ChangeOneTextLocation(UINT left, UINT top, UINT right, UINT bottom,UINT index)
{
	gTexts[index].pt.x = left;
	gTexts[index].pt.y = top;
	return TRUE;
}
BOOL AddOneEllipse(POINT ptS, POINT ptE, LOGPEN hPen, LOGBRUSH logBrush)
{
	MYELLIPSE e;
	e.ptStart = ptS;
	e.ptEnd = ptE;
	e.logPen = hPen;
	e.logBrush = logBrush;
	if (gEllipseCount < MAX_GRA_ONETYPE)
	{
		gEllipses[gEllipseCount++] = e;
		return TRUE;
	}
	return FALSE;
}
BOOL AddOneText(POINT ptS,TCHAR pBuffer[1024],LOGFONT logFont, COLORREF colorText)
{
	MYTEXT t;
	t.color = colorText;
	t.logFont = logFont;
	t.pt = ptS;
	strcpy_s(t.pBuffer, pBuffer);
	if (gTextCount < MAX_GRA_ONETYPE)
	{
		gTexts[gTextCount++] = t;
		return TRUE;
	}
	return FALSE;
}
VOID DrawAllRects(HDC hdc)
{
	if (gRectCount != 0)
		for (UINT i = 0; i < gRectCount; i++)
		{
			HPEN hPen = NULL, hPenOld = NULL;
			HBRUSH hBrush = NULL, hBrushOld = NULL;
			hPen = CreatePenIndirect(&gRects[i].logPen);
			hBrush = CreateBrushIndirect(&gRects[i].logBrush);
			hPenOld = (HPEN)SelectObject(hdc, hPen);
			hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
			
			Rectangle(hdc, gRects[i].ptStart.x, gRects[i].ptStart.y,
				gRects[i].ptEnd.x, gRects[i].ptEnd.y);

			SelectObject(hdc, hPenOld);
			SelectObject(hdc, hBrushOld);
			DeleteObject(hPen);
			DeleteObject(hBrush);
		}
}
VOID DrawAllEllipses(HDC hdc)
{
	if (gEllipseCount != 0)
		for (UINT i = 0; i < gEllipseCount; i++)
		{
			HPEN hPen = NULL, hPenOld = NULL;
			HBRUSH hBrush = NULL, hBrushOld = NULL;
			hPen = CreatePenIndirect(&gEllipses[i].logPen);
			hBrush = CreateBrushIndirect(&gEllipses[i].logBrush);
			hPenOld = (HPEN)SelectObject(hdc, hPen);
			hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);

			Ellipse(hdc, gEllipses[i].ptStart.x, gEllipses[i].ptStart.y,
				gEllipses[i].ptEnd.x, gEllipses[i].ptEnd.y);

			SelectObject(hdc, hPenOld);
			SelectObject(hdc, hBrushOld);
			DeleteObject(hPen);
			DeleteObject(hBrush);
		}
}
VOID DrawAllTexts(HDC hdc)
{
	if (gTextCount != 0)
		for (UINT i = 0; i < gTextCount; i++)
		{
			if (hFont)
				DeleteObject(hFont);
			hFont = CreateFontIndirect(&gTexts[i].logFont);
			if (hFont) SelectObject(hdc, hFont);              //选用逻辑字体
			SetTextColor(hdc, gTexts[i].color);
			TextOut(hdc, gTexts[i].pt.x, gTexts[i].pt.y, gTexts[i].pBuffer, strlen(gTexts[i].pBuffer));
		}
}
VOID ClearBuffer()
{
	if (gLineCount != 0)
	{
		memset(gLines, 0, sizeof(gLines));
		gLineCount = 0;
	}
	if (gRectCount != 0)
	{
		memset(gRects, 0, sizeof(gRects));
		gRectCount = 0;
	}
	if (gEllipseCount != 0)
	{
		memset(gEllipses, 0, sizeof(gEllipses));
		gEllipseCount = 0;
	}
	if (gTextCount != 0)
	{
		memset(gTexts, 0, sizeof(gTexts));
		gTextCount = 0;
	}
}

BOOL CALLBACK InputDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		SetDlgItemText(hDlg, IDC_EDIT1, "");
		return FALSE;

	case WM_COMMAND:
		//处理对话框中各控件通知消息
		switch (LOWORD(wParam))
		{
		case IDOK:
			//响应"确认"按钮
			GetDlgItemText(hDlg, IDC_EDIT1, g_EditInput, 1024);

			//关闭对话框
			EndDialog(hDlg, TRUE);      //关闭对话框
			return TRUE;

		case IDCANCEL:
			//响应"取消"按钮，直接关闭对话框
			EndDialog(hDlg, FALSE);
			return TRUE;
		}
		break;
	}
	return FALSE;
};//结束 InputDlgProc

LOGFONT MyChooseFont(HWND hWnd)
{
	CHOOSEFONT   cf;
	LOGFONT      logfont;

	//初始化结构 cf

	GetObject(GetStockObject(SYSTEM_FONT), sizeof(LOGFONT),
		(PTSTR)&logfont);        //初始化结构 logfont 字体的参数比较多 所以使用GetObject进行初始化 而logpen等直接输参数即可

	//初始化结构 cf
	cf.lStructSize = sizeof(CHOOSEFONT);
	cf.hwndOwner = hWnd;
	cf.hDC = NULL;
	cf.lpLogFont = &logfont;
	cf.iPointSize = 0;
	cf.Flags = CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS | CF_EFFECTS;
	cf.rgbColors = 0;
	cf.lCustData = 0;
	cf.lpfnHook = NULL;
	cf.lpTemplateName = NULL;
	cf.hInstance = NULL;
	cf.lpszStyle = NULL;
	cf.nFontType = 0;
	cf.nSizeMin = 0;
	cf.nSizeMax = 0;

	if (ChooseFont(&cf))
		return logfont;
}
COLORREF MyChooseColor(HWND hWnd)
{
	CHOOSECOLOR  cc;
	COLORREF     crCustomColors[16];
	COLORREF     crText = RGB(0, 0, 0);
	//初始化结构 cc
	cc.lStructSize = sizeof(CHOOSECOLOR);
	cc.hwndOwner = hWnd;
	cc.hInstance = NULL;
	cc.rgbResult = RGB(0, 0, 0);
	cc.lpCustColors = crCustomColors;
	cc.Flags = CC_RGBINIT | CC_FULLOPEN;
	cc.lCustData = 0;
	cc.lpfnHook = NULL;
	cc.lpTemplateName = NULL;

	if (ChooseColor(&cc))
	{
		crText = cc.rgbResult;
	}
	return crText;
}
UINT SelectImag(POINT ptEnd)
{
	UINT flagmode = 0;
	//rect
	for (UINT i = 0; i < gRectCount; i++)
	{
		if (ptEnd.x >= min(gRects[i].ptStart.x, gRects[i].ptEnd.x)&&ptEnd.x <= max(gRects[i].ptStart.x, gRects[i].ptEnd.x) &&ptEnd.y >= min(gRects[i].ptStart.y, gRects[i].ptEnd.y) &&ptEnd.y <= max(gRects[i].ptStart.y, gRects[i].ptEnd.y))
			flagmode = RECTS;
	}
	//ellipse
	for (UINT i = 0; i < gEllipseCount; i++)
	{
		if (ptEnd.x >= min(gEllipses[i].ptStart.x, gEllipses[i].ptEnd.x)&&ptEnd.x <= max(gEllipses[i].ptStart.x, gEllipses[i].ptEnd.x) &&ptEnd.y >= min(gEllipses[i].ptStart.y, gEllipses[i].ptEnd.y) &&ptEnd.y <= max(gEllipses[i].ptStart.y, gEllipses[i].ptEnd.y))
			flagmode = ELLIPSES;
	}
	//text
	for (UINT i = 0; i < gTextCount; i++)
	{
		if (ptEnd.x >= gTexts[i].pt.x&&ptEnd.x <= gTexts[i].pt.x + strlen(gTexts[i].pBuffer)*15 && ptEnd.y >= gTexts[i].pt.y&&ptEnd.y <= gTexts[i].pt.y + abs(gTexts[i].logFont.lfHeight))
			flagmode = TEXTS;
	}
	//line
	for (UINT i = 0; i < gLineCount; i++)
	{
		if (ptEnd.x >= min(gLines[i].ptStart.x, gLines[i].ptEnd.x)&&ptEnd.x <= max(gLines[i].ptStart.x, gLines[i].ptEnd.x) &&ptEnd.y >= min(gLines[i].ptStart.y, gLines[i].ptEnd.y) &&ptEnd.y <= max(gLines[i].ptStart.y, gLines[i].ptEnd.y))
			flagmode = LINES;
	}
	return flagmode;
}

UINT ReturnFigIndex(UINT type , POINT ptEnd)
{
	switch (type)
	{
	case RECTS:
		for (UINT i = 0; i < gRectCount; i++)
		{
			if (ptEnd.x >= min(gRects[i].ptStart.x, gRects[i].ptEnd.x) && ptEnd.x <= max(gRects[i].ptStart.x, gRects[i].ptEnd.x) && ptEnd.y >= min(gRects[i].ptStart.y, gRects[i].ptEnd.y) && ptEnd.y <= max(gRects[i].ptStart.y, gRects[i].ptEnd.y))
				return i;
		}
		break;
	case ELLIPSES:
		for (UINT i = 0; i < gEllipseCount; i++)
		{
			if (ptEnd.x >= min(gEllipses[i].ptStart.x, gEllipses[i].ptEnd.x) && ptEnd.x <= max(gEllipses[i].ptStart.x, gEllipses[i].ptEnd.x) && ptEnd.y >= min(gEllipses[i].ptStart.y, gEllipses[i].ptEnd.y) && ptEnd.y <= max(gEllipses[i].ptStart.y, gEllipses[i].ptEnd.y))
				return i;
		}
		break;
	case LINES:
		for (UINT i = 0; i < gLineCount; i++)
		{
			if (ptEnd.x >= min(gLines[i].ptStart.x, gLines[i].ptEnd.x) && ptEnd.x <= max(gLines[i].ptStart.x, gLines[i].ptEnd.x) && ptEnd.y >= min(gLines[i].ptStart.y, gLines[i].ptEnd.y) && ptEnd.y <= max(gLines[i].ptStart.y, gLines[i].ptEnd.y))
				return i;
		}
		break;
	case TEXTS:
		for (UINT i = 0; i < gTextCount; i++)
		{
			if (ptEnd.x >= gTexts[i].pt.x&&ptEnd.x <= gTexts[i].pt.x + strlen(gTexts[i].pBuffer) * 15 && ptEnd.y >= gTexts[i].pt.y&&ptEnd.y <= gTexts[i].pt.y + abs(gTexts[i].logFont.lfHeight))
				return i;
		}
		break;
	default:
		return 0;
	}
}
BOOL ChangeOneRectSize(UINT left, UINT top, UINT right, UINT bottom, UINT index)
{
	gRects[index].ptStart.x = left;
	gRects[index].ptStart.y = top;
	gRects[index].ptEnd.x = right;
	gRects[index].ptEnd.y = bottom;
	return TRUE;
}
BOOL ChangeOneEllipseSize(UINT left, UINT top, UINT right, UINT bottom, UINT index)
{
	gEllipses[index].ptStart.x = left;
	gEllipses[index].ptStart.y = top;
	gEllipses[index].ptEnd.x = right;
	gEllipses[index].ptEnd.y = bottom;
	return TRUE;
}
BOOL ChangeOneLineSize(UINT left, UINT top, UINT right, UINT bottom, UINT index)
{
	gLines[index].ptStart.x = left;
	gLines[index].ptStart.y = top;
	gLines[index].ptEnd.x = right;
	gLines[index].ptEnd.y = bottom;
	return TRUE;
}
VOID DeleteOneRect(UINT index)   //删除下标为index的图元
{
	UINT i = 0;
	for (i = index; i < gRectCount; i++)
	{
		gRects[i] = gRects[i + 1];
	}
	gRects[i].ptEnd.x = 0;
	gRects[i].ptEnd.y = 0;
	gRects[i].ptStart.x = 0;
	gRects[i].ptStart.y = 0;
	gRectCount--;
}
VOID DeleteOneLine(UINT index)   //删除下标为index的图元
{
	UINT i = 0;
	for (i = index; i < gLineCount; i++)
	{
		gLines[i] = gLines[i + 1];
	}
	gLines[i].ptEnd.x = 0;
	gLines[i].ptEnd.y = 0;
	gLines[i].ptStart.x = 0;
	gLines[i].ptStart.y = 0;
	gLineCount--;
}
VOID DeleteOneEllipse(UINT index)   //删除下标为index的图元
{
	UINT i = 0;
	for (i = index; i < gEllipseCount; i++)
	{
		gEllipses[i] = gEllipses[i + 1];
	}
	gEllipses[i].ptEnd.x = 0;
	gEllipses[i].ptEnd.y = 0;
	gEllipses[i].ptStart.x = 0;
	gEllipses[i].ptStart.y = 0;
	gEllipseCount--;
}
VOID DeleteOneText(UINT index)   //删除下标为index的图元
{
	UINT i = 0;
	for (i = index; i < gTextCount; i++)
	{
		gTexts[i] = gTexts[i + 1];
	}
	gTexts[i].pt.x = 0;
	gTexts[i].pt.y = 0;
	strcpy_s(gTexts[i].pBuffer, "\0");
	gTextCount--;
}
BOOL CALLBACK InputLineProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static UINT iLine;
	//LineWidth = 0;
	switch (message)
	{
	case WM_INITDIALOG:
		iLine = iCurrentLine;
		//SetDlgItemText(hDlg, IDC_WIDTH, "");
		CheckRadioButton(hDlg, IDC_SOLID, IDC_DASHDOTDOT, iLine);
		return FALSE;

	case WM_COMMAND:
		//处理对话框中各控件通知消息
		switch (LOWORD(wParam))
		{
		case IDOK:
			//响应"确认"按钮
			iCurrentLine = iLine;
			//LineWidth = GetDlgItemInt(hDlg, IDC_WIDTH, NULL, FALSE);

			//关闭对话框
			EndDialog(hDlg, TRUE);      //关闭对话框
			return TRUE;

		case IDCANCEL:
			//响应"取消"按钮，直接关闭对话框
			EndDialog(hDlg, FALSE);
			return TRUE;

		case IDC_SOLID:
		case IDC_DASH:
		case IDC_DOT:
		case IDC_DASHDOT:
		case IDC_DASHDOTDOT:
			iLine = LOWORD(wParam);
			CheckRadioButton(hDlg, IDC_SOLID, IDC_DASHDOTDOT, iLine);
			return TRUE;
		}
		break;
	}
	return FALSE;
}
BOOL CALLBACK ComputeProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static UINT rules;
	switch (message)
	{
	case WM_INITDIALOG:
		rules = iCurRule;
		SetDlgItemText(hDlg, IDC_NUM1, "0.00");
		SetDlgItemText(hDlg, IDC_NUM2, "0.00");
		CheckRadioButton(hDlg, IDC_ADD, IDC_DIV, IDC_ADD);
		return FALSE;

	case WM_COMMAND:
		//处理对话框中各控件通知消息
		switch (LOWORD(wParam))
		{
		case IDOK:
			//响应"确认"按钮
			iCurRule = rules;
			GetDlgItemText(hDlg, IDC_NUM1, NUM1, 256);
			GetDlgItemText(hDlg, IDC_NUM2, NUM2, 256);
			//GetDlgItemText(hDlg, IDC_EDIT1, g_EditInput, 1024);
			//关闭对话框
			EndDialog(hDlg, TRUE);    
			return TRUE;

		case IDCANCEL:
			//响应"取消"按钮，直接关闭对话框
			EndDialog(hDlg, FALSE);
			return TRUE;

		case IDC_ADD:
		case IDC_SUB:
		case IDC_MULTI:
		case IDC_DIV:
			rules = LOWORD(wParam);
			CheckRadioButton(hDlg, IDC_SOLID, IDC_DASHDOTDOT, rules);
			return TRUE;
		}
		break;
	}
	return FALSE;
}