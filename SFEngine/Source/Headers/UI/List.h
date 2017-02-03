//#ifndef SFENGINE_UI_LIST_H
//#define SFENGINE_UI_LIST_H
//
//#include "BaseUIElement.h"
//#include "ClickButton.h"
//
//namespace Engine
//{
//#ifdef WITH_EDITOR
//  class Editor;
//#endif
//
//  namespace UI
//  {
//
//    class ListElement : public BaseUIElement
//    {
//    public:
//#ifdef WITH_EDITOR
//      friend class Engine::Editor;
//#endif
//
//      TYPEDEF_PARENT_CLASS(BaseUIElement);
//
//      ListElement();
//      virtual ~ListElement();
//
//      virtual void TickUpdate(const double &delta);
//      virtual void Render();
//      virtual void OnShutDown();
//      virtual void SerializeOut(std::ofstream &out);
//      virtual void SerializeIn(std::ifstream &in);
//
//      virtual bool RespondsTo(const Events &evnt) const;
//      virtual void Align();
//
//      virtual void SetPosition(const sf::Vector2f &v);
//      virtual void SetSize(const sf::Vector2f &v);
//
//      virtual void SetFont(std::shared_ptr<sf::Font> fnt);
//
//      virtual sf::Vector2f GetSize() const;
//      virtual sf::Vector2f GetPosition() const;
//
//
//      virtual void SetText(const std::string &str);
//      //data used for visualization
//      sf::RectangleShape Rect;
//      sf::Text Text;
//
//      virtual void HandleMouseOver(const sf::Vector2i &pos);
//      virtual void HandleMouseExit(const sf::Vector2i &pos);
//      virtual void HandleMouseMovement(const sf::Vector2i &pos);
//      virtual void HandleMousePress(const sf::Vector2i &pos, const sf::Mouse::Button &b);
//      virtual void HandleMouseRelease(const sf::Vector2i &pos, const sf::Mouse::Button &b);
//      virtual void HandleFocusGained(const sf::Vector2i &pos);
//      virtual void HandleFocusLost(const sf::Vector2i &pos);
//      virtual void HandleKeyPress(const sf::Keyboard::Key &key);
//      virtual void HandleKeyRelease(const sf::Keyboard::Key &key);
//      virtual void HandleTextEntered(const sf::Keyboard::Key &key);
//
//    };
//
//    class List : public BaseUIElement
//    {
//    public:
//#ifdef WITH_EDITOR
//      friend class Editor;
//#endif
//
//      TYPEDEF_PARENT_CLASS(BaseUIElement);
//
//      List(const sf::Vector2f &pos, const sf::Vector2f &size);
//      virtual ~List();
//
//      void AddItem(std::shared_ptr<ListElement> element);
//
//      void SetCurrentIndex(int index);
//      int GetCurrentIndex() const;
//      std::shared_ptr<ListElement> GetElementAt(int index) const;
//      void CreateTexture();
//
//      virtual void TickUpdate(const double &delta);
//      virtual void Render();
//      virtual void OnShutDown();
//      virtual void SerializeOut(std::ofstream &out);
//      virtual void SerializeIn(std::ifstream &in);
//
//      virtual void SetPosition(const sf::Vector2f &v);
//      virtual void SetSize(const sf::Vector2f &v);
//
//      virtual void SetFont(std::shared_ptr<sf::Font> fnt);
//      virtual void SetText(const std::string &string);
//
//      virtual bool RespondsTo(const Events &evnt) const;
//
//    protected:
//      std::vector<std::shared_ptr<UI::ListElement>> Elements;
//      sf::RenderTexture ListViewTexture;
//      sf::IntRect ListViewRect;
//      sf::Vector2f ListDimensions;
//
//      std::shared_ptr<ClickButton> UPButton;
//      std::shared_ptr<ClickButton> DOWNButton;
//
//      sf::Text ListText;
//      sf::Font ListFont;
//
//      sf::RectangleShape ListRect;
//
//      std::uint32_t CurrentIndex = 0;
//      std::uint32_t CurrentHighlighted;
//
//      virtual void ScrollListUp();
//      virtual void ScrollListDown();
//
//      bool ScrollingUp = false;
//      bool ScrollingDown = false;
//      float ScrollWait = 0.25;
//
//      virtual void HandleMouseOver(const sf::Vector2i &pos);
//      virtual void HandleMouseExit(const sf::Vector2i &pos);
//      virtual void HandleMouseMovement(const sf::Vector2i &pos);
//      virtual void HandleMousePress(const sf::Vector2i &pos, const sf::Mouse::Button &b);
//      virtual void HandleMouseRelease(const sf::Vector2i &pos, const sf::Mouse::Button &b);
//      virtual void HandleFocusGained(const sf::Vector2i &pos);
//      virtual void HandleFocusLost(const sf::Vector2i &pos);
//      virtual void HandleKeyPress(const sf::Keyboard::Key &key);
//      virtual void HandleKeyRelease(const sf::Keyboard::Key &key);
//      virtual void HandleTextEntered(const sf::Keyboard::Key &key);
//
//    };
//
//  }
//
//}
//
//
//#endif
