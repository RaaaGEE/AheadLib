


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Pretreatment
#include "Main.h"
#include "AboutDlg.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Macro definition
#ifdef _CHS
#define FONT_NAME_AboutDlg		L"Times New Roman"									// Font Name
#else // _CHS
#define FONT_NAME_AboutDlg		L"MS Sans Serif"						// Font Name
#endif // _CHS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AboutDlg Namespaces
namespace AboutDlg
{
#ifdef _CHS
	const WORD WIDTH_AboutDlg = 399;									// Dialog Width
	const WORD HEIGHT_AboutDlg = 273;									// Dialog height
	const WORD FONT_SIZE_AboutDlg = 9;									// font size
#else // _CHS
	const WORD WIDTH_AboutDlg = 399;									// Dialog Width
	const WORD HEIGHT_AboutDlg = 258;									// Dialog height
	const WORD FONT_SIZE_AboutDlg = 8;									// font size
#endif // _CHS

#if defined(_CHS) && defined(_UNICODE)
	const UINT WIDTH_Text = 12;											// The default font width
	const UINT HEIGHT_Text = 13;										// The default font height
#else // defined(_CHS) && defined(_UNICODE)
	const UINT WIDTH_Text = 6;											// The default font width
	const UINT HEIGHT_Text = 13;										// The default font height
#endif // defined(_CHS) && defined(_UNICODE)

	const UINT IDT_Close = 1534;										// Close clock mark
	const COLORREF COLOR_Link = 0x00FF0000;								// Hyperlink color
	const COLORREF COLOR_HotLink = 0x000000FF;							// Mouse Hot Hyperlink color

	// ¶Ô»°¿òÄ£°å
	const struct DIALOGINFO
	{
		DLGTEMPLATE dtDialog;											// Dialog
		WORD wNoMenu;													// No dialog menu
		WORD wNoClass;													// No dialog class name
		WORD wNoCaption;												// No dialog title
		WORD wFontSize;													// Dialog font size
		WCHAR wszFontName[_NumberOf(FONT_NAME_AboutDlg)];				// Dialog Font Name
		__declspec(align(4)) WORD wEndOfDialog;							// Dialog end flag
	}
	DI_Dialog =
	{
		{DS_SETFONT | DS_CENTER | WS_POPUP | WS_BORDER | WS_VISIBLE, 0, 0,
			0, 0, (WIDTH_AboutDlg * 2 / 3), (HEIGHT_AboutDlg * 2 / 3)},
			0, 0, 0, FONT_SIZE_AboutDlg, FONT_NAME_AboutDlg, 0
	};

	// Horizontal group
	const struct LINEINFO
	{
		RECT rtRect;													// position
		COLORREF crColor;												// Colour
	}
	LI_Lines[] =
	{
		{{0, 1, 88, 74}, 0x00FF9966},									// Blue Line Group
		{{60, 116, WIDTH_AboutDlg, 132}, 0x00FF9966},					// Blue Line Group
		{{60, 175, WIDTH_AboutDlg, 176}, 0x00000000},					// A white line
	};

	// rectangle
	const struct RECTINFO
	{
		RECT rtRect;													// position
		COLORREF crColor;												// Colour
	}
	RI_Rects[] =
	{
		{{0, 75, WIDTH_AboutDlg, 111}, 0x00FF9966},						// Blue rectangle
		{{0, 111, WIDTH_AboutDlg, 115}, 0x00CC3333},					// Dark blue rectangle
		{{60, 47, 116, 103}, 0x00CC3333},								// Dark blue rectangle frame Icon
		{{64, 51, 112, 99}, 0x00FFFFFF},								// White rectangle frame Icon
		{{68, 55, 86, 73}, RGB(0xEE, 0xEE, 0xEE + VER_Major % 16)},		// Background light gray rectangle icon
		{{90, 55, 108, 73}, RGB(0xEE, 0xEE, 0xEE + VER_Minor % 16)},	// Background light gray rectangle icon
		{{68, 79, 86, 95}, RGB(0xEE, 0xEE, 0xEE + VER_Release % 16)},	// Background light gray rectangle icon
		{{90, 79, 108, 95}, RGB(0xEE, 0xEE, 0xEE + VER_Build % 16)},	// Background light gray rectangle icon
	};

