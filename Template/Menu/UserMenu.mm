#include "UserMenu.h"
#include "Utilities/Memory.h"
#include "Source/Main.h"



void UserMenu::RenderMenu()
{
    ImGui::SetNextWindowPos(settings.MenuPos, ImGuiCond_Once);
    ImGui::SetNextWindowSize(settings.MenuSize, ImGuiCond_Once);

    ImGui::StyleColorsClassic();

    ImGui::Begin("ImGui Menu Template", NULL, ImGuiWindowFlags_NoCollapse);

    // save Positions
    settings.MenuSize = ImGui::GetCurrentWindow()->Size;
    settings.MenuPos  = ImGui::GetCurrentWindow()->Pos;
 
    
    
    ImGui::End();
}
