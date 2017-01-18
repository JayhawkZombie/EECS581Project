#include "../../Headers/UI/List.h"

namespace Engine
{

  namespace UI
  {

    ListElement::ListElement()
    {

    }

    ListElement::~ListElement()
    {

    }

    void ListElement::TickUpdate(const double &delta)
    {

    }

    void ListElement::Render()
    {
      currentRenderWindow->draw(Rect);
      currentRenderWindow->draw(Text);
    }

    void ListElement::OnShutDown()
    {

    }

    void ListElement::SerializeOut(std::ofstream &out)
    {

    }

    void ListElement::SerializeIn(std::ifstream &in)
    {

    }

    bool ListElement::RespondsTo(const Events &evnt) const
    {
      return true;
    }

    void ListElement::SetText(const std::string &string)
    {

    }

    void ListElement::Align()
    {

    }

    void ListElement::SetPosition(const sf::Vector2f &v)
    {
      Rect.setPosition(v);
      Text.setPosition(v);
      v2fPostion = v;
    }

    void ListElement::SetSize(const sf::Vector2f &v)
    {
      Rect.setSize(v);
      v2fSize = v;
    }

    void ListElement::SetFont(std::shared_ptr<sf::Font> fnt)
    {
      Text.setFont(*fnt);
    }

    sf::Vector2f ListElement::GetSize() const
    {
      return v2fSize;
    }

    sf::Vector2f ListElement::GetPosition() const
    {
      return v2fPostion;
    }

    void ListElement::HandleMouseOver(const sf::Vector2i &pos)
    {

    }

    void ListElement::HandleMouseExit(const sf::Vector2i &pos)
    {

    }

    void ListElement::HandleMouseMovement(const sf::Vector2i &pos)
    {

    }

    void ListElement::HandleMousePress(const sf::Vector2i &pos, const sf::Mouse::Button &b)
    {

    }

    void ListElement::HandleMouseRelease(const sf::Vector2i &pos, const sf::Mouse::Button &b)
    {

    }

    void ListElement::HandleFocusGained(const sf::Vector2i &pos)
    {

    }

    void ListElement::HandleFocusLost(const sf::Vector2i &pos)
    {

    }

    void ListElement::HandleKeyPress(const sf::Keyboard::Key &key)
    {

    }

    void ListElement::HandleKeyRelease(const sf::Keyboard::Key &key)
    {

    }

    void ListElement::HandleTextEntered(const sf::Keyboard::Key &key)
    {

    }

  }

}
