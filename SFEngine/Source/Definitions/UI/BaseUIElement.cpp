#include "../../Headers/UI/BaseUIElement.h"

namespace Engine
{
  namespace UI
  {
    BaseUIElement::BaseUIElement()
    {
      State = DefaultBisetState;
      OnFocusGained = [this](const sf::Vector2i &) {};
      OnFocusLost = [this](const sf::Vector2i &) {};
      OnMouseExit = [this](const sf::Vector2i &) {};
      OnMouseMove = [this](const sf::Vector2i &) {};
      OnMouseOver = [this](const sf::Vector2i &) {};
      OnMousePress = [this](const sf::Vector2i &, const sf::Mouse::Button &) {};
      OnMouseRelease = [this](const sf::Vector2i &, const sf::Mouse::Button &) {};
    }

    BaseUIElement::~BaseUIElement()
    {

    }

    void BaseUIElement::Render()
    {
      for (auto it = RenderTargets.begin(); it != RenderTargets.end(); it++) {
        it->second.Render();
      }
    }

    void BaseUIElement::SerializeOut(std::ostream &out)
    {

    }

    void BaseUIElement::SetPosition(const sf::Vector2f &v)
    {
      v2fPostion = v;
    }

    void BaseUIElement::SetSize(const sf::Vector2f &v)
    {
      v2fSize = v;
    }

    sf::Vector2f BaseUIElement::GetSize() const
    {
      return v2fSize;
    }

    sf::Vector2f BaseUIElement::GetPosition() const
    {
      return v2fPostion;
    }

    void BaseUIElement::AddRenderTarget(std::string &ID, std::shared_ptr<sf::Drawable> item)
    {
      auto found = RenderTargets.find(ID);

      if (found == RenderTargets.end()) {

        //UGH, have to construct the RenderTarget in place
        //STL will try to forward the arguments to the constructor
        //in std::pair, which will try to invoke a copy constructor.
        //Obviously, we want to avoid copying as much as possible, especially with strings

        //Have to use piecewise construction of the std::pair stored in the map
        //but it will cause the RenderTarget to be constructed in-place and no copying will be done
        RenderTargets.emplace(
          std::piecewise_construct, 
          std::make_tuple(ID), 
          std::make_tuple(item)
        );
      }
    }

    void BaseUIElement::AddMouseTarget(std::string &ID, MouseTarget &tgt)
    {
      auto found = MouseTargets.find(ID);

      if (found == MouseTargets.end()) {
        MouseTargets.emplace(
          std::piecewise_construct,
          std::make_tuple(ID),
          std::make_tuple(tgt)
        );
      }
    }

    void BaseUIElement::AddKeyTarget(std::string &ID, KeyTarget &tgt)
    {
      auto found = KeyTargets.find(ID);

      if (found == KeyTargets.end()) {
        KeyTargets.emplace(
          std::piecewise_construct,
          std::make_tuple(ID),
          std::make_tuple(tgt)
        );
      }
    }

    bool BaseUIElement::RespondsTo(const Events &evnt) const
    {

      return false;
    }

    void BaseUIElement::Align()
    {

    }

    void BaseUIElement::HandleMouseExit(const sf::Vector2i &pos)
    {

    }

    void BaseUIElement::HandleMouseOver(const sf::Vector2i &pos)
    {

    }

    void BaseUIElement::HandleMouseMovement(const sf::Vector2i &pos)
    {

    }

    void BaseUIElement::HandleMousePress(const sf::Vector2i &pos, const sf::Mouse::Button &b)
    {

    }

    void BaseUIElement::HandleMouseRelease(const sf::Vector2i &pos, const sf::Mouse::Button &b)
    {

    }

    void BaseUIElement::HandleFocusGained(const sf::Vector2i &pos)
    {

    }

    void BaseUIElement::HandleFocusLost(const sf::Vector2i &pos)
    {

    }

    void BaseUIElement::HandleKeyPress(const sf::Keyboard::Key &key)
    {

    }

    void BaseUIElement::HandleKeyRelease(const sf::Keyboard::Key &key)
    {

    }
  } //namespace UI
}
