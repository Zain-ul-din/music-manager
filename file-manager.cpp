#include "gui.h";
#include "FileDialog.h";

#include <windows.h>

static char filepath[256] = "";

std::string fileName = "Sound files (*.aif *.aiff *.flac *.m4a *.mp3 *.ogg *.wav *.wma *.amr *.m4p *.m4b *.mpc *.ape *.aac *.au *.ra *.snd *.mid *.midi *.rmi *.wv *.ac3 *.dts){.aif,.aiff,.flac,.m4a,.mp3,.ogg,.wav,.wma,.amr,.m4p,.m4b,.mpc,.ape,.aac,.au,.ra,.snd,.mid,.midi,.rmi,.wv,.ac3,.dts}";
std::string key = "sound_key";

FileDialog fileDialog(
    fileName,key
);


void render()
{
    ImGui::Begin("My Custom Window", NULL, ImGuiWindowFlags_NoResize); // ImGuiWindowFlags_NoMove
    ImGui::SetWindowSize(ImVec2(400, 200));
    //ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiCond_Appearing);
    //ImGui::SetWindowPos(ImVec2(0, 0));

    auto pos = ImGui::GetWindowPos();

    std::string str = "X: " + std::to_string(pos.x) + ", y: " + std::to_string(pos.y);
    ImGui::Text(str.c_str());

    //ImGui::NewFrame();

    std::string filesFilter = "Sound files (*.aif *.aiff *.flac *.m4a *.mp3 *.ogg *.wav *.wma *.amr *.m4p *.m4b *.mpc *.ape *.aac *.au *.ra *.snd *.mid *.midi *.rmi *.wv *.ac3 *.dts){.aif,.aiff,.flac,.m4a,.mp3,.ogg,.wav,.wma,.amr,.m4p,.m4b,.mpc,.ape,.aac,.au,.ra,.snd,.mid,.midi,.rmi,.wv,.ac3,.dts}";
    
    // open Dialog Simple
    if (ImGui::Button("Open File Dialog"))  fileDialog.open();

    // display
    fileDialog.render();
    
    
    if (ImGui::Button("open model"))
    {
        ImGui::OpenPopup("Select file");
    }
    
    if (ImGui::BeginPopupModal("Select file", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {

        ImGui::Text("Please select a file:");

        ImGui::Spacing();
        ImGui::Separator();

        ImGui::InputText("Enter file path", filepath, sizeof(filepath));

        std::cout << std::string(filepath) << "\n";

        if (ImGui::Button("close", ImVec2(160, 0))) 
        {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
    

    if (ImGui::Button("Say Hello World"))
    {
        std::cout << "Hello World \n";
    }

    //ImGui::EndFrame();

    ImGui::End();
}

#pragma comment(lib, "Winmm.lib")

// driver code
int main()
{
    // play sound
    
    PlaySound(TEXT("sound.mp3"), NULL, SND_SYNC);
    fileDialog.onFileSelect += [&](std::string& filePath)-> void
    {
        std::cout << "File path : " << filePath << "\n";
    };

	auto renderer = Renderer::Instance();
    renderer->render(&render);
	return 0;
}