	// text
	const struct TEXTINFO
	{
		INT x;															// X coordinate
		INT y;															// Y coordinate
		PCTSTR ptzText;													// String
		COLORREF crColor;												// Colour
	}
	TI_Texts[] =
	{
		{60, 162, CAboutDlg::m_tzStatus, 0x00000000},					// Status Information
		{60, 140, STR_VersionStamp, 0x00BBBBBB},						// Version Information
		{230, 140, STR_BuildStamp, 0x00BBBBBB},							// Compile information
		{60, 240, STR_Description, 0x00000000},							// Description
		{60, 255, STR_Copyright, 0x00000000},							// Copyright Information
	};

	// A string that specifies the font
	const struct FONTTEXTINFO
	{
		INT x;															// X coordinate
		INT y;															// Y coordinate
		PCTSTR ptzText;													// String
		COLORREF crColor;												// Colour
		LOGFONT lfFont;													// Fonts
	}
	FTI_Texts[] =
	{
		{125, 40, STR_AppName, 0x00000000, {36, 0, 0, 0, 800, 1, 0, 0, 0, 0, 0, ANTIALIASED_QUALITY, 0, TEXT("Arial")}},
	};

	// Hyperlink
	const struct LINKINFO
	{
		RECT rtRect;													// position
		PCTSTR ptzTitle;												// title
		PCTSTR ptzTip;													// Prompt string
		PCTSTR ptzUrl;													// Hyperlink Target (HIWORD(ptzUrl) 0 indicates that the command message)
	}
	LI_Links[] =
	{
		{
			{60, 185, 60 + _LengthOf(STR_CheckUpdate) * WIDTH_Text, 185 + HEIGHT_Text},
				STR_CheckUpdate, STR_CheckUpdateTip, (PCTSTR) IDC_CheckUpdate
		},
		{
			{60, 200, 60 + _LengthOf(STR_VisitWeb) * WIDTH_Text, 200 + HEIGHT_Text},
				STR_VisitWeb, STR_VisitWebTip, STR_VisitWebUrl
		},
			{
				{60, 215, 60 + _LengthOf(STR_WriteEmail) * WIDTH_Text, 215 + HEIGHT_Text},
					STR_WriteEmail, STR_WriteEmailTip, STR_WriteEmailUrl
			},
	};

	// Icon Location
	const RECT RT_Icon = RI_Rects[2].rtRect;

