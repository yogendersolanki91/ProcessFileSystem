#include <windows.h>
#include <winbase.h>
#include <stdlib.h>
#include <string>
#include <list>
#include <iostream>
#include "./include/dokan.h"
#include "./include/fileinfo.h"
#include "FileSystemHelper.h"
#include "ProcessManagerBasic.h"
#include "MixingHelepr.h"
using namespace System;
NTSTATUS CreateFileOperation(
	LPCWSTR					FileName,
	DWORD					DesiredAccess,
	DWORD					ShareMode,
	DWORD					CreationDisposition,
	DWORD					FlagsAndAttributes,
	PDOKAN_FILE_INFO		DokanFileInfo)
{
	std::cout << "Create file ";
	std::wprintf(FileName);
	std::cout << std::endl;
	//	std::wcout << _T(FileName) << std::endl;
	return STATUS_SUCCESS;
}
NTSTATUS CreateDirectoryOperation(
	LPCWSTR					FileName,
	PDOKAN_FILE_INFO		DokanFileInfo)
{
	std::cout << "create dir  " << *FileName;
	return STATUS_MEDIA_WRITE_PROTECTED;
}
NTSTATUS OpenDirectoryOperation(
	LPCWSTR					FileName,
	PDOKAN_FILE_INFO		DokanFileInfo)
{
	std::wstring x = std::wstring(FileName);
	std::cout << "Called opendirecorty()";// << FileName << "\n";
	std::wprintf(FileName);
	if (DokanFileInfo->IsDirectory)
		std::cout << "DIrectory ask";
	std::cout << std::endl;

	return STATUS_SUCCESS;
}
void CloseFileOperation(
	LPCWSTR					FileName,
	PDOKAN_FILE_INFO		DokanFileInfo)
{

}
void CleanupOperation(
	LPCWSTR					FileName,
	PDOKAN_FILE_INFO		DokanFileInfo)
{}
NTSTATUS ReadFileOperation(
	LPCWSTR				FileName,
	LPVOID				Buffer,
	DWORD				BufferLength,
	LPDWORD				ReadLength,
	LONGLONG			Offset,
	PDOKAN_FILE_INFO	DokanFileInfo)
{

	return STATUS_CRC_ERROR;
}
NTSTATUS WriteFileOperation(
	LPCWSTR		FileName,
	LPCVOID		Buffer,
	DWORD		NumberOfBytesToWrite,
	LPDWORD		NumberOfBytesWritten,
	LONGLONG			Offset,
	PDOKAN_FILE_INFO	DokanFileInfo)
{
	std::cout << "Write file " << *FileName;
	return STATUS_MEDIA_WRITE_PROTECTED;
}
NTSTATUS GetFileInformationOperation(
	LPCWSTR							FileName,
	LPBY_HANDLE_FILE_INFORMATION	HandleFileInformation,
	PDOKAN_FILE_INFO				DokanFileInfo)
{
	SYSTEMTIME st;
	FILETIME ft;
	GetSystemTime(&st);
	SystemTimeToFileTime(&st, &ft);
	HandleFileInformation->ftCreationTime = ft;
	HandleFileInformation->ftLastWriteTime = ft;
	HandleFileInformation->ftLastAccessTime = ft;
	HandleFileInformation->dwFileAttributes = (0x80);
	return STATUS_SUCCESS;

}
NTSTATUS FindFilesOperation(LPCWSTR	FileName,
	PFillFindData	FillFindData, // function pointer
	PDOKAN_FILE_INFO	DokanFileInfo){
	HANDLE	handle = (HANDLE)DokanFileInfo->Context;
	BOOL	opened = FALSE;
	FileTimeDetail *filetime = new FileTimeDetail();
	WIN32_FIND_DATAW	findData;
	array<String^> ^FileNames = gcnew array<String^> {"Memory", "File", "Network", "Module", "Processor"};
	std::cout << "File find exceute ";
	std::wcout << FileName;
	std::cout << "\n";
	String ^path = gcnew String(FileName);
	SYSTEMTIME st;
	FILETIME ft;
	GetSystemTime(&st);
	SystemTimeToFileTime(&st, &ft);
	filetime->CreationTime = ft;
	filetime->LastAccessTime = ft;
	filetime->ModificationTime = ft;
	if (path->Length == 1){
		std::list<PROCESSENTRY32> all = GetAllProcess();
		std::list<PROCESSENTRY32>::iterator i;
		for (i = all.begin(); i != all.end(); ++i)
		{
			String ^ID = i->th32ProcessID.ToString();
			String ^name = gcnew String(i->szExeFile);
			SetDirectoryData(&findData, StringToWchar(ID + " {" + name + "}"), 0, filetime);
			FillFindData(&findData, DokanFileInfo);
		}

		return STATUS_SUCCESS;
	}
	else
	{
		for each (String ^DataFile in FileNames)
		{
			SetFileData(&findData, StringToWchar(DataFile), Attrib_Normal, filetime, 890);
			FillFindData(&findData, DokanFileInfo);
		}
		return STATUS_SUCCESS;
	}

}



