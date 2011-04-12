// git.cpp : Defines the entry point for the console application.
//
//TODO
//	����� ���������� �� .cfg
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
int plusDif;//������� ������ �� ��������� � ��� ��� ���� �� commit'�
int minusDif;//������� �������


void getData(){
	int numberOfProjects=0;
	std::ifstream f("Stals");
	f>>numberOfProjects;
	
	for(int i=0;i<numberOfProjects;++i){

		std::getline(f,projectDir);//����� ������ ����� ������
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
	std::string str;//������������ ����� ���������� ������
	std::string nick; //������ ��� �������� ����� �������� �� �������������
	f>>projectDir;
	
	
	while(str!="commit"){//���� ���� � ��������� �������� ��� �� ������
	
		projectDir=projectDir+" "+str;
	f>>str;
	}

	//	���� ����������� ����� files ��, ���� ��������� ����� changed, �� ����� ����� ������� ������ ��� �����.

	while(f>>str){

		


		//TODO:��� ����� ���� �� ���������� ����� ������ ����� ������� append �� ��� ��� ���� � ����� ������ ������ �� ����� < - ��� ������ �����, �� ����� �� ����������� �����.
		if(str=="Author:"){//��� ����� �������� ���
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
					//���� ������ ���� ���� � map , ����� ����������� ������ - ����� ������������� ���-�� plus � minus ��� ����� ����
					if(it==rawData.end()){ //���� ������ � ����� ����� ��� ������
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

//���������� raw � data ��� ���� ���������� � �������� � data ,���� raw ����� �����������
//���� ����� ���������� ������ �� ������ �
void editData(){
	/*minusDif=rawData["Stals"].minus-data[projectDir].minus;
		plusDif=rawData["Stals"].plus-data[projectDir].plus;*///��� ��� ������������ �������

	it=data.find(projectDir);
	if(it!=data.end()){
		it->second.minus=rawData["Stals"].minus;
		it->second.plus=rawData["Stals"].plus;
	}else{
		l.minus=rawData["Stals"].minus;
		l.plus=rawData["Stals"].plus;
		data.insert ( std::pair<std::string,lines >(projectDir,l) );
	
	}
	//l.clear();
	projectDir.empty();
}
//��������� � Stals ����� ���������� ���������� �� raw 
void saveData(){

}
int main()
{

	getData();
	parseRaw();
	//������ projectDir - ��� ���������� ������� �� �������� ��� ������� raw

	//������ �� ������ �������� ���-�� ������� � ������� ��� ���� ���������� �� ��������� � ���� ����������� � Stals , ���� ����� ���, ����� ��������� ����� ������ � ��� map
	editData();
	//��������� �� ������� � ����
	saveData();
	return 0;
}

