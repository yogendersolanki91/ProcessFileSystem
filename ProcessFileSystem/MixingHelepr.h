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
using namespace System;

LPCWSTR StringToWchar(String ^s){

	pin_ptr<const WCHAR> returnValue=PtrToStringChars(s);
	
	return returnValue;
}
LPCWSTR AppendWCHAR(String ^main,LPCWSTR append){
	
	main->Concat(gcnew String(append));
	Console::WriteLine(main);
	return StringToWchar(main);
}

DWORD StringToDWORD(String ^num){
	return UInt32::Parse(num);
}
String^ DWORDToString(DWORD num){
	return num.ToString();
}
