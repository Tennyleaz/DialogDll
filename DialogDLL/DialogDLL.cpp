// DialogDLL.cpp : 定義 DLL 應用程式的匯出函式。
#include "stdafx.h"
#include <windows.h>
#include "resource.h"
#include "DialogDLL.h"
#include <string>
//#include "atlconv.h"
using namespace std;


// FIXME: There is a better way by passing the hInstance as a parameter to StartDialog
HINSTANCE hInstance = 0;
int inputInt;
ReturnStruct r;
wstring gInTitle;
wstring gInText;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
		hInstance = (HINSTANCE)hModule;
	return TRUE;
}

//the exported function for clients to call in DLL
ReturnStruct StartDialog(wstring inTitle, wstring inText)
{
	gInTitle = inTitle;
	gInText = inText;

	DialogBox(hInstance, MAKEINTRESOURCE(IDD_CHILD_DIALOG), NULL, DialogProc);

	return r;
}

BOOL CALLBACK DialogProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	MESSAGE_MAP(WM_INITDIALOG, OnDialogInit);
	//MESSAGE_MAP(WM_DESTROY, OnDialogDestroy);
	//MESSAGE_MAP(WM_CLOSE, OnDialogClose);

	MESSAGE_MAP_COMMAND(IDD_BUTTON_EXIT, OnDialogButtonExitClicked);
	MESSAGE_MAP_COMMAND(IDD_BUTTON_SAYHI, OnDialogButtonSayHiClicked);

	return FALSE;
}

BOOL OnDialogInit(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//USES_CONVERSION;

	r.buttonState = false;
	r.s = L"nothing yet";

	SetWindowTextW(hwnd, gInTitle.c_str());
	SetDlgItemTextW(hwnd, ID_StaticText, gInText.c_str());

	return TRUE;
}

BOOL OnDialogDestroy(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PostQuitMessage(0);
	return TRUE;
}

BOOL OnDialogClose(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	DestroyWindow(hwnd);
	return TRUE;
}

BOOL OnDialogButtonExitClicked(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	WCHAR out[150] = {};
	GetDlgItemTextW(hwnd, ID_TextBox, out, 150);
	wstring ws(out);
	//string outString(ws.begin(), ws.end());

	r.buttonState = false;
	r.s = ws;

	OnDialogClose(hwnd, message, wParam, lParam);
	return TRUE;
}

BOOL OnDialogButtonSayHiClicked(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	WCHAR out[150] = {};
	GetDlgItemTextW(hwnd, ID_TextBox, out, 150);
	wstring ws(out);
	//string outString(ws.begin(), ws.end());

	r.buttonState = true;
	r.s = ws;

	/*string s = "Hi, :D\n" + to_string(inputInt);
	MessageBoxA(hwnd, s.c_str(), "DLL", MB_OK);*/
	OnDialogClose(hwnd, message, wParam, lParam);
	return TRUE;
}