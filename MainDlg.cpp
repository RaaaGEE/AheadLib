


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Pretreatment
#include "Main.h"
#include "MainDlg.h"

#pragma warning(disable:4244)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CMainDlg Static member variables
HWND CMainDlg::m_hWnd = NULL;			// Dialog handle
BOOL CMainDlg::m_bShowOptions = TRUE;	// Whether Display Options
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Callback function
INT_PTR CALLBACK CMainDlg::MainDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		// dialog is created
		m_hWnd = hWnd;
		OnInitDialog(lParam);
		break;

	case WM_COMMAND:
		// Command processing
		OnCommand(wParam);
		break;

	case WM_SYSCOMMAND:
		// Command processing system
		OnSysCommand(wParam);
		break;

	case WM_SIZE:
		// Size changes
		OnSize(wParam, lParam);
		break;

	case WM_DROPFILES:
		// Drag file
		OnDropFiles(wParam);
		break;

	case WM_CLOSE:
		// Dialog box is destroyed
		OnClose();
		break;
	}

	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// initialization
VOID WINAPI CMainDlg::OnInitDialog(LPARAM lParam)
{
	UINT uTab = 16;

	// Settings icon
	SetClassLongPtr(m_hWnd, GCL_HICON, (LONG_PTR) LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_Main)));

	// Loading option
	CAheadLib::LoadOptions();

	// Hide options
	if (CIni::GetInt(INI_ShowOptions, TRUE) == FALSE)
	{
		OnOptions();
	}

	// Edit box
	SendDlgItemMessage(m_hWnd, IDC_DllFile, EM_LIMITTEXT, MAX_PATH, 0);
	SendDlgItemMessage(m_hWnd, IDC_CppFile, EM_LIMITTEXT, MAX_PATH, 0);
	SendDlgItemMessage(m_hWnd, IDC_OriginDll, EM_LIMITTEXT, MAX_PATH, 0);
	SendDlgItemMessage(m_hWnd, IDC_Preview, EM_SETTABSTOPS, 1, (LPARAM) &uTab);
	SetDlgItemText(m_hWnd, IDC_DllFile, (PTSTR) lParam);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Command processing
