#include "../../Headers/Engine/Engine.h"
#include "../../Headers/Level/LevelLoader.h"
#include <SFML/OpenGL.hpp>
#include "../../Headers/Lights/LightingSystem.h"


#ifdef WITH_EDITOR
#include "../../Headers/Engine/Editor.h"
#include "../../../ThirdParty/IMGUI/imgui_internal.h"
#endif

namespace Engine
{

  void func()
  {
    std::cerr << "Func called" << std::endl;
  }

  void SomeCallback(std::shared_ptr<sf::Texture> tex, const std::string &ID)
  {
    std::cerr << "<<<<< OOOOOOOH!!!!!" << std::endl;
  }

  UINT32 SFEngine::GameLoop()
  {
    std::chrono::high_resolution_clock::time_point LastFrameStart = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point CurrentFrameStart = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point TickEnd;
    std::chrono::high_resolution_clock::time_point UpdateStart;
    std::chrono::high_resolution_clock::time_point UpdateEnd;
    std::chrono::high_resolution_clock::time_point RenderEnd;

    double TickDelta;
    sf::Event evnt;

    std::shared_ptr<sf::RenderTexture> GameMainTexture = std::make_shared<sf::RenderTexture>();
    GameMainTexture->create(static_cast<unsigned int>(std::ceil(WindowSize.x)), static_cast<unsigned int>(std::ceil(WindowSize.y)));

    sf::Sprite GameSprite;
    GameSprite.setTexture(GameMainTexture->getTexture());

    Window->clear(sf::Color::Black);
    std::shared_ptr<sf::RenderTexture> EditorTexture(new sf::RenderTexture);
    EditorTexture->create(static_cast<unsigned int>(std::ceil(WindowSize.x)), static_cast<unsigned int>(std::ceil(WindowSize.y)));
    EditorTexture->clear(sf::Color::Transparent);

    sf::Sprite EditorSprite;
    EditorSprite.setTexture(EditorTexture->getTexture());

    tgui::Theme::Ptr theme = std::make_shared<tgui::Theme>("./SFEngine/Source/CoreFiles/UIThemes/UIDark.txt");

    EngineScriptConsole = std::make_shared<ScriptConsole>(sf::Vector2f(WindowSize.x, 400), sf::Vector2f(0, (WindowSize.y - 400.f)), theme);
    EngineScriptConsole->SetInputCallback([this](std::string str) { this->CommandProcessor(str); });

    AddKeyboardShortcut({ sf::Keyboard::LControl, sf::Keyboard::LShift, sf::Keyboard::C },
                        [this]() { if (this && this->EngineScriptConsole) this->EngineScriptConsole->Open(); });

    chaiscript::ModulePtr mptr = std::make_shared<chaiscript::Module>();
    ScriptConsole::BindMethods(mptr);
    ScriptEngine->add(mptr);
    EngineScriptConsole->AddToModule(mptr, "Console");
    ScriptEngine->eval_file("./SFEngine/Source/CoreFiles/Scripts/ConsoleFunctions.chai");
    Window->setVerticalSyncEnabled(false);
    Window->setKeyRepeatEnabled(false);
    //Window->setFramerateLimit(60);
    bool Closed = false;

    ScriptEngine->add(chaiscript::fun(Engine::func), "func");

#ifdef WITH_EDITOR
    //GameEditor.PreLoopSetup();
    sf::Clock dClock;
    ImGui::SFML::Init(*currentRenderWindow);
#else
    std::shared_ptr<Level> MainLevel(new Level);
#endif

#ifdef WITH_EDITOR
    //For ImGui
    ImGuiStyle * style = &ImGui::GetStyle();

    style->WindowPadding = ImVec2(5, 5);
    style->WindowRounding = 3.0f;
    style->FramePadding = ImVec2(3, 3);
    style->FrameRounding = 3.0f;
    style->ItemSpacing = ImVec2(6, 4);
    style->ItemInnerSpacing = ImVec2(4, 3);
    style->IndentSpacing = 25.0f;
    style->ScrollbarSize = 10.0f;
    style->ScrollbarRounding = 4.0f;
    style->GrabMinSize = 5.0f;
    style->GrabRounding = 3.0f;

    style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
    style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.0f);
    style->Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_Border] = ImVec4(0.40f, 0.40f, 0.4f, 0.48f);
    style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
    style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.10f, 0.09f, 0.12f, 0.75f);
    style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_ComboBg] = ImVec4(0.19f, 0.18f, 0.21f, 1.00f);
    style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_CloseButton] = ImVec4(0.40f, 0.39f, 0.38f, 0.16f);
    style->Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
    style->Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
    style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
    style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);

    ImGuiIO *io = &ImGui::GetIO();
    io->Fonts->AddFontFromFileTTF("./SFEngine/Source/CoreFiles/Fonts/open-sans/OpenSans-Light.ttf", 10);
    io->Fonts->AddFontFromFileTTF("./SFEngine/Source/CoreFiles/Fonts/open-sans/OpenSans-Light.ttf", 12);
    io->Fonts->AddFontFromFileTTF("./SFEngine/Source/CoreFiles/Fonts/open-sans/OpenSans-Light.ttf", 14);
    io->Fonts->AddFontFromFileTTF("./SFEngine/Source/CoreFiles/Fonts/open-sans/OpenSans-Light.ttf", 16);
