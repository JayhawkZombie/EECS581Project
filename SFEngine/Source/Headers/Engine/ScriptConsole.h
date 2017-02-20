#ifndef SFENGINE_SCRIPT_CONSOLE_H
#define SFENGINE_SCRIPT_CONSOLE_H

#include "../Globals/GlobalHooks.h"
#include "../../../ThirdParty/chaiscript/chaiscript.hpp"
#include "../../../ThirdParty/chaiscript/utility/utility.hpp"
#include <TGUI\TGUI.hpp>


namespace Engine
{

  class ScriptConsole
  {
  public:
    ScriptConsole(const sf::Vector2f &Size, const sf::Vector2f &Position, tgui::Theme::Ptr themeptr);
    ~ScriptConsole();

    void SetTheme(tgui::Theme::Ptr themeptr);
    void Open();
    void Close();

    void SetInputCallback(std::function<void(std::string)> func);
    void IssueResponse(std::string response);

    void AddToModule(chaiscript::ModulePtr module, const std::string &name);
    static void BindMethods(chaiscript::ModulePtr module);
    void Clear();
  protected:
    std::function<void(std::string)> InputCB;
    std::function<void(std::string)> ResponseCB;

    void IssueInput(std::string input);

    sf::Color ConsoleInputColor = sf::Color(109, 109, 109);
    sf::Color ConsoleOutputColor = sf::Color(72, 122, 140);
    
    tgui::Theme::Ptr Theme;
    tgui::Panel::Ptr Panel;
    tgui::ChatBox::Ptr Console;
    tgui::EditBox::Ptr Input;
    tgui::Button::Ptr CommandButton;
  };

}

#endif
