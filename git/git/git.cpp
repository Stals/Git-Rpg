// git.cpp : Defines the entry point for the console application.
//
//TODO
//	брать дериктории из .cfg
//
//
#include "stdafx.h"
#include <iostream>
#include <Windows.h>
int main()
{
	while(true){
		system("C:/msysgit/msysgit/bin/sh.exe --login -i 'C:/My Dropbox/Programming/BigProjects/C++/GitRPG/main.gs'");
		
		//¬ этом месте мы уже получили raw файл, теперь его нужно перегнать в нужный формат
		
		Sleep(120000); //each 2 hours
	}
	return 0;
}

