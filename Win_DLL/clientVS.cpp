// clientVS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <conio.h>
#include <iostream>
using std::cout;
using std::endl;


int main()
{
	cout << "to continue == press space key" << endl;
	_getch();
	HMODULE hMod = LoadLibraryA("serverVS.dll");
	if (hMod == NULL)
	{
		cout << "cannot load library" << endl;
		return 0;
	}
	cout << " library is loaded" << endl;
	cout << "to continue == press space key" << endl;
	_getch();

	typedef int(*MultT)(int, int);
	MultT pFn = (MultT)GetProcAddress(hMod, "Mult");
	if (pFn == NULL)
	{
		cout << "cannot get Mult function address ..." << endl;
		FreeLibrary(hMod);
		return 0;
	}
	
	int nRes = pFn(2, 10);
	cout <<"pFn(2, 10) == "<< nRes << endl;
	FreeLibrary(hMod);
	cout << "to continue == press space key" << endl;
	_getch();
    return 0;
}

