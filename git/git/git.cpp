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
//
struct lines {
	int plus;
	int minus;
	void clear(){plus=0;minus=0;}
}l;
std::map<std::string,lines> data; //data from "your name" file
std::map<std::string,lines> rawData; //data from raw file
std::map<std::string,lines>::iterator it;


std::string projectDir;
int plusDif;//разница плюсов по сравнению с тем что было до commit'а
int minusDif;//разница минусов


void getData(){
	int numberOfProjects=0;
	std::ifstream f("Stals");
	f>>numberOfProjects;
	
	for(int i=0;i<numberOfProjects;++i){

		std::getline(f,projectDir);//чтобы убрать конец строки
		std::getline(f,projectDir);
		f>>l.plus;
		f>>l.minus;

		data.insert ( std::pair<std::string,lines >(projectDir,l) );
		l.clear();
		projectDir.clear();
	}
	f.close();

}
void parseRaw(){
	std::ifstream f("raw");
	std::string str;//используется чтобы перебирать сторки
	std::string nick; //хранит ник человека комит которого мы просматриваем
	f>>projectDir;
	
	
	while(str!="commit"){//если путь с пробелами собираем его по словам
	
		projectDir=projectDir+" "+str;
	f>>str;
	}

	//	Если встречается слово files то, если следующее слово changed, то после этого следает нужное нам число.

	while(f>>str){

		


		//TODO:Ник может быть из нескольких слово поэтом нужно сделать append до тех пор пока в слове первый символ не будет < - что значит почта, но почта не обязательно будет.
		if(str=="Author:"){//тут можно получить ник
			f>>nick;
		}

		if(str=="files"){
			f>>str;
			if(str=="changed,"){
				f>>l.plus;
				f>>str;
				if(str=="insertions(+),"){
					f>>l.minus;
					it=rawData.find(nick);
					//Если такого ника нету в map , тогда добавляется запись - иначе увеличивается кол-вл plus и minus для этого ника
					if(it==rawData.end()){ //если записи с таким ником еще небыло
						rawData.insert ( std::pair<std::string,lines >(nick,l) );
					}else{
						it->second.plus+=l.plus;
						it->second.minus+=l.minus;
					}
				}
				l.clear();
			}
		}
	}
	
}

//Сравнивает raw с data для этой дериктории и изменяет в data ,если raw число увеличилось
//Если такой дериктории небыло то создаёт её
//TODO: передавать сюда строку с ником человека для которого меняем
void editData(){
	/*minusDif=rawData["Stals"].minus-data[projectDir].minus;
		plusDif=rawData["Stals"].plus-data[projectDir].plus;*///это для высчитывания разницы

	it=data.find(projectDir);
	if(it!=data.end()){
		it->second.minus=rawData["Stals"].minus;
		it->second.plus=rawData["Stals"].plus;
	}else{
		l.minus=rawData["Stals"].minus;
		l.plus=rawData["Stals"].plus;
		data.insert ( std::pair<std::string,lines >(projectDir,l) );
	
	}
	l.clear();
	projectDir.empty();
}
//Сохраняет В Stals новую информацию полученную из raw 
void saveData(){
	std::ofstream f("Stals");
	f<<data.size()<<std::endl;
	for(it=data.begin();it!=data.end();++it){
		f<<it->first<<std::endl;
		f<<it->second.plus<<std::endl;
		f<<it->second.minus<<std::endl;
	}

	f.close();
}
int main()
{

	getData();
	parseRaw();
	//Сейчас projectDir - это дериктория проекта из которого был получен raw

	//Сейчас мы должны сравнить кол-во  плючсов и минусов для этой дериктории по сравнению с этой дерикторией в Stals , если такой нет, тогда добавляем новую запись в тот map
	editData();
	//сохраняем всё обратно в файл(ы)
	saveData();
	return 0;
}

