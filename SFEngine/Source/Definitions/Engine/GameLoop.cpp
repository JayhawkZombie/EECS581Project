#include "../../Headers/Engine/Engine.h"

#include "../../Headers/Level/LevelLoader.h"

#include <SFML/OpenGL.hpp>

#include "../../Headers/UI/TextInput.h"

#include "../../Headers/Lights/LightingSystem.h"

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

    std::shared_ptr<sf::Font> txtFont(new sf::Font);

    txtFont->loadFromFile("./SFEngine/Samples/Fonts/PressStart2P.ttf");
    txt.setFont(*txtFont);
    ResourcePoolSizes[0].setFont(*txtFont);
    ResourcePoolSizes[1].setFont(*txtFont);
    ResourcePoolSizes[2].setFont(*txtFont);
    ResourcePoolSizes[3].setFont(*txtFont);

    auto Button = UI::ClickButton::Create();
    Button->SetFont(txtFont, "PressStart2PFont");
    Button->SetPosition(sf::Vector2f(100, 100));
    Button->SetSize(sf::Vector2f(200, 75));
    Button->SetTextSize(14);
    Button->SetText("Load TestLevel");
    std::shared_ptr<Level> MainLevel(new Level);

    Button->OnMouseRelease = [this, Button, MainLevel](const sf::Vector2i &pos, const sf::Mouse::Button &b)
    { 
      MainLevel->LoadLevel("./SFEngine/Samples/Levels/Graveyard/Graveyard.xml");
    };

    std::shared_ptr<UI::TextInput> input(new UI::TextInput);
    input->SetFont("./SFEngine/Samples/Fonts/Raleway-Light.ttf");

    EngineUIController.AddElement(Button);
    EngineUIController.AddElement(input);

    EngineUIController.SetBounds(sf::FloatRect(0, 0, 800, 300));
    EngineUIController.Show();
    //EngineUIController.ShowBoundsRect();

    for (int i = 0; i < 6; ++i)
      LoadingAnimation[i].Play();

	  (*ScriptEngine).add_global(chaiscript::var(&TestPlayer), "MainPlayer");

    LightSystem TestLightSystem;

    TestLightSystem.window_size_x = Window->getSize().x;
    TestLightSystem.window_size_y = Window->getSize().y;

    TestLightSystem.AddLight(sf::Vector2f(600, 400), 400, sf::Color::Blue);
    TestLightSystem.AddLightObject({ 100, 100 }, { 100, 100 }, sf::Color::Red);
    TestLightSystem.AddLightObject({ 200, 500 }, { 80, 75 }, sf::Color::Red);
    //TestLightSystem.AddLightObject({ 700, 675 },  { 90, 135 }, sf::Color::Red);
    

    sf::Shader RadialShader;
    if (!RadialShader.loadFromFile("./SFEngine/Source/LightingRadialShader.fsh", sf::Shader::Fragment)) {

    }

    sf::Glsl::Vec4 color = sf::Color::White;
    RadialShader.setUniform("color", color);
    RadialShader.setUniform("center", sf::Glsl::Vec2{ 400, 400 });
    RadialShader.setUniform("radius", 400.f);
    RadialShader.setUniform("expand", 0.f);
    RadialShader.setUniform("windowHeight", (float)(WindowSize.y));

    sf::CircleShape circle;

    sf::RenderStates LightsState;
    sf::RenderTexture LightTexture;
    LightTexture.create(800, 800);

    circle.setRadius(400.f);
    circle.setOrigin(400.f, 400.f);
    circle.setPosition(sf::Vector2f(800.f, 800.f) / 2.f);
    circle.setFillColor(sf::Color::Transparent);

    LightTexture.draw(circle, &RadialShader);
    LightTexture.display();

    LightsState.texture = &LightTexture.getTexture();
    LightsState.blendMode = sf::BlendAlpha;
    
    TestLightSystem.LightTexture = &LightTexture;

    //TestLightSystem.ComputeRayCasts();
    TestLightSystem.AdvanceSweep({ 600.f, 400.f }, 400.f); 

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

        MainLevel->TickUpdate(TickDelta);
        TestLightSystem.RefreshFrame();
        TestLightSystem.AdvanceSweep(sf::Vector2f(sf::Mouse::getPosition(*currentRenderWindow)), 800.f);

        UpdateEnd = std::chrono::high_resolution_clock::now();

        currentRenderWindow->clear(sf::Color::Black);
        Render::ClearRender();

        glFlush();

        //LoadingAnimation[0].Render();

        if (EngineUIController.IsShown())
          EngineUIController.Render();
        //Render start

        for (int i = 0; i < 6; ++i)
          LoadingAnimation[i].Render();
        
        TestPlayer.Render();
        
        MainLevel->Render();

        TestLightSystem.Render();

        txt.setString("Test String: Elapsed Tick Time: " + std::to_string(TickDelta));

        Render::RenderText(&txt);

        Render();
        //currentRenderWindow->clear();
        //TestLightSystem.Render(*currentRenderWindow, LightsState);
        //currentRenderWindow->display();
      }
      catch (chaiscript::exception::eval_error &e)
      {
        std::cerr << "Script execution error in runtime: " << e.what() << std::endl;
      }

      glFlush();
      currentRenderWindow->display();
      
    }
    delete RenderSettings.texture;
    return Shutdown();
  }
}
