// git.cpp : Defines the entry point for the console application.
//
//TODO
//	брать дериктории из .cfg
//
//
#include "stdafx.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <map>
#include <fstream>
struct lines {
	int plus;
	int minus;
}l;
std::map<std::string,lines> data;
int numberOfProjects=0;
std::string projectDir;

void getData(){

	std::ifstream f("Stals");
	f>>numberOfProjects;

	for(int i=0;i<numberOfProjects;++i){

		f>>projectDir;
		f>>l.plus;
		f>>l.minus;

		data.insert ( std::pair<std::string,lines >(projectDir,l) );
		
	}


}
int main()
{
	
	getData();


	return 0;
}

