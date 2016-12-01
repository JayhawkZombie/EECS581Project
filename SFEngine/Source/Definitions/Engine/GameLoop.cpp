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
    { //this->Levels[0]->LoadLevel();
      //this->Levels[0]->JoinLoaderThread();
      Button->OnMouseRelease = [](const sf::Vector2i &pos, const sf::Mouse::Button &b) {}; //Unbind behavior, prevent extra loads
    };

    EngineUIController.AddElement(Button);

    EngineUIController.SetBounds(sf::FloatRect(0, 0, 800, 300));
    EngineUIController.Show();
    //EngineUIController.ShowBoundsRect();

    LoadingAnimation[0].Play();
   // LoadingAnimation[0].TickUpdate(0.f);
    LoadingAnimation[1].Play();
   // LoadingAnimation[1].TickUpdate(0.f);

    LevelLoader loader;
    loader.Load("./SFEngine/Samples/Maps/MultiLayerForestSmall.ini");

    Window->clear();
    while (!Handler.PollEvents(currentRenderWindow, evnt, true)) {
      //When the window gets closed, we will be alerted, break out, and alert everything that we're closing down
      try
      {
        if (loader.DoneLoading())
          loader.JoinThread();

        CurrentFrameStart = std::chrono::high_resolution_clock::now();
        TickDelta = std::chrono::duration<double, std::milli>(CurrentFrameStart - LastFrameStart).count();
        LastFrameStart = std::chrono::high_resolution_clock::now();

        UpdateStart = std::chrono::high_resolution_clock::now();

        if (EngineUIController.IsShown())
          EngineUIController.TickUpdate(TickDelta);
        //Call "update" on items

        LoadingAnimation[0].TickUpdate(TickDelta);


        UpdateEnd = std::chrono::high_resolution_clock::now();

        currentRenderWindow->clear(sf::Color::Black);
        Render::ClearRender();

        LoadingAnimation[0].Render();
        loader.TestRender();

        if (EngineUIController.IsShown())
          EngineUIController.Render();
        //Render start

        txt.setString("Test String: Elapsed Tick Time: " + std::to_string(TickDelta));
        ResourcePoolSizes[0].setString("Texure Pooling: " + std::to_string(ResourceManager->GetSizeOfTexturePool()) + " bytes");
        ResourcePoolSizes[1].setString("Font   Pooling: " + std::to_string(ResourceManager->GetSizeOfFontPool()) + " bytes");
        ResourcePoolSizes[2].setString("FSH    Pooling: " + std::to_string(ResourceManager->GetSizeOfFragmentShaderPool()) + " bytes");
        ResourcePoolSizes[3].setString("VSH    Pooling: " + std::to_string(ResourceManager->GetSizeOfVertexShaderPool()) + " bytes");

        Render::RenderText(&txt);
        Render::RenderText(&ResourcePoolSizes[0]);
        Render::RenderText(&ResourcePoolSizes[1]);
        Render::RenderText(&ResourcePoolSizes[2]);
        Render::RenderText(&ResourcePoolSizes[3]);

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
