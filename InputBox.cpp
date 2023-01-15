#pragma once

#include "InputBox.h";

InputBox::InputBox(std::string label, std::string err_msg, std::string key) : label(label), err_msg(err_msg), key (key)
{}

const std::string& InputBox::get_input()
{
	return input_buffer;
}

void InputBox::render()
{
	ImGui::Text(label.c_str());
	ImGui::SameLine();
	strcpy_s(buffer, input_buffer.c_str());
	ImGui::InputText(key.c_str(), buffer, sizeof(buffer));
	ImGui::SameLine();
	if (error)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
		ImGui::Text(err_msg.c_str());
		ImGui::PopStyleColor();
	}
	input_buffer = buffer;
}

void InputBox::clear()
{
	input_buffer = "";
}

void InputBox::setBuffer(std::string& new_buffer)
{
	input_buffer = new_buffer;
}
