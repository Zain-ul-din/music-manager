#pragma once

#include "gui.h"
#include "FileDialog.h"
#include "InputBox.h"
#include <iostream>
#include <string>
#include "AppData.h";
#include "Util.h";


class App: public IRenderItem
{
public:
	
	explicit App();
	void start_app();
	void render() override;
private:
	Renderer* renderer;
	FileDialog* file_dialog;

	const float window_width  = 800;
	const float window_height = 600;
	ImVec2 window_pos;
	bool show_quit_popup;

	InputBox* input_music_name, *input_author_name;
	std::string input_file_path;
	
	InputBox* input_search_box_home;
	InputBox* input_search_box_fav;
	
	Music* music_to_edit;


	enum class Menu_State
	{
		Home,
		Edit,
		Favourites,
		AboutUs
	};

	// App Components
	void header();
	void home();
	void about_us();
	void add_music();
	void Favourites();

	Menu_State menu_state;
	
	/// Helpers

	inline void music_renderer(const char*,const char*, bool,bool = false);
	inline void music_renderer(Music& music, int u_id);
	inline void music_renderer(int u_id, Music& music);
	inline void same_line();
	inline void space(int);
	inline void clear_edits();

	DSA::Node<Music>* node_to_del;
	Event<void, Menu_State> on_state_change;
	
	/// Constant

	const std::string about_app_text = "Introducing Random Music Player - the ultimate, cross-platform solution for all your music needs. Whether you're looking to manage your  music library or simply jam out to your favorite tunes, this lightweight app has got you covered. With its sleek and user-friendly interface, Random Music Player makes it easy to take control of your music and elevate your listening experience.";
};


void App::start_app()
{
	renderer->render(*this);
}

void App::render()
{
	ImGui::Begin("Randoms Music App", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);
	ImGui::SetWindowSize(ImVec2(window_width, window_height));
	window_pos.x = (ImGui::GetIO().DisplaySize.x - window_width) * 0.5f;
	window_pos.y = (ImGui::GetIO().DisplaySize.y - window_height) * 0.3f;
	ImGui::SetWindowPos(window_pos);
	{
		header();
	}
	ImGui::End();
}

