#ifndef CREATE_CONVO_H
#define CREATE_CONVO_H

#include <TGUI\TGUI.hpp>
#include "../Conversation.h"
#include "../ListReader.h"

#include "../../SFEngine/Source/Headers/Engine/Engine.h"

//namespace Engine {

  class NewConvoCreator
  {
  public:
    NewConvoCreator() = default;
    ~NewConvoCreator() = default;

    void CreateConvoNode(std::string filename, MainCharacter mc);
    void OpenTheme(tgui::Theme::Ptr Theme);
    void Close();
    void setVariables(int numChoices, std::string contentText, std::string buttonText);

  protected:

    void NewWindow();
    void LoadConvo(int cur);
    void NewConvo();
    void addChoice();

    void LoadConvoGUI(int cur, int j);

    tgui::Theme::Ptr Theme;
    tgui::ChildWindow::Ptr CreationWindow;

    tgui::EditBox::Ptr EditChoice;
    tgui::EditBox::Ptr EditChoiceID;
    tgui::EditBox::Ptr EditContent;
    tgui::EditBox::Ptr EditID;
    tgui::EditBox::Ptr EditCharacter;
    tgui::Button::Ptr EditSave;
    tgui::Button::Ptr EditAddChoice;
    tgui::Button::Ptr EditLoad;

    tgui::Button::Ptr CreateConversations;
    tgui::Button::Ptr LoadGameConvo;
    tgui::ChatBox::Ptr CharSpeaking;
    tgui::TextBox::Ptr ContentText;
    tgui::Button::Ptr ChoiceButton;
    std::string nodeID;

    std::vector<tgui::Button::Ptr> choices_vec;

    int textSize;
    int buttonPos;
    int m_numChoices;
    std::string m_contentText;
    std::string m_buttonText;
    std::string m_id;
    Conversation** convo_arr = NULL;
    int totalNodes = 0;

    std::vector<std::shared_ptr<std::string>> nodeIDs;
    sf::Vector2u WindowSize;
    std::shared_ptr<tgui::Gui> GUI;
    MainCharacter my_mc;
    std::string my_filename;


  };

//}

#endif
