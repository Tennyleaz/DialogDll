#pragma once
// header.h
#ifndef __HEADER_H__
#define __HEADER_H__

#include <windows.h>

using namespace std;
struct ReturnStruct
{
	bool buttonState;
	string s;
};



#define STDCALL    __cdecl
typedef ReturnStruct(STDCALL *StartDialogFunc)(string, string);

#endif /* __HEADER_H__ */