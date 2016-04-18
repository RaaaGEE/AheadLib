


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Pretreatment
#pragma once
#include <Windows.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Result Code
typedef enum tagALRESULT
{
	ALResult_Success,
	ALResult_NotAllRedirect,
	ALResult_InvalidArgs,
	ALResult_OpenDllFile,
	ALResult_InvalidPeFile,
	ALResult_NoExportTable,
	ALResult_HeapAlloc,
	ALResult_WriteCppFile
}
ALRESULT, *PALRESULT;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Export function type
typedef enum tagEXPORTTYPE
{
	ET_NONAME,
	ET_CPP,
	ET_STD,
	ET_FAST,
	ET_CDECL
}
EXPORTTYPE, *PEXPORTTYPE;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Text Results
const PTSTR STR_AheadLib_Result[] =
{
	TEXT("Code generated successfully."),
	TEXT("Code is successfully generated, but not all functions can be forwarded directly."),
	TEXT("Parameters incomplete."),
	TEXT("Open DLL with errors."),
	TEXT("Invalid PE."),
	TEXT("Enter the file does not exist in the export table."),
	TEXT("Unable to allocate memory - kidding! What broken machines?"),
	TEXT("Unable to write to CPP file.")
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Type
typedef DWORD (WINAPI *UNDECORATESYMBOLNAME)(PCSTR, PSTR, DWORD, DWORD);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CAheadLib class
class CAheadLib
{
public:
	static BOOL m_bCallRedirect;							// Direct forwarding function
	static BOOL m_bLoadIfNeed;								// Loading DLL when needed
	static BOOL m_bJumpToOrigin;							// Skip directly to original function
	static BOOL m_bMultiThread ;							// It supports multi-threading
	static BOOL m_bSystemPath;								// System Path
	static BOOL m_bGenerateHook;							// Generate code HOOK
	static TCHAR m_tzDllFile[MAX_PATH];						// Enter DLL
	static TCHAR m_tzCppFile[MAX_PATH];						// Output CPP
	static CHAR m_szOriginDll[MAX_PATH];					// Original DLL
	static CHAR m_szOrigin[MAX_PATH];						// Original name

private:
	static HMODULE m_hDbgHelp;								// DbgHelp Module handle
	static UNDECORATESYMBOLNAME m_pUnDecorateSymbolName;	// UnDecorateSymbolName Function pointer

public:
	// Generation
	static ALRESULT WINAPI Generate(BOOL bWriteCppFile = FALSE);

	// Setting options available state
	static VOID WINAPI SetOptionsEnabled();

	// Loading option settings from INI
	static VOID WINAPI LoadOptions();

	// Save option
	static VOID WINAPI SaveOptions();

	// Read option
	static VOID WINAPI GetOptions();

	// Get Results Text
	inline static PCTSTR WINAPI GetResult(ALRESULT alResult)
	{
		return STR_AheadLib_Result[alResult];
	}

private:
	// Generate code
	static DWORD WINAPI GenerateCode(PSTR pszBuffer, PSTR* ppszNames, DWORD dwBase, DWORD dwCount, BOOL& bLoadOrigin);

	// Generate export indicator
	static BOOL WINAPI GenerateExport(PSTR& pszBuffer, PSTR* ppszNames, DWORD dwBase, DWORD dwCount);

	// Generating function
	static VOID WINAPI GenerateFunction(PSTR& pszBuffer, PSTR pszName, DWORD dwBase, DWORD dwIndex);

	// Generate legal function name
	static VOID WINAPI GenerateDeclaration(PSTR pszDeclaration, PSTR pszCallName, PSTR pszName, DWORD Ordinals);

	// RVA convert file offset
	static DWORD WINAPI RvaToOffset(const PIMAGE_NT_HEADERS pInh, DWORD dwRva);

	// Analyzing Export function type
	static EXPORTTYPE WINAPI GetExportType(PSTR pszName, PSTR& pAt);

	// Generate parameter list
	inline static VOID WINAPI GenerateParam(PSTR pszBuffer, INT iParamCount);

	// Generate #pragma export indicator
	static VOID WINAPI PragmaExport(PSTR& pszBuffer, BOOL& bPragmaExport, DWORD Ordinals,
		PCSTR pszName = NULL, BOOL bRedirect = FALSE);

	// Write to CPP file
	static BOOL WINAPI WriteCppFile(PCSTR pszBuffer, DWORD dwSize);

	// Copy the data and move the pointer
	inline static VOID WINAPI CopyString(PSTR& pszDest, PCSTR pszSrc, SIZE_T sztSize)
	{
		CopyMemory(pszDest, pszSrc, sztSize);
		pszDest += sztSize;
	}

	// Determining whether export name may be forwarded
	inline static BOOL WINAPI CanRedirect(PCSTR pszExportName)
	{
		return pszExportName && m_bCallRedirect && IsStringLegality(pszExportName);
	}

	// To determine whether the string is pure numeric string
	inline static BOOL WINAPI IsStringNumberic(PCSTR pszString)
	{
		for (PCSTR p = pszString; *p; p++)
		{
			if ((*p < '0') || (*p > '9'))
			{
				return FALSE;
			}
		}
		return TRUE;
	}

	// Analyzing string is a legitimate function strings
	inline static BOOL WINAPI IsStringLegality(PCSTR pszString)
	{
		for (PCSTR p = pszString; *p; p++)
		{
			if (((*p == '_') ||
				((*p >= 'A') && (*p <= 'Z')) ||
				((*p >= 'a') && (*p <= 'z')) ||
				((*p >= '0') && (*p <= '9'))) == FALSE)
			{
				return FALSE;
			}
		}
		return TRUE;
	}
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
