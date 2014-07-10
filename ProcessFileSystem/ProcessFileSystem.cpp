// MixTest.cpp : main project file.

#include <windows.h>
#include <winbase.h>
#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include "DokanWork.h"

using namespace System;
int main(array<System::String ^> ^args)
{
	int status;
	int command;
	//procsFSoperation *procsFS = new procsFSoperation();
	PDOKAN_OPERATIONS dokanOperations = new DOKAN_OPERATIONS();
	PDOKAN_OPTIONS dokanOptions = (PDOKAN_OPTIONS)malloc(sizeof(DOKAN_OPTIONS));
	ZeroMemory(dokanOptions, sizeof(DOKAN_OPTIONS));
	dokanOptions->Version = DOKAN_VERSION;
	dokanOptions->ThreadCount = 0;
	dokanOptions->Options |= DOKAN_OPTION_KEEP_ALIVE;
	ZeroMemory(dokanOperations, sizeof(DOKAN_OPERATIONS));
	dokanOperations->CreateFile = CreateFileOperation;
	dokanOperations->OpenDirectory = OpenDirectoryOperation;
	dokanOperations->CreateDirectory = CreateDirectoryOperation;
	dokanOperations->Cleanup = CleanupOperation;
	dokanOperations->CloseFile = CloseFileOperation;
	dokanOperations->ReadFile = ReadFileOperation;
	dokanOperations->WriteFile = WriteFileOperation;
	dokanOperations->FlushFileBuffers = nullptr;
	dokanOperations->GetFileInformation = GetFileInformationOperation;
	dokanOperations->FindFiles = FindFilesOperation;
	dokanOperations->FindFilesWithPattern = nullptr;
	dokanOperations->SetFileAttributes = SetFileAttributesOperation;
	dokanOperations->SetFileTime = nullptr;
	dokanOperations->DeleteFile = DeleteFileOperation;
	dokanOperations->DeleteDirectory = DeleteDirectoryOperation;
	dokanOperations->MoveFile = MoveFileOperation;
	dokanOperations->SetEndOfFile = SetEndOfFileOperation;
	dokanOperations->SetAllocationSize = SetAllocationSizeOperation;
	dokanOperations->LockFile = LockFileOperation;
	dokanOperations->UnlockFile = UnlockFileOperation;
	dokanOperations->GetFileSecurity = GetFileSecurityOperation;
	dokanOperations->SetFileSecurity = SetFileSecurityOperation;
	dokanOperations->GetDiskFreeSpace = nullptr;
	dokanOperations->GetVolumeInformation = GetVolumeInformationOperation;
	dokanOperations->Unmount = Unmount;
	if (dokanOperations == NULL)
	{
		return EXIT_FAILURE;
	}
	wchar_t* drive = L"x";
	dokanOptions->MountPoint = drive;
	status = DokanMain(dokanOptions, dokanOperations);

	switch (status) {
	case DOKAN_SUCCESS:
		fprintf(stderr, "Success");
		break;
	case DOKAN_ERROR:
		fprintf(stderr, "Error");
		break;
	case DOKAN_DRIVE_LETTER_ERROR:
		fprintf(stderr, "Bad Drive letter");
		break;
	case DOKAN_DRIVER_INSTALL_ERROR:
		fprintf(stderr, "Can't install driver");
		break;
	case DOKAN_START_ERROR:
		fprintf(stderr, "Driver something wrong");
		break;
	case DOKAN_MOUNT_ERROR:
		fprintf(stderr, "Can't assign a drive letter");
		break;
	case DOKAN_MOUNT_POINT_ERROR:
		fprintf(stderr, "Mount point error");
		break;
	default:
		fprintf(stderr, "Unknown error: %d", status);
		break;
	}

	DokanUnmount(*drive);
	free(dokanOptions);
	free(dokanOperations);


	_getch();
	Console::ReadLine();
}
