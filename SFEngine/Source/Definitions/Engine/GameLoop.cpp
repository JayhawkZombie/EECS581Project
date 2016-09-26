#include "../../Headers/Engine/Engine.h"

namespace Engine
{

  UINT32 SFEngine::GameLoop()
  {
    sf::ContextSettings settings;

    Window = new sf::RenderWindow(sf::VideoMode(800, 800), "SFEngine V0.1.1", sf::Style::Default, settings);
    MaximumWindowView = Window->getDefaultView();
    currentRenderWindow = Window;

    Render::__Set__Window(Window);

    std::chrono::high_resolution_clock::time_point LastFrameStart = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point CurrentFrameStart = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point TickEnd;
    std::chrono::high_resolution_clock::time_point UpdateStart;
    std::chrono::high_resolution_clock::time_point UpdateEnd;
    std::chrono::high_resolution_clock::time_point RenderEnd;

    double TickDelta;

    sf::Event evnt;

    sf::Text txt;
    txt.setCharacterSize(12);
    txt.setColor(sf::Color::White); //setColor was deprecated, but setFillColor fails
    sf::Font txtFont;
    txtFont.loadFromFile("./SFEngine/Samples/Fonts/OpenSans-Regular.ttf");
    txt.setFont(txtFont);

    auto Button = UI::ClickButton::Create();
    Button->SetPosition(sf::Vector2f(200, 200));
    Button->SetSize(sf::Vector2f(100, 20));
    EngineUIController.AddElement(Button);


    while (!Handler.PollEvents(currentRenderWindow, evnt, true)) {
      //When the window gets closed, we will be alerted, break out, and alert everything that we're closing down

      CurrentFrameStart = std::chrono::high_resolution_clock::now();
      TickDelta = std::chrono::duration<double, std::milli>(CurrentFrameStart - LastFrameStart).count();
      LastFrameStart = std::chrono::high_resolution_clock::now();

      UpdateStart = std::chrono::high_resolution_clock::now();
      
      EngineUIController.TickUpdate(TickDelta);
      //Call "update" on items

      UpdateEnd = std::chrono::high_resolution_clock::now();

      currentRenderWindow->clear();

      EngineUIController.Render();
      //Render start

      txt.setString("Test String: Elapsed Tick Time: " + std::to_string(TickDelta));

      Render::RenderText(&txt);

      currentRenderWindow->display();

    }

    return Shutdown();
  }
}