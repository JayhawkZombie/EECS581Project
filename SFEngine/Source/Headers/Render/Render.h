#ifndef SFENGINE_RENDER_H
#define SFENGINE_RENDER_H

#include <SFML\Graphics.hpp>
#include <cassert>

namespace Engine
{
  namespace Render
  {
    sf::FloatRect DefaultBounds();

    void RenderText(const sf::Text &text);
    void RenderText(const sf::Text &text, const sf::FloatRect &bounds);
    
    void RenderVertices(const sf::VertexArray &arr);
    void RenderVertices(const sf::VertexArray &arr, const sf::FloatRect &bounds);

    void RenderShape(const sf::Shape &shape);
    void RenderShape(const sf::Shape &shape, const sf::FloatRect &bounds);

    void RenderSprite(const sf::Sprite &spr);
    void RenderSprite(const sf::Sprite &spr, const sf::FloatRect &bounds);

    void RenderSFDrawable(const sf::Drawable &drawable);
    void RenderSFDrawable(const sf::Drawable &drawable, const sf::FloatRect &bounds);

    void __Set__Window(sf::RenderWindow *window);
    void __Create__ViewPanel(const sf::FloatRect &bounds);
  }
}


#endif
