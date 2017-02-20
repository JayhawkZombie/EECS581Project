#include "../../Headers/Engine/Engine.h"
#include "../../Headers/Level/LevelLoader.h"
#include <SFML/OpenGL.hpp>
#include "../../Headers/Lights/LightingSystem.h"

#ifdef WITH_EDITOR
#include "../../Headers/Engine/Editor.h"
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
    Window->setVerticalSyncEnabled(false);
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
    GameEditor.PreLoopSetup();
#else
    std::shared_ptr<Level> MainLevel(new Level);
#endif

#ifdef WITH_EDITOR
    while (!FlagForClose && currentRenderWindow && currentRenderWindow->isOpen()) {
#else
    while (currentRenderWindow && currentRenderWindow->isOpen()) {
#endif
      //When the window gets closed, we will be alerted, break out, and alert everything that we're closing down
      Closed = Handler.PollEvents(currentRenderWindow, evnt, true);

      try
      {
        CurrentFrameStart = std::chrono::high_resolution_clock::now();
        TickDelta = std::chrono::duration<double, std::milli>(CurrentFrameStart - LastFrameStart).count();
        LastFrameStart = std::chrono::high_resolution_clock::now();

        UpdateStart = std::chrono::high_resolution_clock::now();

        //if we have the editor, update that instead of the main level
#ifdef WITH_EDITOR
        GameEditor.TickUpdate(TickDelta);
        TestGame.TickUpdate(TickDelta);
#else
        MainLevel->TickUpdate(TickDelta);
#endif

        UpdateEnd = std::chrono::high_resolution_clock::now();
        //Render start

        //if we have the editor, render that instead of the main level
        GameMainTexture->clear(sf::Color::Transparent);
        Window->clear(sf::Color::Black);
        
        EditorTexture->clear(sf::Color::Transparent);
        
#ifdef WITH_EDITOR
        TestGame.Render(GameMainTexture);
        GameMainTexture->display();
        GameSprite.setTexture(GameMainTexture->getTexture());
        currentRenderWindow->draw(GameSprite);
        GameEditor.Render(EditorTexture);
#else
        MainLevel->Render();
#endif

        EditorTexture->display();
        Window->draw(EditorSprite);
        GUI->draw();
        Window->display();
      }
      catch (chaiscript::exception::eval_error &e)
      {
        std::cerr << "Script execution error in runtime: " << e.what() << std::endl;
      }

    }
    //delete RenderSettings.texture;
    return Shutdown();
  }
}