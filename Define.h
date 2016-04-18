


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Pretreatment
#pragma once


#define _CHS
#define _WINVER					0x0400

#if (_WINVER >= 0x0500)
#define UNICODE
#define _UNICODE
#endif

#include <Windows.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Program information
#define VER_Major				2
#define VER_Minor				2
#define VER_Release				151 
#define VER_Build				659  
#define VER_Version				MAKELONG(MAKEWORD(VER_Major, VER_Minor), VER_Release)

#define _Stringizing(v)			#v
#define _VerJoin(a, b, c, d)	_Stringizing(a.b.c.d)

#define STR_BuildDate			TEXT(__DATE__)
#define STR_BuildTime			TEXT(__TIME__)
#define STR_BuilDateTime		TEXT(__DATE__) TEXT(" ") TEXT(__TIME__)
#define STR_Version				TEXT(_VerJoin(VER_Major, VER_Minor, VER_Release, VER_Build))

#define STR_AppName				TEXT("AheadLib")
#define STR_Author				TEXT("Yonsm")
#define STR_Corporation			TEXT("Yonsm.com")
#define STR_Web					TEXT("www.luocong.com/bbs")
#define STR_Email				TEXT("Yonsm@163.com")
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// extension names
#define EXT_Chm					TEXT(".chm")
#define EXT_Dll					TEXT(".dll")
#define EXT_Exe					TEXT(".exe")
#define EXT_Ini					TEXT(".ini")
#define EXT_Cpp					TEXT(".cpp")
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INI Keys
#define INI_Main				STR_AppName
#define INI_WindowLeft			TEXT("WindowLeft")
#define INI_WindowTop			TEXT("WindowTop")
#define INI_WindowWidth			TEXT("WindowWidth")
#define INI_WindowHeight		TEXT("WindowHeight")
#define INI_WindowState			TEXT("WindowState")
#define INI_ShowSplash			TEXT("ShowSplash")

#define INI_ShowOptions			TEXT("ShowOptions")
#define INI_CallRedirect		TEXT("CallRedirect")
#define INI_LoadIfNeed			TEXT("LoadIfNeed")
#define INI_JumpToOrign			TEXT("JumpToOrign")
#define INI_MultiThread			TEXT("MultiThread")
#define INI_SystemPath			TEXT("SystemPath")
#define INI_GenerateHook		TEXT("GenerateHook")
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Regular string
#define	STR_CheckUpdate			TEXT("Check for updates")
#define	STR_VisitWeb			TEXT("Visit Website")
#define	STR_WriteEmail			TEXT("Write to author")

#define STR_CheckUpdateTip		TEXT("On Internet to check for software updates")
#define STR_VisitWebTip			TEXT("access ") STR_Web
#define STR_WriteEmailTip		TEXT("Write to ") STR_Email

#define STR_VisitWebUrl			TEXT("http://") STR_Web
#define STR_WriteEmailUrl		TEXT("mailto:") STR_Email TEXT("?Subject=") STR_AppName

#define STR_VersionStamp		TEXT("Version: ") STR_Version
#define STR_BuildStamp			TEXT("Compile: ") STR_BuilDateTime
#define STR_Description			TEXT("Quickly and easily generate Trojan DLL code.")
#define STR_Copyright			TEXT("All rights reserved (C) 2004 ") STR_Corporation TEXT(", all rights reserved.")
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 文件扩展名过滤器
#define FILTER_All				TEXT("All files(*.*)\0*.*\0")
#define FILTER_Dll				TEXT("DLL file(*.dll)\0*.dll\0")
#define FILTER_Cpp				TEXT("CPP file(*.cpp)\0*.cpp\0")
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
