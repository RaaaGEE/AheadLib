


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Pretreatment
#pragma once
#include "Define.h"
#include "Macro.h"
#include <Windows.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CIni class
class CIni
{
private:
	// INI file
	static TCHAR m_tzFileName[MAX_PATH];

public:
	// Setting INI file name
	inline static VOID WINAPI SetIniName()
	{
		GetModuleFileName(NULL, m_tzFileName, MAX_PATH);
		lstrcpy(_StrEnd(m_tzFileName) - _LengthOf(EXT_Ini), EXT_Ini);
	}

	// Setting INI file name
	inline static VOID WINAPI SetIniName(PCTSTR ptzFileName)
	{
		_StrToStr(m_tzFileName, ptzFileName);
	}

	// Get integer
	inline static UINT WINAPI GetInt(PCTSTR ptzKeyName, INT iDefault = 0, PCTSTR ptzSectionName = INI_Main)
	{
		return GetPrivateProfileInt(ptzSectionName, ptzKeyName, iDefault, m_tzFileName);
	}

	// Setting integer
	inline static BOOL WINAPI SetInt(PCTSTR ptzKeyName, INT iValue = 0, PCTSTR ptzSectionName = INI_Main)
	{
		TCHAR tzString[16];

		wsprintf(tzString, TEXT("%d"), iValue);
		return WritePrivateProfileString(ptzSectionName, ptzKeyName, tzString, m_tzFileName);
	}

	// Get string
	inline static DWORD WINAPI GetString(PCTSTR ptzKeyName, PTSTR ptzReturnedString,
		DWORD dwSize = MAX_PATH, PCTSTR ptzDefault = NULL, PCTSTR ptzSectionName = INI_Main)
	{
		return GetPrivateProfileString(ptzSectionName, ptzKeyName, ptzDefault, ptzReturnedString,
			dwSize, m_tzFileName);
	}

	// Setting string
	inline static BOOL WINAPI SetString(PCTSTR ptzKeyName, PCTSTR ptzString = NULL, PCTSTR ptzSectionName = INI_Main)
	{
		return WritePrivateProfileString(ptzSectionName, ptzKeyName, ptzString, m_tzFileName);
	}

	// Get structure
	inline static BOOL WINAPI GetStruct(PCTSTR ptzKeyName, PVOID pvStruct, UINT uSize, PCTSTR ptzSectionName = INI_Main)
	{
		return GetPrivateProfileStruct(ptzSectionName, ptzKeyName, pvStruct, uSize, m_tzFileName);
	}

	// Setting structure
	inline static BOOL WINAPI SetStruct(PCTSTR ptzKeyName, PVOID pvStruct, UINT uSize, PCTSTR ptzSectionName = INI_Main)
	{
		return WritePrivateProfileStruct(ptzSectionName, ptzKeyName, pvStruct, uSize, m_tzFileName);
	}

	// Get section
	inline static DWORD WINAPI GetSection(PTSTR ptzReturnBuffer, DWORD dwSize, PCTSTR ptzSectionName = INI_Main)
	{
		return GetPrivateProfileSection(ptzSectionName, ptzReturnBuffer, dwSize, m_tzFileName);
	}

	// Setting section
	inline static DWORD WINAPI SetSection(PCTSTR ptzString, PCTSTR ptzSectionName = INI_Main)
	{
		return WritePrivateProfileSection(ptzSectionName, ptzString, m_tzFileName);
	}

	// Get section name
	inline static DWORD WINAPI GetSectionNames(PTSTR ptzReturnBuffer, DWORD dwSize)
	{
		return GetPrivateProfileSectionNames(ptzReturnBuffer, dwSize, m_tzFileName);
	}
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
