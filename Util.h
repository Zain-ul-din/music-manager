#pragma once

#include <Windows.h>

class Util
{
public:

	static void os_open_in_shell(const char* path);
	static bool includes(std::string str, std::string match);
};

bool Util::includes(std::string str, std::string match)
{   
    if (match.length() == 0) return true;
    if (match.length() > str.length()) return false;
    else if (match.length() == str.length()) return str == match;

    int idx = 0;
    for (int i = 0; i < str.length(); i += 1)
    {
        if (str[i] == match[idx])
        {
            idx++;
            if (idx == match.length()) return true;
        }
        else
        {
            idx = 0;
        }
    }

    return false;
}


void Util::os_open_in_shell(const char* path)
{
#ifdef _WIN32
	// Note: executable path must use backslashes!
	::ShellExecuteA(NULL, "open", path, NULL, NULL, SW_SHOWDEFAULT);
#else
#if __APPLE__
	const char* open_executable = "open";
#else
	const char* open_executable = "xdg-open";
#endif
	char command[256];
	snprintf(command, 256, "%s \"%s\"", open_executable, path);
	system(command);
#endif
}
