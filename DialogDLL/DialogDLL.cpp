// DialogDLL.cpp : 定義 DLL 應用程式的匯出函式。
#define _WIN32_WINNT 0x0501
#define WIN32_LEAN_AND_MEAN

#include "stdafx.h"
#include <windows.h>
#include "resource.h"
#include "DialogDLL.h"
#include <iostream>
#include <string>
using namespace std;

#define MESSAGE_MAP(MessageParam, MessageCallback)\
    if(message == MessageParam)\
        return MessageCallback(hwnd, message, wParam, lParam)

#define MESSAGE_MAP_COMMAND(Identifier, MessageCallback)\
    if((message == WM_COMMAND) && (LOWORD(wParam) == Identifier))\
    return MessageCallback(hwnd, message, wParam, lParam);


// FIXME: There is a better way by passing the hInstance as a parameter to StartDialog
HINSTANCE hInstance = 0;
int inputInt;
ReturnStruct r;
string gInTitle;
string gInText;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
		hInstance = (HINSTANCE)hModule;
	return TRUE;
}

ReturnStruct StartDialog(string inTitle, string inText)
{
	//inputInt = i;
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
	r.buttonState = false;
	r.s = "nothing yet";

	SetWindowTextA(hwnd, gInTitle.c_str());
	SetDlgItemTextA(hwnd, ID_StaticText, gInText.c_str());

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
	WCHAR out[50] = {};
	GetDlgItemText(hwnd, ID_TextBox, out, 50);
	wstring ws(out);
	string outString(ws.begin(), ws.end());

	r.buttonState = false;
	r.s = outString;

	OnDialogClose(hwnd, message, wParam, lParam);
	return TRUE;
}

BOOL OnDialogButtonSayHiClicked(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	WCHAR out[50] = {};
	GetDlgItemText(hwnd, ID_TextBox, out, 50);
	wstring ws(out);
	string outString(ws.begin(), ws.end());

	r.buttonState = true;
	r.s = outString;

	/*string s = "Hi, :D\n" + to_string(inputInt);
	MessageBoxA(hwnd, s.c_str(), "DLL", MB_OK);*/
	OnDialogClose(hwnd, message, wParam, lParam);
	return TRUE;
}