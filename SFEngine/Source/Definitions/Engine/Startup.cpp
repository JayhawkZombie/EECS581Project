#include "../../Headers/Engine/Engine.h"

namespace Engine
{
  UINT32 SFEngine::Startup()
  {
    std::cerr << "Binding callbacks" << std::endl;
    Handler.BindCallback(Events::GainedFocus,
                         [this]() {this->HandleWindowGainedFocus(); });

    Handler.BindCallback(Events::LostFocus,
                         [this]() {this->HandleWindowLostFocus(); });

    Handler.BindCallback(Events::WindowClosed,
                         [this]() {this->HandleWindowClosed(); });

    Handler.BindCallback(Events::WindowResized,
                         [this]() {this->HandleWindowResized(); });

    Handler.BindCallback(Events::MouseDown,
                         [this](const sf::Vector2i &i, const sf::Mouse::Button &b) {this->HandleMousePress(i, b); });

    Handler.BindCallback(Events::MouseReleased,
                         [this](const sf::Vector2i &i, const sf::Mouse::Button &b) {this->HandleMouseRelease(i, b); });

    Handler.BindCallback(Events::MouseMoved,
                         [this](const sf::Vector2i &i) {this->HandleMouseMovement(i); });

    Handler.BindCallback(Events::KeyPressed,
                         [this](const sf::Keyboard::Key &k) {this->HandleKeyPress(k); });

    Handler.BindCallback(Events::KeyReleased,
                         [this](const sf::Keyboard::Key &k) {this->HandleKeyRelease(k); });

    std::cerr << "Starting resource manager" << std::endl;
    ResourceManager = std::shared_ptr<Resource::ResourceManager>(new Resource::ResourceManager);
    ResourceManager->Start();

    return GameLoop();
  }
}
