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

//add pma appendixB list of tool
BOOL findProcess()
{
	PROCESSENTRY32  pe = { sizeof(PROCESSENTRY32) };
	HANDLE          ss = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	BOOL            rslt;

	for (rslt = Process32First(ss, &pe); rslt == TRUE; rslt = Process32Next(ss, &pe)) {
		if (!_stricmp(pe.szExeFile, "Firefox.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "Wireshark.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "apateDNS.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "Autoruns.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "bindiff.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "idaq.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "idaq64.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "Procmon.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "x64dbg.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "x32dbg.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "ollydbg.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "ImmunityDebugger.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "VBoxTray.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "VBoxService.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "msedge.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "chrome.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "VirtualBox.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "javaw.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "x96dbg.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "idag.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "idaw.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "windbg.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "dnSpy.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "HxD.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "Scylla_x64.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "Scylla_x86.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "regmon.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "procexp.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "procexp64.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "Tcpview.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "smsniff.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "FakeNet.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "netmon.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "PEiD.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "LordPE.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "PE-bear.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "PPEE.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "die.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "diel.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "pexplorer.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "depends.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "ResourceHacker.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "FileAlyzer2.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "processhacker.exe")) {
			return TRUE;
		}
		else if (!_stricmp(pe.szExeFile, "Regshot-x64-Unicode.exe")) {
			return TRUE;
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

	if (findProcess()) {
		do_or_die();
	}

	system("curl -help");
	do_or_die();

	return 0;
}