#endif
    vec2d Gravity;

    AssignBoundaries(900, 1700);
    Gravity.x = 0.f;
    Gravity.y = 0.01f;
    SetGravity(&Gravity);

    std::shared_ptr<Level> MainLevel = std::make_shared<Level>(sf::Vector2u({ 1700, 900 }), sf::FloatRect(0, 0, 1700, 900), true, sf::Vector2f({ 1700 / 16.f, 900 / 16.f }));
    MainLevel->LoadLevel("./Projects/TestProject/testproject.json"); //Just for testing for right now

    std::shared_ptr<sf::RenderTexture> LevelTexture = std::make_shared<sf::RenderTexture>();
    LevelTexture->create(1700, 900);
    sf::RectangleShape LevelRect;
    LevelRect.setPosition({ 0, 0 });
    LevelRect.setSize({ 1700, 900 });
    LevelRect.setTexture(&(EditorTexture->getTexture()));
    LevelRect.setTextureRect({ 0, 0, 1700, 900 });

    ScriptEngine->eval_file("./Projects/TestProject/Scripts/main.chai");
    ScriptEngine->eval("GameStart();");
    
#ifdef WITH_EDITOR
    while (!FlagForClose && currentRenderWindow && currentRenderWindow->isOpen()) {
#else
    while (currentRenderWindow && currentRenderWindow->isOpen()) {
#endif
      //When the window gets closed, we will be alerted, break out, and alert everything that we're closing down
      Closed = Handler.PollEvents(currentRenderWindow, evnt, true);
      sf::Time fTime = { sf::seconds(0) };

      try
      {
        CurrentFrameStart = std::chrono::high_resolution_clock::now();
        TickDelta = std::chrono::duration<double, std::milli>(CurrentFrameStart - LastFrameStart).count();
        LastFrameStart = std::chrono::high_resolution_clock::now();

        UpdateStart = std::chrono::high_resolution_clock::now();

        fTime = dClock.restart();

        ImGui::SFML::Update(*currentRenderWindow, fTime);
        
        //ImGui::ShowTestWindow();
        MainLevel->TickUpdate(TickDelta);

        UpdateEnd = std::chrono::high_resolution_clock::now();

        Window->clear(EngineRenderSettings.BGClearColor);
        EditorTexture->clear(EngineRenderSettings.BGClearColor); 
        
#ifdef WITH_EDITOR
        EditorTexture->setActive(true);
        MainLevel->Render(EditorTexture);
        EditorTexture->setActive(true);
        EditorTexture->display();

        Window->setActive(true);
        Window->draw(LevelRect);
#else
        MainLevel->Render();
#endif
        ImGui::EndFrame();
        ImGui::Render();

        Window->setActive(true);
        Window->display();
      }
      catch (chaiscript::exception::eval_error &e)
      {
        std::cerr << "Script execution error in runtime: " << e.what() << std::endl;
      }

    }
    //delete RenderSettings.texture;
    EditorTexture.reset();
    LevelTexture.reset();
    return Shutdown();
  }
}