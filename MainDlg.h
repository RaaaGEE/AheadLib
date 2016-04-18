


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Pretreatment
#pragma once
#include <Windows.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CMainDlg class
class CMainDlg
{
public:
	static HWND m_hWnd;			// Dialog handle

private:
	static BOOL m_bShowOptions;	// Whether Display Options

public:
	// Dialog box is displayed
	inline static INT_PTR WINAPI Show(HINSTANCE hInstance, PCTSTR ptzCmdLine = NULL)
	{
		return DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_Main), NULL, MainDlgProc, (LPARAM) ptzCmdLine);
	}

private:
	// Callback function
	static INT_PTR CALLBACK MainDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	// initialization
	static VOID WINAPI OnInitDialog(LPARAM lParam);

	// Command processing
	static VOID WINAPI OnCommand(WPARAM wParam);

	// Command processing system
	static VOID WINAPI OnSysCommand(WPARAM wParam);

	// Size changes
	static VOID WINAPI OnSize(WPARAM wParam, LPARAM lParam);

	// shutdown
	static VOID WINAPI OnClose();

	// Show hidden options
	static VOID WINAPI OnOptions();

	// Browse files
	static VOID WINAPI OnBrowse(BOOL bDllFile);

	// Message Box
	inline static INT WINAPI MsgBox(PCTSTR ptzText = NULL, UINT uType = MB_ICONINFORMATION)
	{
		return MessageBox(m_hWnd, ptzText, STR_AppName, uType);
	}

	// Error box
	inline static INT WINAPI ErrorBox(PCTSTR ptzText = NULL)
	{
		return MsgBox(ptzText, MB_ICONSTOP);
	}

	// Center window
	inline static BOOL WINAPI CenterWindow(INT iWidth, INT iHeight)
	{
		return MoveWindow(m_hWnd,
			(GetSystemMetrics(SM_CXSCREEN) - iWidth) / 2,
			(GetSystemMetrics(SM_CYSCREEN) - iHeight) / 2,
			iWidth, iHeight, TRUE);
	}

	// Drag file
	inline static VOID WINAPI OnDropFiles(WPARAM wParam)
	{
		TCHAR tzFileName[MAX_PATH];
		DragQueryFile((HDROP) wParam, 0, tzFileName, MAX_PATH);
		DragFinish((HDROP) wParam);
		SetDlgItemText(m_hWnd, IDC_DllFile, tzFileName);
	}
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
