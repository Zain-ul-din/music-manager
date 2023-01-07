#include "gui.h"

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

    if (ImGui::Button("Say Hello World"))
    {
        std::cout << "Hello World \n";
    }

    //ImGui::EndFrame();

    ImGui::End();
}

// driver code
int main()
{
	auto renderer = Renderer::Instance();
    renderer->render(&render);
	return 0;
}
