#pragma once
#include <iostream>

BOOL CALLBACK DialogProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
#define DllExport  __declspec(dllexport)
#define STDCALL    __cdecl

#if __cplusplus
extern "C" {
#endif

	DllExport ReturnStruct STDCALL StartDialog(std::string, std::string);

#if __cplusplus
};
#endif



BOOL OnDialogInit(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL OnDialogDestroy(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL OnDialogClose(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

BOOL OnDialogButtonExitClicked(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL OnDialogButtonSayHiClicked(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
