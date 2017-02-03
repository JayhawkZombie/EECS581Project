#include "../../Headers/UI/List.h"
#include "..\..\Headers\UI\List\List.h"

namespace Engine
{

  namespace UI
  {

    List::List(const sf::Vector2f &pos, const sf::Vector2f &size)
    {
      ListFont.loadFromFile("./SFEngine/Source/CoreFiles/Fonts/Raleway-Light.ttf");
      ItemFont = std::shared_ptr<sf::Font>(new sf::Font);
      ItemFont->loadFromFile("./SFEngine/Source/CoreFiles/Fonts/Raleway-Light.ttf");

      ListText.setFont(ListFont);
      ListText.setString("List");
      ListText.setFillColor(sf::Color::White);
      ListText.setCharacterSize(12);
      ListText.setPosition(pos);

      ListRect.setPosition(pos);
      ListRect.setSize(size);
      ListRect.setTexture(&ListViewTexture.getTexture());
      ListRect.setTextureRect({ 0, 0, (int)ceil(size.x), (int)ceil(size.y) });
      ListRect.setFillColor(sf::Color(99, 99, 99, 100));
      ListRect.setOutlineColor(sf::Color::White);
      ListRect.setOutlineThickness(-2);

      ListDimensions = { 0, 0 };

      UPButton = std::shared_ptr<ClickButton>(new ClickButton);
      DOWNButton = std::shared_ptr<ClickButton>(new ClickButton);

      UPButton->SetText("Up");
      UPButton->SetFont(ItemFont, "ButtonUPFont");
      UPButton->SetPosition({ pos.x + size.x - 30.f, pos.y });
      UPButton->OnMousePress = 
        [this](const sf::Vector2i &pos, const sf::Mouse::Button &button)
      {
        this->ScrollingUp = true;
        this->ScrollingDown = false;
      };

      DOWNButton->SetText("Down");
      DOWNButton->SetFont(ItemFont, "ButtonDownFont");
      DOWNButton->SetPosition({ pos.x + size.x - 30.f, pos.y + size.y - 30.f });
      UPButton->OnMouseRelease = 
        [this](const sf::Vector2i &pos, const sf::Mouse::Button &button)
      {
        this->ScrollingDown = true;
        this->ScrollingUp = false;
      };
    }

    List::~List()
    {

    }

    void List::ScrollListUp()
    {

    }

    void List::ScrollListDown()
    {
      
    }

    void List::AddItem(std::shared_ptr<ListElement> element)
    {
      //figure out how large our texture already is
      sf::Vector2u size = ListViewTexture.getSize();

      //figure out how large we need to make the new texture
      auto __size = element->GetSize();

      //figure out the position of the new element
      auto __pos = v2fPostion.y + ListDimensions.y + __size.y + 2; //2px offset between items
      element->SetPosition({v2fPostion.x, __pos});

      //recreate the render texture
      sf::Vector2u NewSize = { size.x, (unsigned int)ceil(ListDimensions.y) + (unsigned int)ceil(__size.y) + 2 };
      ListViewTexture.create(NewSize.x, NewSize.y);
      ListViewTexture.clear(sf::Color::Transparent);

      Elements.push_back(element);
    }

    void List::CreateTexture()
    {
      //go through an render every element
    }

    void List::SetCurrentIndex(int index)
    {

    }

    int List::GetCurrentIndex() const
    {
      return CurrentIndex;
    }

    std::shared_ptr<ListElement> List::GetElementAt(int index) const
    {
      if (index >= Elements.size())
        throw std::runtime_error("index out of range of elements list");

      return Elements[index];
    }

    void List::TickUpdate(const double &delta)
    {

    }

    void List::Render()
    {
      //draw the elements
      currentRenderWindow->draw(ListRect);
      currentRenderWindow->draw(ListText);        
    }

    void List::OnShutDown()
    {

    }

    void List::SerializeOut(std::ofstream &out)
    {

    }

    void List::SerializeIn(std::ifstream &in)
    {

    }

    void List::SetPosition(const sf::Vector2f &v)
    {

    }

    void List::SetSize(const sf::Vector2f &v)
    {

    }

    void List::SetFont(std::shared_ptr<sf::Font> fnt)
    {

    }

    void List::SetText(const std::string &string)
    {
      ListText.setString(string);
    }

    bool List::RespondsTo(const Events &evnt) const
    {
      return true;
    }

    void List::HandleMouseOver(const sf::Vector2i &pos)
    {

    }

    void List::HandleMouseExit(const sf::Vector2i &pos)
    {

    }

    void List::HandleMouseMovement(const sf::Vector2i &pos)
    {

    }

    void List::HandleMousePress(const sf::Vector2i &pos, const sf::Mouse::Button &b)
    {

    }

    void List::HandleMouseRelease(const sf::Vector2i &pos, const sf::Mouse::Button &b)
    {

    }

    void List::HandleFocusGained(const sf::Vector2i &pos)
    {

    }

    void List::HandleFocusLost(const sf::Vector2i &pos)
    {

    }

    void List::HandleKeyPress(const sf::Keyboard::Key &key)
    {

    }

    void List::HandleKeyRelease(const sf::Keyboard::Key &key)
    {

    }

    void List::HandleTextEntered(const sf::Keyboard::Key &key)
    {

    }

}

}
