#include <stdlib.h>
#include <string>
#include <windows.h>
#include <winbase.h>
#include "stdafx.h"
#include <string>
#include <Psapi.h>
#include <conio.h>
#include <vcclr.h> 
#include <tlhelp32.h>
#include <tchar.h>

#pragma region All File Attributes
#define Attrib_Readonly  0x00000001
#define Attrib_Hidden  0x00000002
#define Attrib_System  0x00000004
#define Attrib_Directory  0x00000010
#define Attrib_Archive  0x00000020
#define Attrib_Device   0x00000040
#define Attrib_Normal  0x00000080 
#define Attrib_Temporary  0x00000100
#define Attrib_SparseFile  0x00000200
#define Attrib_ReparsePoint  0x00000400
#define Attrib_Compressed  0x00000800
#define Attrib_Offline  0x00001000
#define Attrib_NotContentIndexed  0x00002000
#define Attrib_Encrypted  0x00004000
#define Attrib_Write_Through  0x80000000
#define Attrib_Overlapped  0x40000000
#define Attrib_NoBuffering  0x20000000
#define Attrib_RandomAccess  0x10000000
#define Attrib_SequentialScan  0x08000000
#define Attrib_DeleteOnClose  0x04000000
#define Attrib_BackupSemantics  0x02000000
#define Attrib_PosixSemantics  0x01000000
#define Attrib_OpenReparsePoint  0x00200000
#define Attrib_OpenNoRecall  0x00100000
#define Attrib_FirstPipeInstance  0x00080000
#pragma endregion

#pragma region Frequently Used File Attribute Combo


#define READ_ONLY_DIR Attrib_Readonly|Attrib_Directory
#define SYSTEM_DIR  Attrib_Hidden|Attrib_Directory
#define HIDDNE_SYSTEM_FILE Attrib_Hidden|Attrib_System

#pragma endregion

typedef struct FileTimeDetail
{
	FILETIME CreationTime;
	FILETIME LastAccessTime;
	FILETIME ModificationTime;
};

void SetFileData(WIN32_FIND_DATA* fileInfo,LPCWSTR name, unsigned int Attribute,FileTimeDetail *timeDetail ,long long size){
	
	DWORD lowsize = size;
	DWORD HightSize = size << 32;
	
	fileInfo->dwFileAttributes = Attribute;
	
	fileInfo->nFileSizeLow = size;
	
	fileInfo->nFileSizeHigh = HightSize;

	fileInfo->ftCreationTime = timeDetail->CreationTime;
	fileInfo->ftLastAccessTime = timeDetail->LastAccessTime;
	fileInfo->ftLastWriteTime = timeDetail->ModificationTime;
	
	wcscpy_s(fileInfo->cFileName,name);
}
void SetDirectoryData(WIN32_FIND_DATA* fileInfo, LPCWSTR name, unsigned int Attribute, FileTimeDetail *timeDetail){
	fileInfo->dwFileAttributes = Attribute|Attrib_Directory;
	fileInfo->ftCreationTime = timeDetail->CreationTime;
	fileInfo->ftLastAccessTime = timeDetail->LastAccessTime;
	fileInfo->ftLastWriteTime = timeDetail->ModificationTime;
	wcscpy_s(fileInfo->cFileName, name);
}