#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Music.h";
#include "Priority_Linkedlist.h";

class AppData
{
public:	
	static AppData* instance();
	DSA::DoublyLinkedList<std::string> creditsList;
	DSA::Priority_Linkedlist<Music> musicList;
private:
	AppData();

	const std::string credits_path = "./db/credits.txt";
	void load_credits();
	static AppData* _instance;
};

AppData* AppData::_instance = nullptr;

AppData* AppData::instance()
{
	if (_instance == nullptr)
		_instance = new AppData();
	return _instance;
}

void AppData::load_credits()
{
	std::ifstream in;
	in.open(credits_path.c_str(), std::ios::in);
	if (in.fail())
	{
		std::string owner = "Zain Ul Din";
		creditsList.push(owner);
	}
	else if (std::ifstream::traits_type::eof() == in.peek())
	{
		std::string owner = "Zain Ul Din";
		creditsList.push(owner);
	}
	else
	{
		std::string aux;
		while (std::getline(in, aux, '\n'))
		{
			creditsList.push_back(aux);
		}
	}
	in.close();
}

AppData::AppData()
{	
	load_credits();
}

