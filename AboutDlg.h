


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Pretreatment
#pragma once
#include <Windows.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CAboutDlg class
class CAboutDlg
{
public:
	static TCHAR m_tzStatus[64];	// Status message string

private:
	static HWND m_hWnd;				// Window handle
	static BOOL m_bSplash;			// Whether to display Splash
	static INT m_iLinkIndex;		// Current Hyperlinks

public:
	// Display the About dialog box
	static VOID WINAPI Show(HWND hParent = NULL);

	// Splash to display the About dialog box
	static VOID WINAPI Splash(HWND hParent = NULL, UINT uTimer = 1000);

	// Close the About dialog box
	static VOID WINAPI Close(UINT uTimer = 0);

	// Setting status information
	static VOID WINAPI SetStatus(PCTSTR ptzText = NULL);

private:
	// About dialog box callback function
	static INT_PTR CALLBACK AboutDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	// Draw dialog box
	static VOID WINAPI OnPaint();

	// Gets the specified point hyperlinks
	static INT WINAPI GetLinkIndex(POINT ptPoint);

	// Draw Hyperlinks
	static VOID WINAPI PaintLinks(HDC hDC);
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
