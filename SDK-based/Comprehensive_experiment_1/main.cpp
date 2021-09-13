/*******************************************************************
���ܣ�����ͼ�α༭��
********************************************************************/
#include "EditFig.h"

TCHAR g_EditInput[1024];
TCHAR g_EditLine[1024];
BOOL  bFileChange = FALSE;
TCHAR szFileFilter[] = TEXT("Fig Files (*.fig)\0*.fig\0")  \
TEXT("All Files (*.*)\0*.*\0\0");
TCHAR szFileName[MAX_PATH] = "", szFileTitle[MAX_PATH] = "";//û��static��ʱ���Լ���ʼ��
POINT ptBegin, ptEnd, ptrEnd;
BOOL  bDrawing = FALSE;
COLORREF crText;
COLORREF crPen;
COLORREF crBrush, crBackBrush;
COLORREF oldColor;

int WINAPI WinMain(HINSTANCE hInstance,         //��ǰʵ�����
	HINSTANCE hPrevInstance,     //ǰһ��ʵ�����
	PSTR szCmdLine,              //�������ַ�
	int iCmdShow)                //������ʾ��ʽ
{
	MSG msg;
	static TCHAR szAppName[] = TEXT("EasyFigEdit");  //Ӧ�ó�������
	HWND hwnd;                                    //���ھ��
	WNDCLASS wcMainWnd;                           //������ṹ
	ATOM a;
	HACCEL hAccel;

	wcMainWnd.style = CS_VREDRAW | CS_HREDRAW;
	wcMainWnd.lpfnWndProc = WinProc;
	wcMainWnd.cbClsExtra = 0;
	wcMainWnd.cbWndExtra = 0;
	wcMainWnd.hInstance = hInstance;
	wcMainWnd.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcMainWnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcMainWnd.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcMainWnd.lpszMenuName = MAKEINTRESOURCE(IDR_MAIN_MENU);
	wcMainWnd.lpszClassName = szAppName;

	//ע�ᴰ����
	a = RegisterClass(&wcMainWnd);

	if (!a)
	{
		MessageBox(NULL, TEXT("ע�ᴰ����ʧ�ܣ�"), szAppName,
			MB_ICONERROR);
		return 0;
	}
	//����������
	hwnd = CreateWindow(szAppName, 						//����������
		TEXT("����ͼ�α༭��--���ߣ�¬����"),			//���ڱ���
		WS_OVERLAPPEDWINDOW,				//���ڷ��
		80,									//����λ�õ�x����
		100,								//����λ�õ�y����
		1100,								//���ڵĿ��
		700,								//���ڵĸ߶�
		NULL,								//�����ھ��
		NULL,								//�˵����
		hInstance,							//Ӧ�ó���ʵ�����
		NULL);								//���ڴ�������ָ��

	if (!hwnd) return FALSE;

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));
	if (!hAccel)
	{
		MessageBeep(0);
		return FALSE;
	}

	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(hwnd, hAccel, &msg))//���ټ�
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hWndEdit;
	HMENU       hMenu = NULL, hMenu1 = NULL, hTackMenu = NULL, hSrcMenu = NULL;
	HDC         hdc;
	PAINTSTRUCT ps;
	RECT        rect;
	static BOOL	first = TRUE, first1 = TRUE;
	static int  iSelectionFig = IDM_LINE;
	static int  flagdraw;
	static int  flagmode;
	static LOGPEN logPen, LogBackPen;
	static HPEN hPen, hOldPen, hBackPen;
	static LOGBRUSH logBrush, LogBackBrush;
	static HBRUSH hBrush, hOldBrush;
	static POINT ptCurrent;
	static UINT index = -1, indexcolor = -1, indexType = -1, indexSize = -1, indexLine = -1, indexDelete = -1;
	//static UINT crCustomLines[5] = { PS_SOLID, PS_DASH,PS_DOT ,PS_DASHDOT ,PS_DASHDOTDOT };
	static HBRUSH hPaintBrush, hBackBrush;
	POINT p;
	float num1, num2, sum;
	TCHAR buf[256];
	CString str, str1, str2;//������ʾ������
	LOGFONT logFont_size;
	HFONT	hOldFont;
	switch (message)
	{
	case WM_CREATE:         //������Ϣ
		logPen.lopnColor = RGB(0, 0, 0);
		logPen.lopnStyle = PS_SOLID;
		logPen.lopnWidth.x = 1;
		crPen = logPen.lopnColor;

		logBrush.lbColor=RGB(255, 255, 255);
		logBrush.lbStyle = BS_SOLID;
		logBrush.lbHatch = 1;
		crBrush = logBrush.lbColor;

		LogBackBrush.lbColor = RGB(255, 255, 255);

		logFont.lfHeight = 25;
		return 0;

	case WM_COMMAND:
		hMenu = GetMenu(hWnd);

		switch (LOWORD(wParam))
		{
		case IDM_NEW:
			if (bFileChange && IDCANCEL == QuerySaveFile(hWnd, szFileTitle))
				return 0;
			SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(255, 255, 255)));
			InvalidateRect(hWnd, NULL, TRUE);
			ClearBuffer();
			bFileChange = FALSE;
			return 0;

		case IDM_OPEN:
			if (bFileChange && IDCANCEL == QuerySaveFile(hWnd, szFileTitle))
				return 0;
			if (OpenAndReadFigures(hWnd))
				InvalidateRect(hWnd, NULL, TRUE);
			return 0;

		case IDM_SAVE:
			SaveFigures(hWnd);
			return 0;

		case IDM_TEXT_COLOR:
			hdc = GetDC(hWnd);
			crText = MyChooseColor(hWnd);
			SetTextColor(hdc, crText);
			ReleaseDC(hWnd, hdc);
			return 0;

		case IDM_TEXT_STYLE:
			logFont = MyChooseFont(hWnd);
			hdc = GetDC(hWnd);
			if (hFont)
				DeleteObject(hFont);
			hFont = CreateFontIndirect(&logFont);//������ʼ���õ�����
			if (hFont) SelectObject(hdc, hFont);              //ѡ���߼�����
			InvalidateRect(hWnd, NULL, TRUE);
			ReleaseDC(hWnd, hdc);
			return 0;

		case IDM_PEN_COLOR:
			crPen = MyChooseColor(hWnd);
			logPen.lopnColor = crPen;
			return 0;

		case IDM_BRUSH_COLOR:
			crBrush = MyChooseColor(hWnd);
			logBrush.lbColor = crBrush;
			return 0;

		case IDM_BACKGROUND_COLOR:
			crBackBrush = MyChooseColor(hWnd);
			LogBackBrush.lbColor = crBackBrush;
			hBackBrush = CreateBrushIndirect(&LogBackBrush);
			hOldBrush = (HBRUSH)GetClassLong(hWnd, GCL_HBRBACKGROUND);     //GCL_HBRBACKGROUND����ñ�����ˢ�����
			SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)hBackBrush);//ÿ����һ�α�����ˢ�ͻ����һ���ɻ�ˢ
			DeleteObject(hOldBrush);
			InvalidateRect(hWnd, NULL, TRUE);
			return 0;

		case IDM_EXIT:
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			return 0;

		case IDM_TEXT:
			if (first == TRUE)
			{
				MessageBox(hWnd, TEXT("����Ҽ�������ʾ�����ı�"),
					TEXT("�򵥻�ͼ����"), MB_OK | MB_ICONINFORMATION);
				first = FALSE;
			}
		case IDM_LINE:
		case IDM_RECT:
		case IDM_ELLIPESE:
			CheckMenuItem(hMenu, iSelectionFig, MF_UNCHECKED);
			iSelectionFig = LOWORD(wParam);
			CheckMenuItem(hMenu, iSelectionFig, MF_CHECKED);
			return 0;

		case IDM_FIX_SIZE:
			SetCapture(hWnd);
			p.x = ptrEnd.x;//��������Ҽ�����λ�ã�
			p.y = ptrEnd.y;
			ScreenToClient(hWnd, &p);
			indexSize = -1;
			flagmode = SelectImag(p);
			indexSize = ReturnFigIndex(flagmode, p);//����indexΪѡ�е�ͼԪ���
			if (indexSize != -1)
			{
				bDrawing = TRUE;
				//���ԭͼԪ
				hdc = GetDC(hWnd);
				if (LogBackBrush.lbColor == RGB(255, 255, 255))
				{
					SetROP2(hdc, R2_WHITE);
				}
				else
				{
					hBackBrush = CreateBrushIndirect(&LogBackBrush);
					hOldBrush = (HBRUSH)SelectObject(hdc, hBackBrush);
					LogBackPen.lopnColor = LogBackBrush.lbColor;
					hBackPen = CreatePenIndirect(&LogBackPen);
					hOldPen = (HPEN)SelectObject(hdc, hBackPen);
				}
				switch (flagmode)
				{
				case RECTS:
					Rectangle(hdc, gRects[indexSize].ptStart.x, gRects[indexSize].ptStart.y,
						gRects[indexSize].ptEnd.x, gRects[indexSize].ptEnd.y);
					break;
				case LINES:
					DrawOneLine(hdc, gLines[indexSize].ptStart.x, gLines[indexSize].ptStart.y,
						gLines[indexSize].ptEnd.x, gLines[indexSize].ptEnd.y, logPen);
					break;
				case ELLIPSES:
					Ellipse(hdc, gEllipses[indexSize].ptStart.x, gEllipses[indexSize].ptStart.y,
						gEllipses[indexSize].ptEnd.x, gEllipses[indexSize].ptEnd.y);
					break;
				}
				SendMessage(hWnd, WM_MOUSEMOVE, 0, 0);
				ReleaseDC(hWnd, hdc);
				if (LogBackBrush.lbColor != RGB(255, 255, 255))
				{
					SelectObject(hdc, hOldBrush);
					DeleteObject(hBackBrush);
					SelectObject(hdc, hOldPen);
					DeleteObject(hBackPen);
				}
			}
			ReleaseCapture();
			return 0;

		case IDM_FIX_TYPE:
			SetCapture(hWnd);
			p.x = ptrEnd.x;//��������Ҽ�����λ�ã�
			p.y = ptrEnd.y;
			ScreenToClient(hWnd, &p);
			indexType = -1;
			flagmode = SelectImag(p);
			indexType = ReturnFigIndex(flagmode, p);//����indexΪѡ�е�ͼԪ���
			if (flagmode == TEXTS&&indexType!=-1)
				gTexts[indexType].logFont = MyChooseFont(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
			ReleaseCapture();
			indexType = -1;
			return 0;

		case IDM_FIX_LOCATION:
			SetCapture(hWnd);
			p.x = ptrEnd.x;//��������Ҽ�����λ�ã�
			p.y = ptrEnd.y;
			ScreenToClient(hWnd, &p);
			index = -1;
			flagmode = SelectImag(p);
			index = ReturnFigIndex(flagmode, p);//����indexΪѡ�е�ͼԪ���
			if (index != -1)
			{
				bDrawing = TRUE;
				//���ԭͼԪ
				hdc = GetDC(hWnd);
				if (LogBackBrush.lbColor == RGB(255, 255, 255))
				{
					SetROP2(hdc, R2_WHITE);
				}
				else
				{
					hBackBrush = CreateBrushIndirect(&LogBackBrush);
					hOldBrush = (HBRUSH)SelectObject(hdc, hBackBrush);
					LogBackPen.lopnColor = LogBackBrush.lbColor;
					hBackPen = CreatePenIndirect(&LogBackPen);
					hOldPen = (HPEN)SelectObject(hdc, hBackPen);
				}
				switch (flagmode)
				{
				case RECTS:
					Rectangle(hdc, gRects[index].ptStart.x, gRects[index].ptStart.y,
						gRects[index].ptEnd.x, gRects[index].ptEnd.y);
					break;
				case LINES:
					DrawOneLine(hdc, gLines[index].ptStart.x, gLines[index].ptStart.y,
						gLines[index].ptEnd.x, gLines[index].ptEnd.y, logPen);
					break;
				case ELLIPSES:
					Ellipse(hdc, gEllipses[index].ptStart.x, gEllipses[index].ptStart.y,
						gEllipses[index].ptEnd.x, gEllipses[index].ptEnd.y);
					break;
				case TEXTS:
					rect.left = gTexts[index].pt.x;
					rect.top = gTexts[index].pt.y;
					rect.right = gTexts[index].pt.x + strlen(gTexts[index].pBuffer) * 30;
					rect.bottom = gTexts[index].pt.y + abs(gTexts[index].logFont.lfHeight);
					FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
					break;
				}
				if (LogBackBrush.lbColor != RGB(255, 255, 255))
				{
					SelectObject(hdc, hOldBrush);
					DeleteObject(hBackBrush);
					SelectObject(hdc, hOldPen);
					DeleteObject(hBackPen);
				}
				SendMessage(hWnd, WM_MOUSEMOVE, 0, 0);
				ReleaseDC(hWnd,hdc);
			}
			ReleaseCapture();
			return 0;

		case IDM_FIX_COLOR:
			SetCapture(hWnd);
			p.x = ptrEnd.x;//��������Ҽ�����λ�ã�
			p.y = ptrEnd.y;
			ScreenToClient(hWnd, &p);
			indexcolor = -1;
			flagmode = SelectImag(p);
			indexcolor = ReturnFigIndex(flagmode, p);//����indexΪѡ�е�ͼԪ���
			if (indexcolor != -1)
			{
				switch (flagmode)
				{
				case LINES:
					oldColor = crPen;
					logPen.lopnColor = MyChooseColor(hWnd);
					gLines[indexcolor].logPen = logPen;
					logPen.lopnColor = oldColor;//�ָ���ɫ
					break;
				case RECTS:
					oldColor = crBrush;
					logBrush.lbColor = MyChooseColor(hWnd);
					gRects[indexcolor].logBrush = logBrush;
					logBrush.lbColor = oldColor;//�ָ���ɫ
					break;
				case ELLIPSES:
					oldColor = crBrush;
					logBrush.lbColor = MyChooseColor(hWnd);
					gEllipses[indexcolor].logBrush = logBrush;
					logBrush.lbColor = oldColor;//�ָ���ɫ
					break;
				case TEXTS:
					gTexts[indexcolor].color = MyChooseColor(hWnd);
					break;
				}
			}
			indexcolor = -1;
			InvalidateRect(hWnd, NULL, TRUE);
			ReleaseCapture();
			return 0;

		case IDM_FIX_LINE:
			SetCapture(hWnd);
			p.x = ptrEnd.x;//��������Ҽ�����λ�ã�
			p.y = ptrEnd.y;
			ScreenToClient(hWnd, &p);
			indexLine = -1;
			flagmode = SelectImag(p);
			indexLine = ReturnFigIndex(flagmode, p);//����indexΪѡ�е�ͼԪ���
			if (flagmode == LINES&&indexLine!=-1)
			{
				if ((DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
					MAKEINTRESOURCE(IDD_LINE),
					hWnd, InputLineProc) == IDOK))
				{
					switch (iCurrentLine)
					{
					case IDC_SOLID:
						gLines[indexLine].logPen.lopnStyle = PS_SOLID;
						break;
					case IDC_DASH:
						gLines[indexLine].logPen.lopnStyle = PS_DASH;
						break;
					case IDC_DOT:
						gLines[indexLine].logPen.lopnStyle = PS_DOT;
						break;
					case IDC_DASHDOT:
						gLines[indexLine].logPen.lopnStyle = PS_DASHDOT;
						break;
					case IDC_DASHDOTDOT:
						gLines[indexLine].logPen.lopnStyle = PS_DASHDOTDOT;
						break;
					}
				}
			}
			InvalidateRect(hWnd, NULL, TRUE);
			ReleaseCapture();
			return 0;

		case IDM_DELETE:
			SetCapture(hWnd);
			p.x = ptrEnd.x;//��������Ҽ�����λ�ã�
			p.y = ptrEnd.y;
			ScreenToClient(hWnd, &p);
			indexDelete = -1;
			flagmode = SelectImag(p);
			indexDelete = ReturnFigIndex(flagmode, p);//����indexΪѡ�е�ͼԪ���
			if (indexDelete != -1)
			{
				switch (flagmode)
				{
				case LINES:
					DeleteOneLine(indexDelete);
					break;
				case RECTS:
					DeleteOneRect(indexDelete);
					break;
				case ELLIPSES:
					DeleteOneEllipse(indexDelete);
					break;
				case TEXTS:
					DeleteOneText(indexDelete);
					break;
				}
			}
			InvalidateRect(hWnd, NULL, TRUE);
			ReleaseCapture();
			return 0;

		case IDM_COMPUTE:
			if ((DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
				MAKEINTRESOURCE(IDD_COMPUTE),
				hWnd, ComputeProc) == IDOK))
			{
				num1 = atof(NUM1);
				num2 = atof(NUM2);
				switch (iCurRule)
				{
				case IDC_ADD:
					sum = num1 + num2;
					str.Format(TEXT("%.2f"), num1);
					str1.Format(TEXT("%.2f"), num2);
					str2.Format(TEXT("%.2f"), sum);
					wsprintf(buf, "%s+%s��%s", str.GetBuffer(str.GetLength()), str1.GetBuffer(str.GetLength()), str2.GetBuffer(str.GetLength()));
					break;
				case IDC_SUB:
					sum = num1 - num2;
					str.Format(TEXT("%.2f"), num1);
					str1.Format(TEXT("%.2f"), num2);
					str2.Format(TEXT("%.2f"), sum);
					wsprintf(buf, "%s-%s��%s", str.GetBuffer(str.GetLength()), str1.GetBuffer(str.GetLength()), str2.GetBuffer(str.GetLength()));
					break;
				case IDC_MULTI:
					sum = num1*num2;
					str.Format(TEXT("%.2f"), num1);
					str1.Format(TEXT("%.2f"), num2);
					str2.Format(TEXT("%.2f"), sum);
					wsprintf(buf, "%s��%s��%s", str.GetBuffer(str.GetLength()), str1.GetBuffer(str.GetLength()), str2.GetBuffer(str.GetLength()));
					break;
				case IDC_DIV:
					sum = num1 / num2;
					str.Format(TEXT("%.2f"), num1);
					str1.Format(TEXT("%.2f"), num2);
					str2.Format(TEXT("%.2f"), sum);
					wsprintf(buf, "%s��%s��%s", str.GetBuffer(str.GetLength()), str1.GetBuffer(str.GetLength()), str2.GetBuffer(str.GetLength()));
					break;
				}
				
				MessageBox(hWnd, buf,
					TEXT("������"), MB_OK | MB_ICONINFORMATION);
			}
			return 0;

		case IDM_HELP:
			MessageBox(hWnd, TEXT("�򵥻�ͼ���򣺽���ʽ���ƻ���ͼ��"),
				TEXT("�򵥻�ͼ����"), MB_OK | MB_ICONINFORMATION);
			return 0;
		}
		return 0;

	case WM_CONTEXTMENU://ѡ���ı��� �Ҽ����ı�
		flagmode = 0;
		SetCapture(hWnd);
		hWnd = (HWND)wParam; //���ھ��
		ptrEnd.x = GET_X_LPARAM(lParam);  //���X��Ļ����
		ptrEnd.y = GET_Y_LPARAM(lParam);  //���Y��Ļ����
		ScreenToClient(hWnd, &ptrEnd);
		
		flagmode = SelectImag(ptrEnd);//�ж��Ҽ��Ƿ���ͼԪ��

		if (flagmode)
		{
			ClientToScreen(hWnd, &ptrEnd);
			hMenu = CreatePopupMenu();  //��������ʽ�˵�
			hSrcMenu = LoadMenu((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDR_RBUTTON_MENU)); //���ز˵���Դ																										  //��uFlags����ΪMF_POPUPʱ��������������ʾ����ʽ�˵����Ӳ˵��ľ����
			AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hSrcMenu, TEXT("Popup")); //���ӵ������˵�
			hTackMenu = GetSubMenu(hMenu, 0); //ȡ��Ŀ��˵�
			if (flagmode != LINES)
				EnableMenuItem(hTackMenu, IDM_FIX_LINE, MF_GRAYED);
			if (flagmode != TEXTS)
				EnableMenuItem(hTackMenu, IDM_FIX_TYPE, MF_GRAYED);
			else
				EnableMenuItem(hTackMenu, IDM_FIX_SIZE, MF_GRAYED);
			TrackPopupMenuEx(hTackMenu, 0, ptrEnd.x, ptrEnd.y, hWnd, NULL); //�����˵�
			DestroyMenu(hSrcMenu); //���ټ��صĲ˵�
			DestroyMenu(hMenu); //���ٵ����˵�
		}
		else
		{
			switch (iSelectionFig)
			{
			case IDM_TEXT:
				if ((DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
					MAKEINTRESOURCE(IDD_TEXT),
					hWnd, InputDlgProc) == IDOK))
				{
					// ���Ի����е�������ӵ���ǰ�ı༭����
					hdc = GetDC(hWnd);
					TextOut(hdc, ptrEnd.x, ptrEnd.y, g_EditInput, strlen(g_EditInput));
					InvalidateRect(hWnd, NULL, TRUE);
					AddOneText(ptrEnd, g_EditInput, logFont, crText);
					ReleaseDC(hWnd, hdc);
				}
				break;
			}
		}
		ReleaseCapture();
		flagmode = 0;
		return 0;

	case WM_LBUTTONDOWN:
		if (!bDrawing)
			SetCapture(hWnd);

		ptBegin.x = GET_X_LPARAM(lParam);
		ptBegin.y = GET_Y_LPARAM(lParam);
		ptEnd.x = GET_X_LPARAM(lParam);
		ptEnd.y = GET_Y_LPARAM(lParam);
		
		bDrawing = TRUE;
		return 0;

	case WM_LBUTTONUP:
		if (bDrawing)
			ReleaseCapture();
		if (index != -1)
		{
			switch (flagmode)
			{
			case LINES:
				rect.left = (ptEnd.x - 0.5*(gLines[index].ptEnd.x - gLines[index].ptStart.x));
				rect.top = (ptEnd.y - 0.5*(gLines[index].ptEnd.y - gLines[index].ptStart.y));
				rect.right = (ptEnd.x + 0.5*(gLines[index].ptEnd.x - gLines[index].ptStart.x));
				rect.bottom = (ptEnd.y + 0.5*(gLines[index].ptEnd.y - gLines[index].ptStart.y));
				if (ChangeOneLineLocation(rect.left, rect.top, rect.right, rect.bottom, index))
					index = -1;
				break;
			case RECTS:
				rect.left = (ptEnd.x - 0.5*(gRects[index].ptEnd.x - gRects[index].ptStart.x));
				rect.top = (ptEnd.y - 0.5*(gRects[index].ptEnd.y - gRects[index].ptStart.y));
				rect.right = (ptEnd.x + 0.5*(gRects[index].ptEnd.x - gRects[index].ptStart.x));
				rect.bottom = (ptEnd.y + 0.5*(gRects[index].ptEnd.y - gRects[index].ptStart.y));
				if (ChangeOneRectLocation(rect.left, rect.top, rect.right, rect.bottom, index))
					index = -1;
				break;
			case ELLIPSES:
				rect.left = (ptEnd.x - 0.5*(gEllipses[index].ptEnd.x - gEllipses[index].ptStart.x));
				rect.top = (ptEnd.y - 0.5*(gEllipses[index].ptEnd.y - gEllipses[index].ptStart.y));
				rect.right = (ptEnd.x + 0.5*(gEllipses[index].ptEnd.x - gEllipses[index].ptStart.x));
				rect.bottom = (ptEnd.y + 0.5*(gEllipses[index].ptEnd.y - gEllipses[index].ptStart.y));
				if (ChangeOneEllipseLocation(rect.left, rect.top, rect.right, rect.bottom, index))
					index = -1;
				break;
			case TEXTS:
				rect.left = (ptEnd.x - 0.5*strlen(gTexts[index].pBuffer) * 15);
				rect.top = (ptEnd.y - 0.5*(abs(gTexts[index].logFont.lfHeight)));
				rect.right = (ptEnd.x + 0.5*(strlen(gTexts[index].pBuffer) * 15));
				rect.bottom = (ptEnd.y + 0.5*(abs(gTexts[index].logFont.lfHeight)));
				if (ChangeOneTextLocation(rect.left, rect.top, rect.right, rect.bottom,index))
					index = -1;
				break;
			}
		}
		else if (indexSize != -1)
		{
			switch (flagmode)
			{
			case LINES:
				if (ChangeOneLineSize(gLines[indexSize].ptStart.x, gLines[indexSize].ptStart.y, ptEnd.x, ptEnd.y, indexSize))
					indexSize = -1;
				break;
			case RECTS:
				if (ChangeOneRectSize(gRects[indexSize].ptStart.x, gRects[indexSize].ptStart.y, ptEnd.x, ptEnd.y, indexSize))
					indexSize = -1;
				break;
			case ELLIPSES:
				if (ChangeOneEllipseSize(gEllipses[indexSize].ptStart.x, gEllipses[indexSize].ptStart.y, ptEnd.x, ptEnd.y, indexSize))
					indexSize = -1;
				break;
			}
		}
		else
		{
			switch (flagdraw)
			{
			case LINES:
				AddOneLine(ptBegin, ptEnd, logPen);
				break;
			case RECTS:
				AddOneRect(ptBegin, ptEnd, logPen, logBrush);
				break;
			case ELLIPSES:
				AddOneEllipse(ptBegin, ptEnd, logPen, logBrush);
				break;
			}
		}
		InvalidateRect(hWnd, NULL, TRUE);
		bFileChange = TRUE;
		bDrawing = FALSE;
		return 0;

	case WM_MOUSEMOVE:
		if (!bDrawing)
			return 0;
		hdc = GetDC(hWnd);
		hPen = CreatePenIndirect(&logPen);
		hOldPen = (HPEN)SelectObject(hdc, hPen);
		hBrush = CreateBrushIndirect(&logBrush);
		hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		//���ԭ��ͼ�켣
		if (LogBackBrush.lbColor == RGB(255, 255, 255))
		{
			SetROP2(hdc, R2_WHITE);
		}
		else
		{
			hBackBrush = CreateBrushIndirect(&LogBackBrush);
			hOldBrush = (HBRUSH)SelectObject(hdc, hBackBrush);
			LogBackPen.lopnColor = LogBackBrush.lbColor;
			hBackPen = CreatePenIndirect(&LogBackPen);
			hOldPen = (HPEN)SelectObject(hdc, hBackPen);
		}
		if (index != -1)
		{
			switch (flagmode)
			{
			case LINES:
				rect.left = (ptEnd.x - 0.5*(gLines[index].ptEnd.x - gLines[index].ptStart.x));
				rect.top = (ptEnd.y - 0.5*(gLines[index].ptEnd.y - gLines[index].ptStart.y));
				rect.right = (ptEnd.x + 0.5*(gLines[index].ptEnd.x - gLines[index].ptStart.x));
				rect.bottom = (ptEnd.y + 0.5*(gLines[index].ptEnd.y - gLines[index].ptStart.y));
				DrawOneLine(hdc, rect.left, rect.top, rect.right, rect.bottom, logPen);
				break;
			case RECTS:
					rect.left = (ptEnd.x - 0.5*(gRects[index].ptEnd.x - gRects[index].ptStart.x));
					rect.top = (ptEnd.y - 0.5*(gRects[index].ptEnd.y - gRects[index].ptStart.y));
					rect.right = (ptEnd.x + 0.5*(gRects[index].ptEnd.x - gRects[index].ptStart.x));
					rect.bottom = (ptEnd.y + 0.5*(gRects[index].ptEnd.y - gRects[index].ptStart.y));
					if (LogBackBrush.lbColor == RGB(255, 255, 255))
						FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
					else
						FillRect(hdc, &rect, hBackBrush);
				break;
			case ELLIPSES:
					rect.left = (ptEnd.x - 0.5*(gEllipses[index].ptEnd.x - gEllipses[index].ptStart.x));
					rect.top = (ptEnd.y - 0.5*(gEllipses[index].ptEnd.y - gEllipses[index].ptStart.y));
					rect.right = (ptEnd.x + 0.5*(gEllipses[index].ptEnd.x - gEllipses[index].ptStart.x));
					rect.bottom = (ptEnd.y + 0.5*(gEllipses[index].ptEnd.y - gEllipses[index].ptStart.y));
					if (LogBackBrush.lbColor == RGB(255, 255, 255))
						FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
					else
						FillRect(hdc, &rect, hBackBrush);
				break;
			case TEXTS:
					rect.left = ptEnd.x - 0.5*strlen(gTexts[index].pBuffer) * 20;
					rect.top = ptEnd.y - 0.5*abs(gTexts[index].logFont.lfHeight);
					rect.right = ptEnd.x + 0.5*strlen(gTexts[index].pBuffer) * 20;
					rect.bottom = ptEnd.y + 0.5*abs(gTexts[index].logFont.lfHeight);
					if (LogBackBrush.lbColor == RGB(255, 255, 255))
						FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
					else
						FillRect(hdc, &rect, hBackBrush);
				break;
			}
		}
		else if (indexSize != -1)
		{
			switch (flagmode)
			{
			case LINES:
				rect.left = gLines[indexSize].ptStart.x;
				rect.top = gLines[indexSize].ptStart.y;
				rect.right = ptEnd.x;
				rect.bottom = ptEnd.y;
				DrawOneLine(hdc, rect.left, rect.top, rect.right, rect.bottom, logPen);
				break;
			case RECTS:
				rect.left = gRects[indexSize].ptStart.x;
				rect.top = gRects[indexSize].ptStart.y;
				rect.right = ptEnd.x;
				rect.bottom = ptEnd.y;
				if (LogBackBrush.lbColor == RGB(255, 255, 255))
					FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
				else
					FillRect(hdc, &rect, hBackBrush);
				break;
			case ELLIPSES:
				rect.left = gEllipses[indexSize].ptStart.x;
				rect.top = gEllipses[indexSize].ptStart.y;
				rect.right = ptEnd.x;
				rect.bottom = ptEnd.y;
				if (LogBackBrush.lbColor == RGB(255, 255, 255))
					FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
				else
					FillRect(hdc, &rect, hBackBrush);
				break;
			}
		}
		else
		{
			switch (iSelectionFig)
			{
			case IDM_LINE:
				DrawOneLine(hdc, ptBegin.x, ptBegin.y, ptEnd.x, ptEnd.y, logPen);
				break;
			case IDM_RECT:
					Rectangle(hdc, ptBegin.x, ptBegin.y,
						ptEnd.x, ptEnd.y);
				break;
			case IDM_ELLIPESE:
					Ellipse(hdc, ptBegin.x, ptBegin.y,
						ptEnd.x, ptEnd.y);
				break;
			}
		}
		if (LogBackBrush.lbColor != RGB(255, 255, 255))
		{
			SelectObject(hdc, hOldBrush);
			DeleteObject(hBackBrush);
			SelectObject(hdc, hOldPen);
			DeleteObject(hBackPen);
		}
		//�����¹켣
		ptEnd.x = GET_X_LPARAM(lParam);
		ptEnd.y = GET_Y_LPARAM(lParam);

		SetROP2(hdc, R2_COPYPEN);
		if (index != -1)
		{//�ƶ���ʱ����ݵ�ǰ�Ҽ��Ķ��� �����ܸ��ݲ˵�ѡ�
			switch (flagmode)
			{
			case LINES:
				DrawOneLine(hdc, (ptEnd.x - 0.5*(gLines[index].ptEnd.x - gLines[index].ptStart.x)), (ptEnd.y - 0.5*(gLines[index].ptEnd.y - gLines[index].ptStart.y)),
					(ptEnd.x + 0.5*(gLines[index].ptEnd.x - gLines[index].ptStart.x)), (ptEnd.y + 0.5*(gLines[index].ptEnd.y - gLines[index].ptStart.y)), gLines[index].logPen);
				break;
			case RECTS:
					/*Rectangle(hdc, ptEnd.x, ptEnd.y,
					ptEnd.x + (gRects[index].ptEnd.x - gRects[index].ptStart.x), ptEnd.y + (gRects[index].ptEnd.y - gRects[index].ptStart.y));*/
				hPaintBrush = CreateBrushIndirect(&gRects[index].logBrush);
				hOldBrush = (HBRUSH)SelectObject(hdc, hPaintBrush);
				Rectangle(hdc, (ptEnd.x - 0.5*(gRects[index].ptEnd.x - gRects[index].ptStart.x)), (ptEnd.y - 0.5*(gRects[index].ptEnd.y - gRects[index].ptStart.y)),
					(ptEnd.x + 0.5*(gRects[index].ptEnd.x - gRects[index].ptStart.x)), (ptEnd.y + 0.5*(gRects[index].ptEnd.y - gRects[index].ptStart.y)));
				SelectObject(hdc, hOldBrush);
				DeleteObject(hPaintBrush);
				break;

			case ELLIPSES:
				hPaintBrush = CreateBrushIndirect(&gEllipses[index].logBrush);
				hOldBrush = (HBRUSH)SelectObject(hdc, hPaintBrush);
				Ellipse(hdc, (ptEnd.x - 0.5*(gEllipses[index].ptEnd.x - gEllipses[index].ptStart.x)), (ptEnd.y - 0.5*(gEllipses[index].ptEnd.y - gEllipses[index].ptStart.y)),
					(ptEnd.x + 0.5*(gEllipses[index].ptEnd.x - gEllipses[index].ptStart.x)), (ptEnd.y + 0.5*(gEllipses[index].ptEnd.y - gEllipses[index].ptStart.y)));
				SelectObject(hdc, hOldBrush);
				DeleteObject(hPaintBrush);
				break;
			case TEXTS:
				rect.left = ptEnd.x-0.5*strlen(gTexts[index].pBuffer) * 20;
				rect.top = ptEnd.y - 0.5*abs(gTexts[index].logFont.lfHeight);
				rect.right = ptEnd.x +0.5*strlen(gTexts[index].pBuffer) * 20;
				rect.bottom = ptEnd.y + 0.5*abs(gTexts[index].logFont.lfHeight);

				logFont_size = gTexts[index].logFont;
				hFont = CreateFontIndirect(&logFont_size);
				hOldFont = (HFONT)SelectObject(hdc, hFont);         //ѡ���߼�����				
				SetTextColor(hdc, gTexts[index].color);				
				//���ﲻ����Textout�����ܸ�������ƶ�
				DrawText(hdc, gTexts[index].pBuffer, strlen(gTexts[index].pBuffer), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				break;
			}
		}
		else if (indexSize != -1)
		{
			switch (flagmode)
			{
			case LINES:
				DrawOneLine(hdc, gLines[indexSize].ptStart.x, gLines[indexSize].ptStart.y,
					ptEnd.x, ptEnd.y, gLines[indexSize].logPen);
				break;

			case RECTS:
				hPaintBrush = CreateBrushIndirect(&gRects[indexSize].logBrush);
				hOldBrush = (HBRUSH)SelectObject(hdc, hPaintBrush);
				Rectangle(hdc, gRects[indexSize].ptStart.x, gRects[indexSize].ptStart.y,
					ptEnd.x, ptEnd.y);
				SelectObject(hdc, hOldBrush);
				DeleteObject(hPaintBrush);
				break;

			case ELLIPSES:
				hPaintBrush = CreateBrushIndirect(&gEllipses[indexSize].logBrush);
				hOldBrush = (HBRUSH)SelectObject(hdc, hPaintBrush);
				Ellipse(hdc, gEllipses[indexSize].ptStart.x, gEllipses[indexSize].ptStart.y,
					ptEnd.x, ptEnd.y);
				SelectObject(hdc, hOldBrush);
				DeleteObject(hPaintBrush);
				break;
			}
		}
		else
		{//�������ƶ�״̬�ſ��Ը��ݲ˵�ѡ�
			
			switch (iSelectionFig)
			{
			case IDM_LINE:
				flagdraw = LINES;
				DrawOneLine(hdc, ptBegin.x, ptBegin.y, ptEnd.x, ptEnd.y, logPen);
				break;

			case IDM_RECT:
				flagdraw = RECTS;
				Rectangle(hdc, ptBegin.x, ptBegin.y,
					ptEnd.x, ptEnd.y);
				break;

			case IDM_ELLIPESE:
				flagdraw = ELLIPSES;
				Ellipse(hdc, ptBegin.x, ptBegin.y,
					ptEnd.x, ptEnd.y);
				break;
			}
		}
		SetTextColor(hdc, crText);
		SelectObject(hdc, hOldPen);
		SelectObject(hdc, hOldBrush);
		SelectObject(hdc, hOldFont);
		ReleaseDC(hWnd, hdc);
		return 0;

	case WM_PAINT:              

		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);

		DrawAllLines(hdc);
		DrawAllRects(hdc);
		DrawAllEllipses(hdc);
		DrawAllTexts(hdc);

		if (first1 == TRUE)
		{
			MessageBox(hWnd, TEXT("����Ҽ�����ͼԪ�ɽ��и��������޸�"),
				TEXT("�򵥻�ͼ����"), MB_OK | MB_ICONINFORMATION);
			first1 = FALSE;
		}
		EndPaint(hWnd, &ps);
		return 0;

	case WM_CLOSE:
		if (!bFileChange || IDCANCEL != QuerySaveFile(hWnd, szFileTitle))
			DestroyWindow(hWnd);
		return 0;

	case WM_DESTROY:
		if (hFont)  DeleteObject(hFont);
		DeleteObject(hPen);
		DeleteObject(hBrush);
		PostQuitMessage(0);

		return 0;
	}

	//����ȱʡ��Ϣ�������
	return DefWindowProc(hWnd, message, wParam, lParam);

} //���� WinProc ����

