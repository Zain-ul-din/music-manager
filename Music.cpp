#pragma once

#include "Music.h"

Music::Music(std::string music_name, std::string author_name, std::string music_path, bool is_fav)
	: music_name(music_name), author_name(author_name), is_fav(is_fav), music_path(music_path) {}

std::string Music::to_string()
{
	std::stringstream ss;
	ss << music_name << "`" << author_name << "`" << music_path << "`" << is_fav;
	return ss.str();
}

bool Music::IsLunderR(char l, char r)
{
	for (int i = 0; i < 26; i++) {
		if (alphabet[i] == l || Alphabet[i] == l) return true;
		if (alphabet[i] == r || Alphabet[i] == r) return false;
	}
	return l < r;
}

bool Music::operator<= (const Music& rhs)
{
	if (music_name == rhs.music_name) return true;

	int minLen = rhs.music_name.length() < music_name.length() ? rhs.music_name.length() : music_name.length();

	for (int i = 0; i < minLen; i += 1)
	{
		if (music_name[i] == rhs.music_name[i]) continue;
		return IsLunderR(music_name[i], rhs.music_name[i]);
	}

	return true;
}

const char Music::alphabet[26] = {
	'a' , 'b' , 'c' , 'd' , 'e' , 'f' , 'g' , 'h' , 'i' , 'j' , 'k' , 'l' , 'm' , 'n' , 'o' ,'p' ,
	'q' , 'r'  , 's' , 't' , 'u' , 'v' , 'w' , 'x' , 'y' ,'z'
};

const char Music::Alphabet[26] = {
			'A' , 'B' , 'C' , 'D' , 'E' , 'F' , 'G' , 'H' , 'I' , 'J' , 'K' , 'L' , 'M' , 'N' , 'O' ,'P' ,
			'Q' , 'R'  , 'S' , 'T' , 'U' , 'V' , 'W' , 'X' , 'Y' ,'Z'
};

bool Music::operator== (const Music& rhs)
{
	return music_name == rhs.music_name;
}

Music::Music()
{
	music_name = "";
	author_name = "";
	is_fav = false;
}