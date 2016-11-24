#include <iostream>
#include <windows.h>
#include <string>
#include "header.h"
using namespace std;

void main(void)
{
	cout << "testing app" << endl;

	/*HINSTANCE hInstance;  //HINSTANCE需要包含windows.h
	typedef int (Func)(int);  //定義函數原型
	typedef int (Func2)(HINSTANCE hInst, HINSTANCE h0, LPTSTR lpCmdLine, int nCmdShow);  //定義函數原型
	Func* pFunc = nullptr;  //聲明函數指針
	Func2* pFunc2 = nullptr;*/

	/*//返回由LoadLibrary加載的動態鏈接庫的實例句柄
	hInstance = LoadLibrary(L"DialogDLL.dll");

	if (!hInstance)
	{
		cout << "load dll failed" << endl;
		system("pause");
		return;
	}
	else
		cout << "dll loaded!" << endl;

	//找到DLL中ShowDialog函數的地址，函數名調用
	pFunc = (Func*)GetProcAddress(hInstance, "test");
	pFunc2 = (Func2*)GetProcAddress(hInstance, "DialogMain");

	if (!pFunc2)
	{
		cout << "load function failed" << endl;
		system("pause");
		return;
	}
	else
		cout << "function loaded!" << endl;

	//using my dl functions
	cout << "pFunc(3)=" << pFunc(3) << endl;*/




	HINSTANCE hDll;
	StartDialogFunc StartDialog;
	hDll = LoadLibrary(TEXT("DialogDLL.dll"));
	if (!hDll) {
		cout << "load function failed (2)" << endl;
		MessageBox(NULL, TEXT("Cannot load DialogDLL.dll"), NULL, MB_OK);
		return;
	}


	//let wcin can read chinese
	setlocale(LC_ALL, "");
	ios_base::sync_with_stdio(false); // 缺少的話，wcout wchar_t 會漏掉中文
	wcin.imbue(locale(""));
	wcout.imbue(locale(""));

	wstring win, win2;
	cout << "key in yout title:";
	getline(wcin, win);

	cout << "key in yout text:";
	getline(wcin, win2);

	StartDialog = (StartDialogFunc)GetProcAddress(hDll, "StartDialog");
	ReturnStruct r = StartDialog(win, win2);

	string btnstate;
	if (r.buttonState)
		btnstate = "[OK]";
	else
		btnstate = "[Cancel]";

	wcout << "returned text is:" << r.s << endl;
	cout << "you have pressed the " << btnstate << " button." << endl;

	FreeLibrary(hDll);
	system("pause");
	return;
}


