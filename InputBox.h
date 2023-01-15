#pragma once

#include "imgui.h"
#include "IRenderItem.h"
#include <iostream>
#include <string>

class InputBox: public IRenderItem
{
public:

	InputBox(std::string, std::string, std::string);
	void render() override;
	const std::string& get_input();
	void clear();
	void setBuffer(std::string&);
	bool error;
private:
	std::string label;
	std::string input_buffer;
	std::string err_msg;
	std::string key;
	char buffer[256];
};