VOID WINAPI CMainDlg::OnCommand(WPARAM wParam)
{
	PSTR p;
	ALRESULT alResult;

	switch (LOWORD(wParam))
	{
	case IDOK:
		// Makefile
		alResult = CAheadLib::Generate(TRUE);
		MsgBox(CAheadLib::GetResult(alResult), (alResult <= ALResult_NotAllRedirect) ? MB_ICONINFORMATION : MB_ICONSTOP);
		break;

	case IDC_BrowseDll:
		OnBrowse(TRUE);
		break;

	case IDC_BrowseCpp:
		OnBrowse(FALSE);
		break;

	case IDC_Options:
		OnOptions();
		break;

	case IDC_About:
		CAboutDlg::Show(m_hWnd);
		break;

	case IDCANCEL:
		SendMessage(m_hWnd, WM_CLOSE, 0, 0);
		break;

	case IDC_DllFile:
		if (HIWORD(wParam) == EN_CHANGE)
		{
			// Automatically generated output file name
			if (GetDlgItemText(m_hWnd, IDC_DllFile, CAheadLib::m_tzDllFile, MAX_PATH))
			{
				TCHAR tzTemp[MAX_PATH];
				lstrcpy(tzTemp, CAheadLib::m_tzDllFile);
				PTSTR p = _StrRChr(tzTemp, '.');
				_ExIf(p == NULL, p = _StrEnd(tzTemp));
				lstrcpy(p, EXT_Cpp);
				SetDlgItemText(m_hWnd, IDC_CppFile, tzTemp);
				if (CAheadLib::m_bSystemPath)
				{
					*p = 0;
				}
				else
				{
					lstrcpy(p, TEXT("Org"));
				}
				p = _StrRChr(tzTemp, '\\');
				SetDlgItemText(m_hWnd, IDC_OriginDll, p ? p + 1 : tzTemp);
			}
			else
			{
				SetDlgItemText(m_hWnd, IDC_CppFile, NULL);
				SetDlgItemText(m_hWnd, IDC_OriginDll, NULL);
			}
		}
		break;

	case IDC_CppFile:
	case IDC_OriginDll:
		if (HIWORD(wParam) == EN_CHANGE)
		{
			// Get original DLL name, set button state
			GetDlgItemText(m_hWnd, IDC_CppFile, CAheadLib::m_tzCppFile, MAX_PATH);
			GetDlgItemTextA(m_hWnd, IDC_OriginDll, CAheadLib::m_szOriginDll, MAX_PATH);
			p = _AStrRChr(CAheadLib::m_szOriginDll, '\\');
			lstrcpyA(CAheadLib::m_szOrigin, p ? p + 1 : CAheadLib::m_szOriginDll);
			p = _AStrRChr(CAheadLib::m_szOrigin, '.');
			_ExIf(p, *p = 0);
			EnableWindow(GetDlgItem(m_hWnd, IDOK), CAheadLib::m_tzCppFile[0] && CAheadLib::m_szOrigin[0]);
			if ((LOWORD(wParam) == IDC_OriginDll) && m_bShowOptions)
			{
				CAheadLib::Generate();
			}
		}
		break;

	case IDC_CallRedirect:
	case IDC_CallInTime:
	case IDC_LoadInEntry:
	case IDC_LoadIfNeed:
	case IDC_JumpToOrigin:
	case IDC_CallOrigin:
	case IDC_MultiThread:
	case IDC_SystemPath:
	case IDC_GenerateHook:
		CAheadLib::GetOptions();
		if (m_bShowOptions)
		{
			CAheadLib::Generate();
		}
		break;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dialog System Command message
VOID WINAPI CMainDlg::OnSysCommand(WPARAM wParam)
{
	static BOOL s_bRestoreOptions = FALSE;

	if (wParam == SC_MAXIMIZE)
	{
		if (m_bShowOptions == FALSE)
		{
			m_bShowOptions = TRUE;
			s_bRestoreOptions = TRUE;
			CAheadLib::Generate();
		}
	}
	else if (wParam == SC_RESTORE)
	{
		if (s_bRestoreOptions)
		{
			m_bShowOptions = FALSE;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Size changes
VOID WINAPI CMainDlg::OnSize(WPARAM wParam, LPARAM lParam)
{
	HWND hCtrl;
	RECT rtRect;

	if (wParam != SIZE_MINIMIZED)
	{
		hCtrl = GetDlgItem(m_hWnd, IDC_Preview);
		GetWindowRect(hCtrl, &rtRect);
		MapWindowPoints(NULL, m_hWnd, (PPOINT) &rtRect, 2);
		rtRect.right = LOWORD(lParam) - 10;
		rtRect.bottom = HIWORD(lParam) - 10;
		MoveWindow(hCtrl, rtRect.left, rtRect.top, _RectWidth(rtRect), _RectHeight(rtRect), TRUE);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dialog destroy message
VOID WINAPI CMainDlg::OnClose()
{
	//WINDOWPLACEMENT wpWindow;

	// Save dialog location information
	//wpWindow.length = sizeof(WINDOWPLACEMENT);
	//GetWindowPlacement(m_hWnd, &wpWindow);
	//CIni::SetInt(INI_WindowLeft, wpWindow.rcNormalPosition.left);
	//CIni::SetInt(INI_WindowTop, wpWindow.rcNormalPosition.top);
	//CIni::SetInt(INI_WindowWidth, _RectWidth(wpWindow.rcNormalPosition));
	//CIni::SetInt(INI_WindowHeight, _RectHeight(wpWindow.rcNormalPosition));
	//CIni::SetInt(INI_WindowState, wpWindow.showCmd);

	// Save Options
	CAheadLib::SaveOptions();
	CIni::SetInt(INI_ShowOptions, m_bShowOptions);

	// Close dialog
	EndDialog(m_hWnd, 0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Show hidden options
VOID WINAPI CMainDlg::OnOptions()
{
	if (IsZoomed(m_hWnd))
	{
		ShowWindow(m_hWnd, SW_RESTORE);
		m_bShowOptions = FALSE;
	}
	else
	{
		m_bShowOptions = !m_bShowOptions;
	}

	if (m_bShowOptions)
	{
		CAheadLib::Generate();
		CenterWindow(714, 486);
	}
	else
	{
		CenterWindow(334, 162);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse files
VOID WINAPI CMainDlg::OnBrowse(BOOL bDllFile)
{
	OPENFILENAME ofnName;
	TCHAR tzFileName[MAX_PATH];

	tzFileName[0] = 0;
	ZeroMemory(&ofnName, sizeof(OPENFILENAME));
	ofnName.lStructSize = sizeof(OPENFILENAME);
	ofnName.hwndOwner = m_hWnd;
	ofnName.lpstrFile = tzFileName;
	ofnName.nMaxFile = MAX_PATH;
	ofnName.lpstrDefExt = bDllFile ? EXT_Dll : EXT_Cpp;
	ofnName.lpstrFilter = bDllFile ? FILTER_Dll FILTER_All: FILTER_Cpp FILTER_All;
	if (bDllFile)
	{
		ofnName.Flags = OFN_ENABLESIZING | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
		_ReturnIf(GetOpenFileName(&ofnName) == FALSE);
	}
	else
	{
		ofnName.Flags = OFN_ENABLESIZING | OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;
		_ReturnIf(GetSaveFileName(&ofnName) == FALSE);
	}
	SetDlgItemText(m_hWnd, bDllFile ? IDC_DllFile : IDC_CppFile, tzFileName);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
