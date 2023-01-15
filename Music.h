#pragma once

#include <iostream>
#include <string>
#include <sstream>

class Music
{
public:
	explicit Music();
	Music(std::string, std::string, std::string, bool);
	std::string music_name, author_name, music_path;
	bool is_fav;

	bool operator <= (const Music& rhs);
	bool operator == (const Music& rhs);

	std::string to_string();
private:

	static const char alphabet[26];
	static const char Alphabet[26];

	static bool IsLunderR(char l, char r);
};



