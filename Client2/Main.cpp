#include <Windows.h>
#include <CommCtrl.h>
#include <tchar.h>
#include "resource.h"
#include "ReturnStruct.h"

#define STDCALL    __cdecl
typedef ReturnStruct (STDCALL *StartDialogFunc)(wstring, wstring);

#pragma comment(linker, \
  "\"/manifestdependency:type='Win32' "\
  "name='Microsoft.Windows.Common-Controls' "\
  "version='6.0.0.0' "\
  "processorArchitecture='*' "\
  "publicKeyToken='6595b64144ccf1df' "\
  "language='*'\"")

#pragma comment(lib, "ComCtl32.lib")

bool isChildActive;

INT_PTR CALLBACK DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:  //WM_CREATE is not used for DialogProc !
	{
		SetDlgItemTextA(hwnd, ID_EditTitle, "I am title");
		SetDlgItemTextA(hwnd, ID_EditText, "I am text");
		break;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			HMODULE dllHandler;
			StartDialogFunc StartDialog;

			//getting the dll and the function in dll
			dllHandler = LoadLibrary(TEXT("DialogDLL.dll"));
			if (!dllHandler) {
				MessageBox(NULL, TEXT("Cannot load DialogDLL.dll"), NULL, MB_OK);
				return -1;
			}

			StartDialog = (StartDialogFunc)GetProcAddress(dllHandler, "StartDialog");
			if (!StartDialog) {
				MessageBox(NULL, TEXT("Cannot load function StartDialog"), NULL, MB_OK);
				return -1;
			}

			isChildActive = true;

			//getting text boxt items
			WCHAR out[150] = {};
			GetDlgItemTextW(hwnd, ID_EditTitle, out, 150);
			wstring ws(out);

			memset(out, 0, 150);
			GetDlgItemTextW(hwnd, ID_EditText, out, 150);
			wstring ws2(out);

			//make the input structure, start the dll dialog
			ReturnStruct r = StartDialog(ws, ws2);

			//change the text after dll returns
			if (r.buttonState == true)
			{
				SetDlgItemTextA(hwnd, ID_ButtonIndicator, "You pressed the [OK] button.");
				if (r.s.length() > 0)
					SetDlgItemTextW(hwnd, ID_ReturnText, r.s.c_str());
				else
					SetDlgItemTextA(hwnd, ID_ReturnText, "(Nothing to show)");
			}
			else
				SetDlgItemTextA(hwnd, ID_ButtonIndicator, "You pressed the [Cancel] button.");

			FreeLibrary(dllHandler);
		}
		case IDCANCEL:
			SendMessage(hwnd, WM_CLOSE, 0, 0);
			return TRUE;
		}
		break;

	case WM_CLOSE:
		if (isChildActive)
		{
			isChildActive = false;
			return true;
		}

		if (MessageBox(hwnd, TEXT("Close the program?"), TEXT("Close"), MB_ICONQUESTION | MB_YESNO) == IDYES)
		{
			DestroyWindow(hwnd);
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
	HWND hwnd;
	MSG msg;
	BOOL isSuccess;
	InitCommonControls();

	isChildActive = false;

	hwnd = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, DialogProc, 0);
	ShowWindow(hwnd, nCmdShow);

	while ((isSuccess = GetMessage(&msg, 0, 0, 0)) != 0) {
		if (isSuccess == -1)
			return -1;

		if (!IsDialogMessage(hwnd, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}