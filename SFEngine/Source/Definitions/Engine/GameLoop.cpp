#include "../../Headers/Engine/Engine.h"
#include "../../Headers/Level/LevelLoader.h"
#include <SFML/OpenGL.hpp>
#include "../../Headers/UI/TextInput.h"
#include "../../Headers/Lights/LightingSystem.h"

#ifdef WITH_EDITOR
#include "../../Headers/Engine/Editor.h"
#endif

namespace Engine
{

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
    GameMainTexture->create(1200, 900);

    sf::Sprite GameSprite;
    GameSprite.setTexture(GameMainTexture->getTexture());

    (*ScriptEngine).add_global(chaiscript::var(&TestPlayer), "MainPlayer");

    //if we are launching with the editor, enable the editor
    //otherwise, create a main level and update the level instead of the editor
//#ifdef WITH_EDITOR
//    GameEditor.Render();
//#else
//    std::shared_ptr<Level> MainLevel(new Level);
//#endif

#ifndef WITH_EDITOR
    std::shared_ptr<Level> MainLevel(new Level);
#endif

    sf::RectangleShape Rect;
    Rect.setPosition({ 100, 100 });
    Rect.setSize({ 500, 500 });
    Rect.setFillColor(sf::Color(0, 0, 102));

    Window->clear(sf::Color::Black);
    std::shared_ptr<sf::RenderTexture> EditorTexture(new sf::RenderTexture);
    EditorTexture->create(1200, 900);
    EditorTexture->clear(sf::Color::Transparent);

    sf::Sprite EditorSprite;
    EditorSprite.setTexture(EditorTexture->getTexture());

    while (!Handler.PollEvents(currentRenderWindow, evnt, true)) {
      //When the window gets closed, we will be alerted, break out, and alert everything that we're closing down
      try
      {
        CurrentFrameStart = std::chrono::high_resolution_clock::now();
        TickDelta = std::chrono::duration<double, std::milli>(CurrentFrameStart - LastFrameStart).count();
        LastFrameStart = std::chrono::high_resolution_clock::now();

        UpdateStart = std::chrono::high_resolution_clock::now();

        //if (EngineUIController.IsShown())
        //  EngineUIController.TickUpdate(TickDelta);

        //if we have the editor, update that instead of the main level
#ifdef WITH_EDITOR
        GameEditor.TickUpdate(TickDelta);
        TestGame.TickUpdate(TickDelta);
#else
        MainLevel->TickUpdate(TickDelta);
#endif

        UpdateEnd = std::chrono::high_resolution_clock::now();

        //if (EngineUIController.IsShown())
        //  EngineUIController.Render();
        //Render start

        //if we have the editor, render that instead of the main level
        GameMainTexture->clear(sf::Color::Transparent);
        Window->setActive(true);
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
        Window->display();
        //Render();
      }
      catch (chaiscript::exception::eval_error &e)
      {
        std::cerr << "Script execution error in runtime: " << e.what() << std::endl;
      }

      //glFlush();
      //currentRenderWindow->display();

    }
    //delete RenderSettings.texture;
    return Shutdown();
  }
}