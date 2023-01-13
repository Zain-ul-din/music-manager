#pragma once

#include <string>
#include "ImGuiFileDialog.h";
#include "IRenderItem.h"
#include "Event.h";

class FileDialog: public IRenderItem
{
public:
	FileDialog(std::string&, std::string&);
	void render() override;

	void open();

	Event <void, std::string&> onFileSelect;
private:
	std::string filesFilter;
	std::string key;
};
