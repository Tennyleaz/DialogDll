#include <Windows.h>
#include <CommCtrl.h>
#include <tchar.h>
#include "resource.h"
#include "ReturnStruct.h"

#define STDCALL    __cdecl
typedef ReturnStruct (STDCALL *StartDialogFunc)(string, string);

#pragma comment(linker, \
  "\"/manifestdependency:type='Win32' "\
  "name='Microsoft.Windows.Common-Controls' "\
  "version='6.0.0.0' "\
  "processorArchitecture='*' "\
  "publicKeyToken='6595b64144ccf1df' "\
  "language='*'\"")

#pragma comment(lib, "ComCtl32.lib")

bool isChildActive;

INT_PTR CALLBACK DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			HMODULE hDll;
			StartDialogFunc StartDialog;

			hDll = LoadLibrary(TEXT("DialogDLL.dll"));
			if (!hDll) {
				MessageBox(NULL, TEXT("Cannot load DialogDLL.dll"), NULL, MB_OK);
				return -1;
			}

			StartDialog = (StartDialogFunc)GetProcAddress(hDll, "StartDialog");
			if (!StartDialog) {
				MessageBox(NULL, TEXT("Cannot load function StartDialog"), NULL, MB_OK);
				return -1;
			}

			isChildActive = true;
			ReturnStruct r = StartDialog("I am title", "I am text");

			if (r.buttonState == true)
			{
				if (r.s.length() > 0)
					SetDlgItemTextA(hDlg, ID_ReturnText, r.s.c_str());
				else
					SetDlgItemTextA(hDlg, ID_ReturnText, "(Nothing to show)");
			}

			/*HWND wnd = FindWindow(NULL, L"MyApp");
			if (wnd)
			{
				MessageBox(NULL, TEXT("MyApp found"), NULL, MB_OK);
			}*/
		}
		case IDCANCEL:
			SendMessage(hDlg, WM_CLOSE, 0, 0);
			return TRUE;
		}
		break;

	case WM_CLOSE:
		if (isChildActive)
		{
			isChildActive = false;
			return true;
		}

		if (MessageBox(hDlg, TEXT("Close the program?"), TEXT("Close"), MB_ICONQUESTION | MB_YESNO) == IDYES)
		{
			DestroyWindow(hDlg);
		}
		return TRUE;

	case WM_DESTROY:
		if (isChildActive)
		{
			isChildActive = false;
			return true;
		}

		PostQuitMessage(0);
		return TRUE;
	}

	return FALSE;
}

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE h0, LPTSTR lpCmdLine, int nCmdShow)
{
	HWND hDlg;
	MSG msg;
	BOOL ret;
	InitCommonControls();

	isChildActive = false;

	hDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, DialogProc, 0);
	ShowWindow(hDlg, nCmdShow);

	while ((ret = GetMessage(&msg, 0, 0, 0)) != 0) {
		if (ret == -1)
			return -1;

		if (!IsDialogMessage(hDlg, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}