#include "../../Headers/Engine/Engine.h"

#include "../../Headers/Level/LevelLoader.h"

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

    sf::Text txt;
    sf::Text ResourcePoolSizes[4];
    ResourcePoolSizes[0].setCharacterSize(12);
    ResourcePoolSizes[0].setPosition(sf::Vector2f(10, 30));

    ResourcePoolSizes[1].setCharacterSize(12);
    ResourcePoolSizes[1].setPosition(sf::Vector2f(10, 50));

    ResourcePoolSizes[2].setCharacterSize(12);
    ResourcePoolSizes[2].setPosition(sf::Vector2f(10, 70));

    ResourcePoolSizes[3].setCharacterSize(12);
    ResourcePoolSizes[3].setPosition(sf::Vector2f(10, 90));



    txt.setCharacterSize(20);
    txt.setFillColor(sf::Color::White); //setColor was deprecated, but setFillColor fails
    sf::Font txtFont;
    txtFont.loadFromFile("./SFEngine/Samples/Fonts/PressStart2P.ttf");
    txt.setFont(txtFont);
    ResourcePoolSizes[0].setFont(txtFont);
    ResourcePoolSizes[1].setFont(txtFont);
    ResourcePoolSizes[2].setFont(txtFont);
    ResourcePoolSizes[3].setFont(txtFont);

    auto Button = UI::ClickButton::Create();
    Button->SetPosition(sf::Vector2f(100, 100));
    Button->SetSize(sf::Vector2f(200, 75));

    Button->OnMouseRelease = [this, Button](const sf::Vector2i &pos, const sf::Mouse::Button &b)
    { 
      Button->OnMouseRelease = [](const sf::Vector2i &pos, const sf::Mouse::Button &b) {}; //Unbind behavior, prevent extra loads
    };

    EngineUIController.AddElement(Button);

    EngineUIController.SetBounds(sf::FloatRect(0, 0, 800, 300));
    EngineUIController.Show();
    //EngineUIController.ShowBoundsRect();

    for (int i = 0; i < 6; ++i)
      LoadingAnimation[i].Play();
    

    LevelLoader loader;
    loader.Load("./SFEngine/Samples/Maps/MultiLayerForest.ini");

	  (*ScriptEngine).add(chaiscript::fun(static_cast<void(Player::*)()>(&Player::KeyDownPressed)), "KeyDownPressed");
	  (*ScriptEngine).add(chaiscript::fun(static_cast<void(Player::*)()>(&Player::KeyUpPressed)), "KeyUpPressed");
	  (*ScriptEngine).add(chaiscript::fun(static_cast<void(Player::*)()>(&Player::KeyRightPressed)), "KeyRightPressed");
	  (*ScriptEngine).add(chaiscript::fun(static_cast<void(Player::*)()>(&Player::KeyLeftPressed)), "KeyLeftPressed");
    (*ScriptEngine).add(chaiscript::fun(static_cast<void(Player::*)(float, float)>(&Player::ForcePosition)), "ForcePosition");
    (*ScriptEngine).add(chaiscript::fun(static_cast<float(Player::*)()>(&Player::GetPositionX)), "GetPositionX");
    (*ScriptEngine).add(chaiscript::fun(static_cast<float(Player::*)()>(&Player::GetPositionY)), "GetPositionY");

	  (*ScriptEngine).add_global(chaiscript::var(&TestPlayer), "MainPlayer");

    (*ScriptEngine).eval_file("./SFEngine/Samples/Scripts/MainActorScript.chai");

    Window->clear();
    while (!Handler.PollEvents(currentRenderWindow, evnt, true)) {
      //When the window gets closed, we will be alerted, break out, and alert everything that we're closing down
      try
      {
        CurrentFrameStart = std::chrono::high_resolution_clock::now();
        TickDelta = std::chrono::duration<double, std::milli>(CurrentFrameStart - LastFrameStart).count();
        LastFrameStart = std::chrono::high_resolution_clock::now();

        UpdateStart = std::chrono::high_resolution_clock::now();

        if (EngineUIController.IsShown())
          EngineUIController.TickUpdate(TickDelta);
        //Call "update" on items

        for (int i = 0; i < 6; ++i)
          LoadingAnimation[i].TickUpdate(TickDelta);

        UpdateEnd = std::chrono::high_resolution_clock::now();

        currentRenderWindow->clear(sf::Color::Black);
        Render::ClearRender();

        //LoadingAnimation[0].Render();

        if (EngineUIController.IsShown())
          EngineUIController.Render();
        //Render start

        for (int i = 0; i < 6; ++i)
          LoadingAnimation[i].Render();
        
        TestPlayer.Render();

        txt.setString("Test String: Elapsed Tick Time: " + std::to_string(TickDelta));

        Render::RenderText(&txt);

        Render();

      }
      catch (chaiscript::exception::eval_error &e)
      {
        std::cerr << "Script execution error in runtime: " << e.what() << std::endl;
      }
      currentRenderWindow->display();
      
    }
    delete RenderSettings.texture;
    return Shutdown();
  }
}
