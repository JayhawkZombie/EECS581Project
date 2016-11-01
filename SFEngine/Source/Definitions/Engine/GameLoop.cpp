#include "../../Headers/Engine/Engine.h"

namespace Engine
{

  void SomeCallback(std::shared_ptr<sf::Texture> tex, const std::string &ID)
  {
    std::cerr << "<<<<< OOOOOOOH!!!!!" << std::endl;
  }

  UINT32 SFEngine::GameLoop()
  {

    Window = new sf::RenderWindow(sf::VideoMode(EngineConfig.Window_v2fWindowSize.x, EngineConfig.Window_v2fWindowSize.y), "SFEngine V0.1.1", sf::Style::Default, ContextSettings);
    MaximumWindowView = Window->getDefaultView();
    Window->setKeyRepeatEnabled(false);
    currentRenderWindow = Window;

    RenderSettings.texture = new sf::RenderTexture;
    RenderSettings.texture->create(EngineConfig.Window_v2fWindowSize.x, EngineConfig.Window_v2fWindowSize.y);
    RenderSettings.texture->setActive(true);

    FragmentShader = new sf::Shader;
    VertexShader = new sf::Shader;
    if (!FragmentShader->loadFromFile("./SFEngine/Source/CoreFragmentShader.fsh", sf::Shader::Fragment)) {
      std::cerr << "Failed to load fragment shader from file" << std::endl;
    }
    if (!VertexShader->loadFromFile("./SFEngine/Source/CoreVertexShader.vsh", sf::Shader::Vertex)) {
      std::cerr << "Failed to load vertex shader from file" << std::endl;
    }

    RenderStates.blendMode = sf::BlendAdd;
    Render::__Set__Core__Shaders(FragmentShader, VertexShader);
    Render::__Set__Render__States(RenderStates);
    Render::__Set__Render__Settings(RenderSettings);

    Render::__Set__Window(Window);
    Window->clear(sf::Color::Black);
    Window->display();

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



    txt.setCharacterSize(12);
    txt.setFillColor(sf::Color::White); //setColor was deprecated, but setFillColor fails
    sf::Font txtFont;
    txtFont.loadFromFile("./SFEngine/Samples/Fonts/OpenSans-Regular.ttf");
    txt.setFont(txtFont);
    ResourcePoolSizes[0].setFont(txtFont);
    ResourcePoolSizes[1].setFont(txtFont);
    ResourcePoolSizes[2].setFont(txtFont);
    ResourcePoolSizes[3].setFont(txtFont);

    auto Button = UI::ClickButton::Create();
    Button->SetPosition(sf::Vector2f(100, 100));
    Button->SetSize(sf::Vector2f(100, 20));
    Button->OnMouseRelease = [this](const sf::Vector2i &v, const sf::Mouse::Button &b) {
      ResourceManager->RequestTexture("./SFEngine/Samples/Textures/UI/ButtonBG.png", "ButtonBG2", SomeCallback);
    };
    EngineUIController.AddElement(Button);

    EngineUIController.SetBounds(sf::FloatRect(0, 0, 800, 300));
    EngineUIController.Show();
    //EngineUIController.ShowBoundsRect();
    std::shared_ptr<Level> lvl(new Level("./SFEngine/Samples/Maps/testforest.ini"));
    Levels.push_back(lvl);
    Levels[0]->LoadLevel();
    Levels[0]->JoinLoaderThread();
    
    
    std::cerr << "Size of Levels: " << sizeof(Levels[0]) << std::endl;
    while (!Handler.PollEvents(currentRenderWindow, evnt, true)) {
      //When the window gets closed, we will be alerted, break out, and alert everything that we're closing down
      
      CurrentFrameStart = std::chrono::high_resolution_clock::now();
      TickDelta = std::chrono::duration<double, std::milli>(CurrentFrameStart - LastFrameStart).count();
      LastFrameStart = std::chrono::high_resolution_clock::now();

      UpdateStart = std::chrono::high_resolution_clock::now();
      
      if (EngineUIController.IsShown())
        EngineUIController.TickUpdate(TickDelta);
      //Call "update" on items

      Levels[0]->TickUpdate(TickDelta);

      UpdateEnd = std::chrono::high_resolution_clock::now();

      currentRenderWindow->clear(sf::Color::Black);
      Render::ClearRender();

      Levels[0]->Render();

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

      currentRenderWindow->display();

    }
    delete RenderSettings.texture;
    return Shutdown();
  }
}