void App::header()
{

	if (ImGui::Button("Music")) { menu_state = Menu_State::Home;  on_state_change.invoke(menu_state); }		 same_line();
	if (ImGui::Button("Add Music")) { menu_state = Menu_State::Edit;  on_state_change.invoke(menu_state); }		 same_line();
	if (ImGui::Button("favourites")) { menu_state = Menu_State::Favourites; on_state_change.invoke(menu_state); } same_line();
	if (ImGui::Button("About Us")) { menu_state = Menu_State::AboutUs;  on_state_change.invoke(menu_state); }	 same_line();
	if (ImGui::Button("Quit"))	show_quit_popup = true;

	ImGui::Spacing();
	ImGui::Separator();

	switch (menu_state)
	{
	case Menu_State::Home:
		home();
		break;
	case Menu_State::Edit:
		add_music();
		break;
	case Menu_State::Favourites:
		Favourites();
		break;
	case Menu_State::AboutUs:
		about_us();
		break;
	}

	ImVec2 windowSize = ImGui::GetWindowSize();



	if (show_quit_popup)
	{
		ImGui::OpenPopup("Quit Application");
		if (ImGui::BeginPopupModal("Quit Application", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text("Are you sure you want to quit the application?");

			ImGui::SetCursorPosX((windowSize.x - ImGui::CalcTextSize("Yes").x) / 5.5f);
			if (ImGui::Button("Yes"))
			{
				exit(0);
			}

			ImGui::SetCursorPosX((windowSize.x - ImGui::CalcTextSize("No ").x) / 5);
			ImGui::SameLine();
			if (ImGui::Button("No "))
			{
				show_quit_popup = false;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}
}

App::App()
{
	menu_state = Menu_State::Home;
	renderer = Renderer::Instance();
	std::string fileFilter = "Sound files (*.aif *.aiff *.flac *.m4a *.mp3 *.ogg *.wav *.wma *.amr *.m4p *.m4b *.mpc *.ape *.aac *.au *.ra *.snd *.mid *.midi *.rmi *.wv *.ac3 *.dts){.aif,.aiff,.flac,.m4a,.mp3,.ogg,.wav,.wma,.amr,.m4p,.m4b,.mpc,.ape,.aac,.au,.ra,.snd,.mid,.midi,.rmi,.wv,.ac3,.dts}";
	std::string key = "sound_key";

	file_dialog = new FileDialog(fileFilter, key);

	input_author_name = new InputBox("Enter Author Name", "", " ");
	input_music_name = new InputBox("Enter Music Name ", "Music Already Exsists", "  ");
	input_search_box_home = new InputBox("Search Music", "Not Found", "   ");
	input_search_box_fav = new InputBox("Search Music", "Not Found", "     ");

	input_file_path = "";
	file_dialog->onFileSelect += [&](std::string& path)->void {	input_file_path = path;	};
	on_state_change += [&](Menu_State newState)->void {	music_to_edit = nullptr; clear_edits();	};
	node_to_del = nullptr;
	music_to_edit = nullptr;
}

void App::about_us()
{
	space(10);

	ImGui::TextWrapped(about_app_text.c_str());

	space(5);
	ImVec2 windowSize = ImGui::GetWindowSize();

	ImGui::SetCursorPosX((windowSize.x - ImGui::CalcTextSize("Build on the top of c++ and DSA Concepts").x) / 2);
	ImGui::Text("Build on the top of c++ and DSA Concepts");

	space(15);
	ImGui::SetCursorPosX((windowSize.x - ImGui::CalcTextSize("CREATED BY").x) / 2);
	ImGui::Text("CREATED BY");

	space(2);

	AppData::instance()->creditsList.for_each([&](auto* node)->void {
		ImGui::SetCursorPosX((windowSize.x - ImGui::CalcTextSize(node->data.c_str()).x) / 2);
		ImGui::Text(node->data.c_str());
		});

	ImGui::SetCursorPosY(windowSize.y - 30);
	ImGui::SetCursorPosX((windowSize.x - ImGui::CalcTextSize("Github Link").x) / 2);
	if (ImGui::Button("Github Link"))
		Util::os_open_in_shell("https://github.com/Zain-ul-din");
}

void App::Favourites()
{
	space(10);
	ImVec2 windowSize = ImGui::GetWindowSize();
	{
		ImGui::SetCursorPosX((windowSize.x - ImGui::CalcTextSize("Favourite Musics").x) / 2);
		ImGui::Text("Favourite Musics");
	}

	{
		space(5);
		ImGui::SetCursorPosX((windowSize.x - 300) / 2);
		ImGui::PushItemWidth(200);
		{
			input_search_box_fav->render();
		}
		ImGui::PopItemWidth();
	}


	space(10);
	ImGui::Separator();
	space(1);
	music_renderer("Music Name", "Author Name", false, true);
	space(1);

	ImGui::BeginChild("Scrolling");
	{
		int idx = 0;
		AppData::instance()->musicList.list.for_each([&](Music& music)->void {
			if (Util::includes(music.music_name, input_search_box_fav->get_input()) && music.is_fav)
			{
				ImGui::Separator();
				music_renderer(idx, music);
				space(2);
				idx += 1;
			}
			});

		if (idx == 0 && !AppData::instance()->musicList.list.is_empty() && input_search_box_fav->get_input() != "")
			input_search_box_fav->error = true;
		else input_search_box_fav->error = false;
	}
	ImGui::EndChild();
}

void App::home()
{
	space(10);
	ImVec2 windowSize = ImGui::GetWindowSize();
	{
		ImGui::SetCursorPosX((windowSize.x - ImGui::CalcTextSize("Welcome to Randoms Music Player").x) / 2);
		ImGui::Text("Welcome to Randoms Music Player");
	}

	{
		space(5);
		ImGui::SetCursorPosX((windowSize.x - 300) / 2);
		ImGui::PushItemWidth(200);
		{
			input_search_box_home->render();
		}
		ImGui::PopItemWidth();
	}

	space(10);
	ImGui::Separator();
	space(1);
	music_renderer("Music Name", "Author Name", false, true);
	space(1);


	ImGui::BeginChild("Scrolling");
	{
		int idx = 0;
		AppData::instance()->musicList.list.for_each([&](Music& music)->void {
			if (Util::includes(music.music_name, input_search_box_home->get_input()))
			{
				ImGui::Separator();
				music_renderer(music, idx);
				space(2);
				idx += 1;
			}
			});

		if (idx == 0 && !AppData::instance()->musicList.list.is_empty() && input_search_box_home->get_input() != "")
			input_search_box_home->error = true;
		else input_search_box_home->error = false;
	}
	ImGui::EndChild();

	if (node_to_del != nullptr)
	{
		AppData::instance()->musicList.list.remove(node_to_del);
		node_to_del = nullptr;
	}
}

void App::add_music()
{
	bool isEdits = music_to_edit != nullptr;
	space(10);
	ImVec2 windowSize = ImGui::GetWindowSize();
	{
		ImGui::SetCursorPosX((windowSize.x - ImGui::CalcTextSize(isEdits ? "Edit Music" : "Add Music").x) / 2);
		ImGui::Text(isEdits ? "Edit Music" : "Add Music");
	}
	{
		space(5);
		ImGui::SetCursorPosX((windowSize.x - 402) / 2);
		ImGui::PushItemWidth(200);
		{
			input_music_name->error = false;

			AppData::instance()->musicList.list.for_each([&](Music& music)->void {
				if (music.music_name == input_music_name->get_input() && !(music == *music_to_edit))
					input_music_name->error = true;
				});

			input_music_name->render();
		}
		ImGui::PopItemWidth();

		space(5);
		ImGui::SetCursorPosX((windowSize.x - 402) / 2);
		ImGui::PushItemWidth(200);
		{
			input_author_name->render();
		}
		ImGui::PopItemWidth();

		space(3);
		std::string text_path = "Music File Path: " + input_file_path;
		ImGui::SetCursorPosX((windowSize.x - ImGui::CalcTextSize(text_path.c_str()).x) / 2);
		ImGui::Text(text_path.c_str());

		space(3);
		{
			file_dialog->render();

			ImGui::SetCursorPosX((windowSize.x - ImGui::CalcTextSize("Select File").x) / 2);
			if (ImGui::Button("Select File"))
			{
				file_dialog->open();
			}
		}

		{
			space(10);
			ImGui::SetCursorPosX((windowSize.x - ImGui::CalcTextSize(isEdits ? "Save Edits" : "Add Music To List").x) / 2);

			if (ImGui::Button(isEdits ? "Save Edits" : "Add Music To List"))
			{
				if (
					input_author_name->get_input() != "" &&
					input_file_path != "" && input_music_name->get_input() != ""
					&& !input_music_name->error
					) {
					if (!isEdits)
					{
						Music music_obj(
							input_music_name->get_input(),
							input_author_name->get_input(),
							input_file_path,
							false
						);

						AppData::instance()->musicList.prioritize(music_obj);
						clear_edits();
					}
					else
					{
						music_to_edit->music_name = input_music_name->get_input();
						music_to_edit->author_name = input_author_name->get_input();
						music_to_edit->music_path = input_file_path;
						clear_edits();

						menu_state = Menu_State::Home;
						input_search_box_home->setBuffer(music_to_edit->music_name);
						music_to_edit = nullptr;
					}
				}
			}
		}

	}

}

/// Helpers

inline void App::same_line()
{
	ImGui::SameLine();
	ImGui::Spacing();
	ImGui::SameLine();
}

inline void App::space(int n)
{
	for (int i = 0; i < n; i += 1)
		ImGui::Spacing();
}

inline void App::music_renderer(const char* music_name, const char* author_name, bool is_fav, bool is_header)
{
	ImVec2 windowSize = ImGui::GetWindowSize();
	ImGui::SetCursorPosX((windowSize.x - ImGui::CalcTextSize("....................").x) / 10);
	ImGui::Text(music_name);
	ImGui::SameLine();
	ImGui::SetCursorPosX((windowSize.x - ImGui::CalcTextSize("....................").x) / 2.5f);
	ImGui::Text(author_name);
	ImGui::SameLine();
	ImGui::SetCursorPosX((windowSize.x - ImGui::CalcTextSize("favourites").x) / 1.5f);
	if (is_header)
		ImGui::Text("favourite");
	ImGui::SameLine();
	ImGui::SetCursorPosX((windowSize.x - ImGui::CalcTextSize("Controls").x) / 1.15f);
	ImGui::Text("Controls");
}

void App::music_renderer(Music& music, int u_id)
{
	ImVec2 windowSize = ImGui::GetWindowSize();
	ImGui::SetCursorPosX((windowSize.x - ImGui::CalcTextSize("....................").x) / 10);
	ImGui::Text(music.music_name.c_str());
	ImGui::SameLine();
	ImGui::SetCursorPosX((windowSize.x - ImGui::CalcTextSize("....................").x) / 2.5f);
	ImGui::Text(music.author_name.c_str());
	ImGui::SameLine();
	ImGui::SetCursorPosX((windowSize.x - ImGui::CalcTextSize("favourites").x) / 1.5f);
	ImGui::PushItemWidth(0);

	std::string check_box_uid = "  ##" + std::to_string(u_id);
	if (ImGui::Checkbox(check_box_uid.c_str(), &(music.is_fav)))
	{
		// do some thing...
	}
	ImGui::PopItemWidth();

	ImGui::SameLine();
	ImGui::SetCursorPosX((windowSize.x - ImGui::CalcTextSize("Play").x) / 1.22f);
	std::string play_btn_lablel = "play##" + std::to_string(u_id);
	if (ImGui::Button(play_btn_lablel.c_str()))
	{
		Util::os_open_in_shell(music.music_path.c_str());
	}

	ImGui::SameLine();
	ImGui::SetCursorPosX((windowSize.x - ImGui::CalcTextSize("Remove").x) / 1.12f);
	std::string edit_btn_label = "edit##" + std::to_string(u_id);
	if (ImGui::Button("edit"))
	{
		input_author_name->setBuffer(music.author_name);
		input_music_name->setBuffer(music.music_name);
		input_file_path = music.music_path;
		music_to_edit = &music;
		menu_state = Menu_State::Edit;
	}

	ImGui::SameLine();
	std::string remove_btn_lablel = "remove##" + std::to_string(u_id);
	ImGui::SetCursorPosX((windowSize.x - ImGui::CalcTextSize("Remove").x) / 1.05f);
	if (ImGui::Button(remove_btn_lablel.c_str()))
	{
		node_to_del = AppData::instance()->musicList.list.begin();
		while (node_to_del != nullptr)
		{
			if (node_to_del->data.music_name == music.music_name)	break;
			node_to_del = node_to_del->next;
		}
	}

}


void App::music_renderer(int u_id, Music& music)
{
	ImVec2 windowSize = ImGui::GetWindowSize();
	ImGui::SetCursorPosX((windowSize.x - ImGui::CalcTextSize("....................").x) / 10);
	ImGui::Text(music.music_name.c_str());
	ImGui::SameLine();
	ImGui::SetCursorPosX((windowSize.x - ImGui::CalcTextSize("....................").x) / 2.5f);
	ImGui::Text(music.author_name.c_str());
	ImGui::SameLine();
	ImGui::SetCursorPosX((windowSize.x - ImGui::CalcTextSize("favourites").x) / 1.5f);
	ImGui::PushItemWidth(0);
	ImGui::Text(music.is_fav ? "true" : "false");

	ImGui::SameLine();
	std::string view_btn_label = "view##" + std::to_string(u_id);
	ImGui::SetCursorPosX((windowSize.x - ImGui::CalcTextSize("view").x) / 1.15f);
	if (ImGui::Button(view_btn_label.c_str()))
	{
		input_search_box_home->setBuffer(music.music_name);
		menu_state = Menu_State::Home;
	}
}

inline void App::clear_edits()
{
	input_author_name->clear();
	input_music_name->clear();
	input_file_path = "";
}

