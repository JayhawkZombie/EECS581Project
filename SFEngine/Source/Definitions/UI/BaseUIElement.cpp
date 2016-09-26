#include "../../Headers/UI/BaseUIElement.h"

namespace Engine
{
  namespace UI
  {
    BaseUIElement::BaseUIElement()
    {
      State = DefaultBisetState;
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

    /**
     * Variadic template construction of MouseTarget (in-place construction, to avoid copying)
     *   I Promise, it only LOOKS gross. Everything is resolved at compile time :D
     */
    template<typename EVENTS, typename CALLBACK, typename... OTHERS>
    void BaseUIElement::AddMouseTarget(std::string &ID, const sf::FloatRect &rect, EVENTS, CALLBACK, OTHERS...)
    {
      auto found = MouseTargets.find(ID);

      if (found == MouseTargets.end()) {
        MouseTargets.emplace(
          std::piecewise_construct,
          std::make_tuple(ID),
          std::make_tuple(rect, EVENTS, CALLBACK, OTHERS...)
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

  } //namespace UI
}
