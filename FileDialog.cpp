#pragma once

#include "FileDialog.h";

FileDialog::FileDialog(std::string& filesFilter, std::string& key) : filesFilter
(std::move(filesFilter)), key(std::move(key)) {}

void FileDialog::open()
{
	ImGuiFileDialog::Instance()->OpenDialog(key.c_str(), "Choose File", filesFilter.c_str(), ".");
}

void FileDialog::render()
{
	if (ImGuiFileDialog::Instance()->Display(key.c_str()))
	{
		// action if OK
		if (ImGuiFileDialog::Instance()->IsOk())
		{
			std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
			// std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
			onFileSelect.invoke(filePathName);
		}

		ImGuiFileDialog::Instance()->Close();
	}
}
