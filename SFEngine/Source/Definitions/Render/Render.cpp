#include "../../Headers/Render/Render.h"

namespace
{
  sf::RenderWindow *DrawWindow = nullptr;
  sf::Vector2u WinSize;
  sf::FloatRect ViewPanel;
  sf::View view;
}

namespace Engine
{
  namespace Render
  {
    sf::FloatRect DefaultBounds()
    {
      return sf::FloatRect(0, 0, WinSize.x, WinSize.y);
    }

    void RenderText(const sf::Text &text)
    {
      RenderText(text, DefaultBounds());
    }

    void RenderText(const sf::Text &text, const sf::FloatRect &bounds)
    {
      RenderSFDrawable(text, bounds);
    }

    void RenderVertices(const sf::VertexArray &arr)
    {
      RenderVertices(arr, DefaultBounds());
    }

    void RenderVertices(const sf::VertexArray &arr, const sf::FloatRect &bounds)
    {
      RenderSFDrawable(arr, bounds);
    }

    void RenderShape(const sf::Shape &shape)
    {
      RenderShape(shape, DefaultBounds());
    }

    void RenderShape(const sf::Shape &shape, const sf::FloatRect &bounds)
    {
      RenderSFDrawable(shape, bounds);
    }

    void RenderSprite(const sf::Sprite &spr)
    {
      RenderSprite(spr, DefaultBounds());
    }

    void RenderSprite(const sf::Sprite &spr, const sf::FloatRect &bounds)
    {
      RenderSFDrawable(spr, bounds);
    }

    void RenderSFDrawable(const sf::Drawable &drawable, const sf::FloatRect &bounds)
    {
      if (DrawWindow) {
        __Create__ViewPanel(bounds);

        DrawWindow->draw(drawable);
        DrawWindow->setView(DrawWindow->getDefaultView());
      }
    }

    void __Set__Window(sf::RenderWindow *window)
    {
      DrawWindow = window;
      if (DrawWindow) {
        WinSize = DrawWindow->getSize();
      }
      
      assert(DrawWindow);
    }


    void __Create__ViewPanel(const sf::FloatRect &bounds)
    {
      ViewPanel = sf::FloatRect(
        bounds.left / WinSize.x,
        bounds.top / WinSize.y,
        bounds.width / WinSize.x,
        bounds.height / WinSize.y
      );

      view.reset(bounds);
      view.setViewport(ViewPanel);
    }
  }
}