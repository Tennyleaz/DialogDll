#include <iostream>
#include <windows.h>
#include <string>
#include "header.h"
using namespace std;

void main(void)
{
	cout << "testing app" << endl;

	/*HINSTANCE hInstance;  //HINSTANCE�ݭn�]�twindows.h
	typedef int (Func)(int);  //�w�q��ƭ쫬
	typedef int (Func2)(HINSTANCE hInst, HINSTANCE h0, LPTSTR lpCmdLine, int nCmdShow);  //�w�q��ƭ쫬
	Func* pFunc = nullptr;  //�n����ƫ��w
	Func2* pFunc2 = nullptr;*/

	/*//��^��LoadLibrary�[�����ʺA�챵�w����ҥy�`
	hInstance = LoadLibrary(L"DialogDLL.dll");

	if (!hInstance)
	{
		cout << "load dll failed" << endl;
		system("pause");
		return;
	}
	else
		cout << "dll loaded!" << endl;

	//���DLL��ShowDialog��ƪ��a�}�A��ƦW�ե�
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
	StartDialog = (StartDialogFunc)GetProcAddress(hDll, "StartDialog");
	ReturnStruct r = StartDialog("I have a title", "I have a text");

	string btnstate;
	if (r.buttonState)
		btnstate = "OK";
	else
		btnstate = "Cancel";
	
	cout << "returned text is:" << r.s << endl;
	cout << "you have pressed the " << btnstate << " button." << endl;

	FreeLibrary(hDll);
	system("pause");
	return;
}