	// Status information about the location
	const RECT RT_Status = {TI_Texts[0].x, TI_Texts[0].y, WIDTH_AboutDlg, TI_Texts[0].y + HEIGHT_Text};
};
using namespace AboutDlg;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CAboutDlg Static member variables
HWND CAboutDlg::m_hWnd = NULL;
BOOL CAboutDlg::m_bSplash = FALSE;
INT CAboutDlg::m_iLinkIndex = -1;
TCHAR CAboutDlg::m_tzStatus[64] = {0};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Display the About dialog box
VOID WINAPI CAboutDlg::Show(HWND hParent)
{
	if (m_hWnd == NULL)
	{
		DialogBoxIndirect(g_hInst, (LPDLGTEMPLATE) &DI_Dialog, hParent, AboutDlgProc);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Splash to display the About dialog box
VOID WINAPI CAboutDlg::Splash(HWND hParent, UINT uTimer)
{
	if (m_hWnd == NULL)
	{
		// Create a modeless dialog box
		CreateDialogIndirect(g_hInst, (LPDLGTEMPLATE) &DI_Dialog, hParent, AboutDlgProc);

		// If you specify automatic shutdown
		if (uTimer)
		{
			SetTimer(m_hWnd, IDT_Close, uTimer, NULL);
		}

		// Set current window display of tags to Splash
		m_bSplash = TRUE;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close the About dialog box
VOID WINAPI CAboutDlg::Close(UINT uTimer)
{
	// If it is closed immediately
	if (uTimer)
	{
		SetTimer(m_hWnd, IDT_Close, uTimer, NULL);
	}
	else
	{
		// Remove Timer
		KillTimer(m_hWnd, IDT_Close);

		// If the current window to display Splash
		if (m_bSplash)
		{
			DestroyWindow(m_hWnd);
			m_bSplash = FALSE;
		}
		else
		{
			EndDialog(m_hWnd, 0);
		}

		m_hWnd = NULL;
		m_tzStatus[0] = 0;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Setting status information
VOID WINAPI CAboutDlg::SetStatus(PCTSTR ptzText)
{
	HDC hDC;

	// Get status information
	if (ptzText)
	{
		_StrToStr(m_tzStatus, ptzText);
	}
	else
	{
		m_tzStatus[0] = 0;
	}

	// Drawing state information
	hDC = GetDC(m_hWnd);
	SetTextColor(hDC, TI_Texts[0].crColor);
	FillRect(hDC, &RT_Status, (HBRUSH) GetStockObject(WHITE_BRUSH));
	SelectObject(hDC, (HFONT) SendMessage(m_hWnd, WM_GETFONT, 0, 0));
	TextOut(hDC, TI_Texts[0].x, TI_Texts[0].y, TI_Texts[0].ptzText, lstrlen(TI_Texts[0].ptzText));
	ReleaseDC(m_hWnd, hDC);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// About dialog box callback function
INT_PTR CALLBACK CAboutDlg::AboutDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	INT i;
	HDC hDC;
	POINT ptPoint;

	switch (uMsg)
	{
	case WM_INITDIALOG:
		// Initialize variables
		m_hWnd = hWnd;
		m_iLinkIndex = NULL;

		// Set the mouse pointer
		SetClassLong(m_hWnd, GCL_HCURSOR, 0);
		SetCursor(LoadCursor(NULL, IDC_ARROW));

		// Style Settings dialog box
		if (GetParent(m_hWnd) == NULL)
		{
			SetWindowLong(m_hWnd, GWL_EXSTYLE, (GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_TOOLWINDOW));
			SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		}
		break;

	case WM_CTLCOLORDLG:
	case WM_CTLCOLORSTATIC:
		return (INT_PTR) GetStockObject(WHITE_BRUSH);

	case WM_PAINT:
		OnPaint();
		break;

	case WM_ACTIVATEAPP:
		// Activate the program
		GetCursorPos(&ptPoint);
		MapWindowPoints(NULL, m_hWnd, &ptPoint, 1);
		SendMessage(m_hWnd, WM_MOUSEMOVE, 0, MAKELONG(ptPoint.x, ptPoint.y));
		break;

	case WM_MOUSEMOVE:
		// Hyperlink change if the mouse position where
		ptPoint.x = LOWORD(lParam);
		ptPoint.y = HIWORD(lParam);
		i = GetLinkIndex(ptPoint);
		if (i != m_iLinkIndex)
		{
			m_iLinkIndex = i;
			hDC = GetDC(m_hWnd);
			PaintLinks(hDC);
			ReleaseDC(m_hWnd, hDC);
		}
		break;

	case WM_LBUTTONDOWN:
		// If the icon box, drag the dialog box
		ptPoint.x = LOWORD(lParam);
		ptPoint.y = HIWORD(lParam);
		if (PtInRect(&RT_Icon, ptPoint))
		{
			ReleaseCapture();
			PostMessage(m_hWnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
		}
		break;

	case WM_ENTERSIZEMOVE:
		SetCursor(LoadCursor(NULL, IDC_SIZEALL));
		break;

	case WM_EXITSIZEMOVE:
		SetCursor(LoadCursor(NULL, IDC_ARROW));
		break;

	case WM_LBUTTONUP:
		// If the mouse over the hyperlink within
		if (m_iLinkIndex != -1)
		{
			// If HIWORD (ptz Url) is 0, indicating that the command, otherwise it represents a hyperlink
			if (HIWORD(LI_Links[m_iLinkIndex].ptzUrl))
			{
				ShellExecute(NULL, NULL, LI_Links[m_iLinkIndex].ptzUrl, NULL, NULL, SW_NORMAL);
			}
			else
			{
				PostMessage(m_hWnd, WM_COMMAND, (WPARAM) LI_Links[m_iLinkIndex].ptzUrl, 0);
			}
		}
		else
		{
			// Close the dialog
			Close();
		}
		break;

	case WM_COMMAND:
		// Processing Command message
		switch (LOWORD(wParam))
		{
		case IDC_CheckUpdate:
			// Check for updates
			MessageBox(hWnd, TEXT("Hey, online upgrade feature is not implemented..."), STR_AppName, MB_ICONINFORMATION);
			break;

		case IDOK:
		case IDCANCEL:
			// Close the dialog
			Close();
			break;
		}
		break;

	case WM_TIMER:
	case WM_RBUTTONUP:
		// Close the dialog
		Close();
		break;
	}

	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw dialog box
VOID WINAPI CAboutDlg::OnPaint()
{
	INT i;
	INT j;
	HDC hDC;
	HPEN hPen;
	HBRUSH hBrush;
	POINT ptPoint;
	PAINTSTRUCT psPaint;

	// Start drawing
	hDC = BeginPaint(m_hWnd, &psPaint);

	// Draw a horizontal line group
	for (i = 0; i < _NumberOf(LI_Lines); i++)
	{
		hPen = (HPEN) SelectObject(hDC, CreatePen(PS_SOLID, 0, LI_Lines[i].crColor));
		for(j = LI_Lines[i].rtRect.top; j < LI_Lines[i].rtRect.bottom; j += 2)
		{
			MoveToEx(hDC, LI_Lines[i].rtRect.left, j, NULL);
			LineTo(hDC, LI_Lines[i].rtRect.right, j);
		}
		DeleteObject(SelectObject(hDC, hPen));
	}

	// Draw a rectangular area
	for (i = 0; i < _NumberOf(RI_Rects); i++)
	{
		hBrush = CreateSolidBrush(RI_Rects[i].crColor);
		FillRect(hDC, &RI_Rects[i].rtRect, hBrush);
		DeleteObject(hBrush);
	}

	// Charting
	DrawIcon(hDC,
		RT_Icon.left + (_RectWidth(RT_Icon) - 32) / 2,
		RT_Icon.top + (_RectHeight(RT_Icon) - 32) / 2,
		LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_Main)));

	// Draw Hyperlinks
	GetCursorPos(&ptPoint);
	MapWindowPoints(NULL, m_hWnd, &ptPoint, 1);
	m_iLinkIndex = GetLinkIndex(ptPoint);
	PaintLinks(hDC);

	// Use the dialog box default font, text rendering transparent background
	SetBkMode(hDC, TRANSPARENT);
	SelectObject(hDC, (HFONT) SendMessage(m_hWnd, WM_GETFONT, 0, 0));
	for (i = 0; i < _NumberOf(TI_Texts); i++)
	{
		SetTextColor(hDC, TI_Texts[i].crColor);
		TextOut(hDC, TI_Texts[i].x, TI_Texts[i].y, TI_Texts[i].ptzText, lstrlen(TI_Texts[i].ptzText));
	}

	// Draws the specified text font
	for (i = 0; i < _NumberOf(FTI_Texts); i++)
	{
		HFONT hFont = (HFONT) SelectObject(hDC, CreateFontIndirect(&FTI_Texts[i].lfFont));
		SetTextColor(hDC, FTI_Texts[i].crColor);
		TextOut(hDC, FTI_Texts[i].x, FTI_Texts[i].y, FTI_Texts[i].ptzText, lstrlen(FTI_Texts[i].ptzText));
		DeleteObject(SelectObject(hDC, hFont));
	}

	// End Draw
	EndPaint(m_hWnd, &psPaint);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Gets the specified point hyperlinks
INT WINAPI CAboutDlg::GetLinkIndex(POINT ptPoint)
{
	for (INT i = 0; i < _NumberOf(LI_Links); i++)
	{
		if (PtInRect(&LI_Links[i].rtRect, ptPoint))
		{
			return i;
		}
	}
	return -1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw Hyperlinks
VOID WINAPI CAboutDlg::PaintLinks(HDC hDC)
{
	HFONT hFont;
	LOGFONT lfFont;

	GetObject((HFONT) SendMessage(m_hWnd, WM_GETFONT, 0, 0), sizeof(LOGFONT), &lfFont);
	for (INT i = 0; i < _NumberOf(LI_Links); i++)
	{
		lfFont.lfUnderline = (i == m_iLinkIndex);
		hFont = (HFONT) SelectObject(hDC, CreateFontIndirect(&lfFont));
		SetTextColor(hDC, lfFont.lfUnderline ? COLOR_HotLink : COLOR_Link);
		TextOut(hDC, LI_Links[i].rtRect.left, LI_Links[i].rtRect.top,
			LI_Links[i].ptzTitle, lstrlen(LI_Links[i].ptzTitle));
		DeleteObject(SelectObject(hDC, hFont));
	}
	SetCursor(LoadCursor(NULL, (m_iLinkIndex != -1) ? IDC_HAND : IDC_ARROW));
	SetStatus((m_iLinkIndex == -1) ? NULL : LI_Links[m_iLinkIndex].ptzTip);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
