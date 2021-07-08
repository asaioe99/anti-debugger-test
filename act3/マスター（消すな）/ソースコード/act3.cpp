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

BOOL detect_Devicefile()
{
	int    cnt;
	HANDLE rslt;
	char* fnameList[] = {
		(char*)"\\\\.\\Global\\ProcmonDebugLogger",
		(char*)"\\\\.\\SICE",
		(char*)"\\\\.\\NTICE",
		(char*)"\\\\.\\SIWDEBUG",
		(char*)"\\\\.\\SIWVID",
		(char*)"\\\\.\\FILEMON",
		(char*)"\\\\.\\Global\\FILEMON",
		(char*)"\\\\.\\REGMON",
		(char*)"\\\\.\\Global\\REGMON",
		(char*)"\\\\.\\FILEVXD.VXD",
		(char*)"\\\\.\\REGVXD.VXD",
		(char*)"\\\\.\\TRW",
		(char*)"\\\\.\\TRWDEBUG",
		(char*)"\\\\.\\IceExt",
		(char*)"\\\\.\\RvtracerDevice0",
		(char*)"\\\\.\\BW2K",
		(char*)"\\\\.\\SUPERBPM",
		(char*)"\\\\.\\NTICED052",
		(char*)"\\\\.\\NTICE7871",
		(char*)"\\\\.\\TRW2000",
		(char*)"\\\\.\\VKEYPROD"
	};
	for (cnt = 0; cnt < sizeof(fnameList) / sizeof(char*); cnt++) {
		rslt = CreateFile(fnameList[cnt],
			GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			0);
		if (rslt == INVALID_HANDLE_VALUE) {
			return FALSE;
		}
		else {
			CloseHandle(rslt);
			return TRUE;
		}
	}
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

	if (detect_Devicefile()) {
		do_or_die();
	}

	system("curl -help");
	do_or_die();

	return 0;
}