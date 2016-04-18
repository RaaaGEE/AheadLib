


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Pretreatment
#pragma once
#include "Main.h"
#include "MapFile.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor, map file is read-only
WINAPI CMapFile::CMapFile(PCTSTR ptzFileName)
{
	// open file
	_Assert(ptzFileName);
	m_dwSize = 0;
	m_pvFile = NULL;
	m_hMapping = NULL;
	m_hFile = _CreateFileForRead(ptzFileName);
	if (m_hFile != INVALID_HANDLE_VALUE)
	{
		// get file size
		m_dwSize = GetFileSize(m_hFile, NULL);
		if ((m_dwSize != INVALID_FILE_SIZE) && m_dwSize)
		{
			// Create file mapping
			m_hMapping = CreateFileMapping(m_hFile, NULL, PAGE_READONLY, 0, 0, NULL);
			if (m_hMapping)
			{
				// Mapping file
				m_pvFile = MapViewOfFile(m_hMapping, FILE_MAP_READ, 0, 0, 0);
			}
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor, map files to be read
WINAPI CMapFile::CMapFile(PCTSTR ptzFileName, DWORD dwSize)
{
	// open file
	_Assert(ptzFileName && dwSize);
	m_dwSize = 0;
	m_pvFile = NULL;
	m_hMapping = NULL;
	m_hFile = _CreateFileForAppend(ptzFileName);
	if (m_hFile != INVALID_HANDLE_VALUE)
	{
		// Create file mapping
		m_dwSize = dwSize;
		m_hMapping = CreateFileMapping(m_hFile, NULL, PAGE_READWRITE, 0, m_dwSize, NULL);
		if (m_hMapping)
		{
			// Mapping file
			m_pvFile = MapViewOfFile(m_hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
WINAPI CMapFile::~CMapFile()
{
	if (m_pvFile)
	{
		UnmapViewOfFile(m_pvFile);
	}
	if (m_hMapping)
	{
		CloseHandle(m_hMapping);
	}
	if (m_hFile)
	{
		CloseHandle(m_hFile);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