NTSTATUS DeleteFileOperation(
	LPCWSTR				FileName,
	PDOKAN_FILE_INFO	DokanFileInfo)
{
	std::cout << "Delet file " << *FileName;
	return STATUS_MEDIA_WRITE_PROTECTED;
}
NTSTATUS DeleteDirectoryOperation(
	LPCWSTR				FileName,
	PDOKAN_FILE_INFO	DokanFileInfo)
{
	std::cout << "Delete Drectory " << *FileName;
	return STATUS_MEDIA_WRITE_PROTECTED;
}
NTSTATUS MoveFileOperation(
	LPCWSTR				FileName, // existing file name
	LPCWSTR				NewFileName,
	BOOL				ReplaceIfExisting,
	PDOKAN_FILE_INFO	DokanFileInfo)
{
	std::cout << "Move File " << *FileName;
	return STATUS_MEDIA_WRITE_PROTECTED;
}
NTSTATUS LockFileOperation(
	LPCWSTR				FileName,
	LONGLONG			ByteOffset,
	LONGLONG			Length,
	PDOKAN_FILE_INFO	DokanFileInfo)
{
	return STATUS_LOCK_NOT_GRANTED;
}
NTSTATUS SetEndOfFileOperation(
	LPCWSTR				FileName,
	LONGLONG			ByteOffset,
	PDOKAN_FILE_INFO	DokanFileInfo)
{
	std::cout << "Set EOF File " << *FileName;
	return STATUS_MEDIA_WRITE_PROTECTED;
}
NTSTATUS SetAllocationSizeOperation(
	LPCWSTR				FileName,
	LONGLONG			AllocSize,
	PDOKAN_FILE_INFO	DokanFileInfo)
{
	std::cout << "set Allocation size " << *FileName;
	return STATUS_MEDIA_WRITE_PROTECTED;
}
NTSTATUS SetFileAttributesOperation(
	LPCWSTR				FileName,
	DWORD				FileAttributes,
	PDOKAN_FILE_INFO	DokanFileInfo)
{
	std::cout << "Set File Attrib " << *FileName;
	return STATUS_MEDIA_WRITE_PROTECTED;
}
NTSTATUS UnlockFileOperation(
	LPCWSTR				FileName,
	LONGLONG			ByteOffset,
	LONGLONG			Length,
	PDOKAN_FILE_INFO	DokanFileInfo)
{
	return STATUS_SUCCESS;
}
NTSTATUS GetFileSecurityOperation(
	LPCWSTR					FileName,
	PSECURITY_INFORMATION	SecurityInformation,
	PSECURITY_DESCRIPTOR	SecurityDescriptor,
	ULONG				BufferLength,
	PULONG				LengthNeeded,
	PDOKAN_FILE_INFO	DokanFileInfo)
{
	return STATUS_DATA_ERROR;
}
NTSTATUS SetFileSecurityOperation(
	LPCWSTR					FileName,
	PSECURITY_INFORMATION	SecurityInformation,
	PSECURITY_DESCRIPTOR	SecurityDescriptor,
	ULONG				/*SecurityDescriptorLength*/,
	PDOKAN_FILE_INFO	DokanFileInfo)
{
	std::cout << "Set FIle security  " << *FileName;
	return STATUS_MEDIA_WRITE_PROTECTED;
}
NTSTATUS GetVolumeInformationOperation(
	LPWSTR		VolumeNameBuffer,
	DWORD		VolumeNameSize,
	LPDWORD		VolumeSerialNumber,
	LPDWORD		MaximumComponentLength,
	LPDWORD		FileSystemFlags,
	LPWSTR		FileSystemNameBuffer,
	DWORD		FileSystemNameSize,
	PDOKAN_FILE_INFO	/*DokanFileInfo*/)
{
	wcscpy_s(VolumeNameBuffer, VolumeNameSize / sizeof(WCHAR), L"DOKAN");
	*VolumeSerialNumber = 0x19831116;
	*MaximumComponentLength = 256;
	*FileSystemFlags = FILE_CASE_SENSITIVE_SEARCH |
		FILE_CASE_PRESERVED_NAMES |
		FILE_SUPPORTS_REMOTE_STORAGE |
		FILE_UNICODE_ON_DISK |
		FILE_PERSISTENT_ACLS;

	wcscpy_s(FileSystemNameBuffer, FileSystemNameSize / sizeof(WCHAR), L"Dokan");

	return STATUS_SUCCESS;
}
NTSTATUS Unmount(
	PDOKAN_FILE_INFO	DokanFileInfo)
{
	//logw(L"Unmount");
	return STATUS_SUCCESS;
}