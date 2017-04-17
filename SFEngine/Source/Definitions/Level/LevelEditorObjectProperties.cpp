#include "Level\BasicLevel.h"
#include "Level\LevelObject.h"

#include "IMGUI\imgui.h"
#include "IMGUI\imgui_internal.h"

namespace Engine
{

  void BasicLevel::ShowObjectProperties(std::shared_ptr<Engine::LevelObject> Object)
  {
    static sf::Vector2f __Position = { 0.f, 0.f };
    static sf::Vector2f __Size = { 0.f, 0.f };
    static sf::Vector2f __PDelta;
    static float __Rotation = 0.f;
    
    static float __DragLowSpeed  = 0.5f;
    static float __DragHighSpeed = 10.f;

    __Position.x = Object->Position.x;
    __Position.y = Object->Position.y;

    __Size.x = Object->Size.x;
    __Size.y = Object->Size.y;

    ImGui::Text("Position("); ImGui::SameLine(); 
    ImGui::PushItemWidth(80.f); ImGui::InputFloat("X:##Position_x", &Object->Position.x, __DragLowSpeed, __DragHighSpeed); ImGui::PopItemWidth();
    ImGui::SameLine(); 
    ImGui::PushItemWidth(80.f); ImGui::InputFloat("Y:##Position_y", &Object->Position.y, __DragLowSpeed, __DragHighSpeed); ImGui::PopItemWidth();
    ImGui::SameLine(); ImGui::Text(")");
    ImGui::NewLine();
    
    ImGui::Text("Size("); ImGui::SameLine(); 
    ImGui::PushItemWidth(80.f); ImGui::InputFloat("X:##Size_x", &Object->Size.x, __DragLowSpeed, __DragHighSpeed); ImGui::PopItemWidth();
    ImGui::SameLine(); 
    ImGui::PushItemWidth(80.f); ImGui::InputFloat("Y:##Size_y", &Object->Size.y, __DragLowSpeed, __DragHighSpeed); ImGui::PopItemWidth();
    ImGui::SameLine(); ImGui::Text(")");

    ImGui::NewLine();
    ImGui::InputFloat("Rotation:", &__Rotation, 1.f, 10.f);

    __PDelta = Object->Position - __Position;
    Object->Move(__PDelta);

  }

}
